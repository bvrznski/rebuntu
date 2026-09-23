#include <runtime/state/persistence/journal.hpp>
#include <fstream>
#include <sstream>
namespace rebuntu::persistence {
static std::string esc(std::string s){for(char&c:s)if(c=='\t'||c=='\n'||c=='\r')c=' ';return s;}
Journal::Journal(std::filesystem::path p):path_(std::move(p)){if(path_.has_parent_path())std::filesystem::create_directories(path_.parent_path());}
void Journal::append(const JournalEntry&e){std::scoped_lock lock(mutex_);std::ofstream f(path_,std::ios::app);if(!f)throw std::runtime_error("cannot open journal");f<<esc(e.transaction_id)<<'\t'<<esc(e.domain)<<'\t'<<esc(e.target)<<'\t'<<esc(e.action)<<'\t'<<esc(e.before_value)<<'\t'<<esc(e.after_value)<<'\t'<<esc(e.status)<<'\n';f.flush();if(!f)throw std::runtime_error("cannot persist journal");}
std::vector<JournalEntry> Journal::load()const{std::scoped_lock lock(mutex_);std::ifstream f(path_);std::vector<JournalEntry> out;std::string line;while(std::getline(f,line)){std::istringstream s(line);JournalEntry e;std::getline(s,e.transaction_id,'\t');std::getline(s,e.domain,'\t');std::getline(s,e.target,'\t');std::getline(s,e.action,'\t');std::getline(s,e.before_value,'\t');std::getline(s,e.after_value,'\t');std::getline(s,e.status,'\t');if(!e.transaction_id.empty())out.push_back(std::move(e));}return out;}
std::optional<JournalEntry> Journal::latest(const std::string&t)const{auto v=load();for(auto it=v.rbegin();it!=v.rend();++it)if(it->target==t)return *it;return std::nullopt;}
}
