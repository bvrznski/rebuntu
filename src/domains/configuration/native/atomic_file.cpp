#include <domains/configuration/atomic_file.hpp>
#include <cerrno>
#include <fcntl.h>
#include <fstream>
#include <stdexcept>
#include <system_error>
#include <unistd.h>
namespace fs=std::filesystem;
namespace rebuntu::domains::configuration {
std::string AtomicFile::read(const fs::path&p){std::ifstream f(p,std::ios::binary);if(!f)throw std::system_error(errno,std::generic_category(),"open "+p.string());return {std::istreambuf_iterator<char>(f),{}};}
static void write_all(int fd,const std::string&s){size_t n=0;while(n<s.size()){auto r=::write(fd,s.data()+n,s.size()-n);if(r<0){if(errno==EINTR)continue;throw std::system_error(errno,std::generic_category(),"write");}n+=static_cast<size_t>(r);}}
WriteResult AtomicFile::replace(const fs::path&p,const std::string&content,bool keep){
 if(p.empty()||p.filename().empty())throw std::invalid_argument("configuration target must be a file");
 std::error_code ec; if(fs::exists(p,ec)&&read(p)==content)return{};
 fs::create_directories(p.parent_path().empty()?fs::path("."):p.parent_path());
 std::optional<fs::path> backup; fs::perms perms=fs::perms::owner_read|fs::perms::owner_write;
 if(fs::exists(p)){perms=fs::status(p).permissions();if(keep){backup=p;*backup += ".rebuntu.bak";fs::copy_file(p,*backup,fs::copy_options::overwrite_existing);}}
 auto tmp=p; tmp += ".rebuntu.tmp."+std::to_string(::getpid());
 int fd=::open(tmp.c_str(),O_WRONLY|O_CREAT|O_EXCL|O_CLOEXEC,0600);if(fd<0)throw std::system_error(errno,std::generic_category(),"create temp");
 try{write_all(fd,content);if(::fsync(fd))throw std::system_error(errno,std::generic_category(),"fsync");::close(fd);fd=-1;fs::permissions(tmp,perms);fs::rename(tmp,p);int dfd=::open((p.parent_path().empty()?fs::path("."):p.parent_path()).c_str(),O_RDONLY|O_DIRECTORY|O_CLOEXEC);if(dfd>=0){::fsync(dfd);::close(dfd);}}
 catch(...){if(fd>=0)::close(fd);fs::remove(tmp);throw;}
 return{true,backup};
}
}
