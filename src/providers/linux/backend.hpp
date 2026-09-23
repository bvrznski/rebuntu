#pragma once
#include <chrono>
#include <string>
#include <vector>
namespace rebuntu::backend {
struct Command{std::string program;std::vector<std::string> arguments;bool privileged{false};std::chrono::milliseconds timeout{30000};};
struct Result{int exit_code{-1};std::string stdout_text,stderr_text;bool timed_out{false};};
class Backend{public:virtual ~Backend()=default;virtual Result execute(const Command&)=0;};
class DryRunBackend final:public Backend{public:Result execute(const Command&)override;const std::vector<Command>& commands()const{return commands_;}private:std::vector<Command> commands_;};
}
