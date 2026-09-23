#include <providers/linux/backend.hpp>
namespace rebuntu::backend { Result DryRunBackend::execute(const Command&c){commands_.push_back(c);Result r;r.exit_code=0;r.stdout_text="dry-run:"+c.program;for(auto&a:c.arguments)r.stdout_text+=' '+a;return r;} }
