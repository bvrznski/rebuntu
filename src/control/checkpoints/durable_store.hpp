#pragma once
#include <cerrno>
#include <filesystem>
#include <fstream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <fcntl.h>
#include <unistd.h>

namespace rebuntu::control::checkpoints {
enum class DurableStage { prepared, applied, verified, committed, rollback_pending, rolled_back, failed };
struct DurableRecord { std::string transaction_id; std::string work_id; DurableStage stage{DurableStage::prepared}; std::size_t sequence{0}; };
inline std::string_view stage_name(DurableStage s) {
    switch(s){case DurableStage::prepared:return "prepared";case DurableStage::applied:return "applied";case DurableStage::verified:return "verified";case DurableStage::committed:return "committed";case DurableStage::rollback_pending:return "rollback_pending";case DurableStage::rolled_back:return "rolled_back";case DurableStage::failed:return "failed";} return "failed";
}
inline std::optional<DurableStage> parse_stage(std::string_view s) {
    if(s=="prepared") return DurableStage::prepared;
    if(s=="applied") return DurableStage::applied;
    if(s=="verified") return DurableStage::verified;
    if(s=="committed") return DurableStage::committed;
    if(s=="rollback_pending") return DurableStage::rollback_pending;
    if(s=="rolled_back") return DurableStage::rolled_back;
    if(s=="failed") return DurableStage::failed;
    return std::nullopt;
}
class DurableStore {
    std::filesystem::path path_;
    static std::string checksum(std::string_view s){std::uint64_t h=1469598103934665603ULL;for(unsigned char c:s){h^=c;h*=1099511628211ULL;}std::ostringstream o;o<<std::hex<<std::setw(16)<<std::setfill('0')<<h;return o.str();}
    static std::vector<std::string> fields(const std::string& line){std::vector<std::string> f;std::size_t p=0;for(;;){auto n=line.find('\t',p);f.push_back(line.substr(p,n-p));if(n==std::string::npos)break;p=n+1;}return f;}
    static std::string payload(const DurableRecord& r){return r.transaction_id+'\t'+r.work_id+'\t'+std::string(stage_name(r.stage))+'\t'+std::to_string(r.sequence);}

    static void validate_field(std::string_view value){if(value.empty()||value.find_first_of("\t\n\r")!=std::string_view::npos)throw std::invalid_argument("invalid checkpoint field");}
    void sync_parent() const { auto parent=path_.parent_path(); if(parent.empty())parent="."; int fd=::open(parent.c_str(),O_RDONLY|O_DIRECTORY);if(fd<0)throw std::runtime_error("open checkpoint directory failed");if(::fsync(fd)!=0){int e=errno;::close(fd);throw std::runtime_error("fsync checkpoint directory failed: "+std::to_string(e));}::close(fd); }
public:
    explicit DurableStore(std::filesystem::path path):path_(std::move(path)){}
    const std::filesystem::path& path()const noexcept{return path_;}
    std::vector<DurableRecord> load(bool tolerate_torn_tail=false) const {
        std::vector<DurableRecord> out; std::ifstream in(path_,std::ios::binary); if(!in){if(!std::filesystem::exists(path_))return out;throw std::runtime_error("checkpoint read failed");}
        std::string content((std::istreambuf_iterator<char>(in)),{});const bool torn=!content.empty()&&content.back()!='\n';std::size_t pos=0,line_no=0;
        while(pos<content.size()){auto end=content.find('\n',pos);if(end==std::string::npos){if(tolerate_torn_tail&&torn)break;throw std::runtime_error("torn checkpoint tail");}++line_no;auto line=content.substr(pos,end-pos);pos=end+1;auto f=fields(line);if(f.size()!=4&&f.size()!=5)throw std::runtime_error("malformed checkpoint line "+std::to_string(line_no));auto st=parse_stage(f[2]);if(!st)throw std::runtime_error("unknown checkpoint stage");std::size_t used=0;auto seq=std::stoull(f[3],&used);if(used!=f[3].size())throw std::runtime_error("invalid checkpoint sequence");DurableRecord r{f[0],f[1],*st,static_cast<std::size_t>(seq)};if(f.size()==5&&checksum(payload(r))!=f[4])throw std::runtime_error("checkpoint integrity failure");out.push_back(std::move(r));}
        return out;
    }
    bool recover_torn_tail() const {
        if(!std::filesystem::exists(path_)) return false;
        std::ifstream in(path_,std::ios::binary);
        std::string content((std::istreambuf_iterator<char>(in)),{});
        if(content.empty()||content.back()=='\n') return false;
        (void)load(true);
        auto last=content.rfind('\n');
        std::uintmax_t keep=last==std::string::npos?0:static_cast<std::uintmax_t>(last+1);
        std::filesystem::resize_file(path_,keep);
        int fd=::open(path_.c_str(),O_RDWR);
        if(fd<0) throw std::runtime_error("checkpoint recovery open failed");
        if(::fsync(fd)!=0){::close(fd);throw std::runtime_error("checkpoint recovery fsync failed");}
        ::close(fd);sync_parent();return true;
    }
    void append(const DurableRecord& record) const {
        validate_field(record.transaction_id);validate_field(record.work_id);auto parent=path_.parent_path();if(!parent.empty())std::filesystem::create_directories(parent);
        int fd=::open(path_.c_str(),O_WRONLY|O_CREAT|O_APPEND,0600);if(fd<0)throw std::runtime_error("checkpoint open failed");std::string body=payload(record);std::string line=body+'\t'+checksum(body)+'\n';std::size_t off=0;while(off<line.size()){auto n=::write(fd,line.data()+off,line.size()-off);if(n<=0){::close(fd);throw std::runtime_error("checkpoint write failed");}off+=static_cast<std::size_t>(n);}if(::fsync(fd)!=0){::close(fd);throw std::runtime_error("checkpoint fsync failed");}::close(fd);sync_parent();
    }
    std::vector<DurableRecord> transaction(std::string_view id) const {std::vector<DurableRecord> out;for(const auto& r:load())if(r.transaction_id==id)out.push_back(r);return out;}
};
} // namespace rebuntu::control::checkpoints
