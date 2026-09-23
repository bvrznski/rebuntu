#include "runtime.hpp"
#include <algorithm>
#include <cctype>
#include <utility>
namespace rebuntu::operator_ui::gui {
namespace { bool terminal(ActionState s){return s==ActionState::succeeded||s==ActionState::failed||s==ActionState::cancelled;} }
bool GuiRuntime::register_action(Action a){ if(a.id.empty()||a.label.empty()||a.intent.empty()) return false; return actions_.emplace(a.id,std::move(a)).second; }
const Action* GuiRuntime::action(const std::string& id) const noexcept { auto i=actions_.find(id); return i==actions_.end()?nullptr:&i->second; }
bool GuiRuntime::request_execution(const std::string& id){ auto i=actions_.find(id); if(i==actions_.end()||terminal(i->second.state)||!i->second.policy_allowed)return false; auto&a=i->second; if(a.risk==Risk::destructive&&!a.confirmed){a.state=ActionState::awaiting_confirmation;return false;} a.state=ActionState::authorized; return true; }
bool GuiRuntime::confirm(const std::string& id){auto i=actions_.find(id);if(i==actions_.end()||i->second.state!=ActionState::awaiting_confirmation||!i->second.policy_allowed)return false;i->second.confirmed=true;i->second.state=ActionState::authorized;return true;}
bool GuiRuntime::mark_dispatched(const std::string& id){auto i=actions_.find(id);if(i==actions_.end()||i->second.state!=ActionState::authorized)return false;i->second.state=ActionState::dispatched;view_.busy=true;return true;}
bool GuiRuntime::complete(const std::string& id,bool ok,Evidence e){auto i=actions_.find(id);if(i==actions_.end()||i->second.state!=ActionState::dispatched||e.source.empty())return false;i->second.evidence.push_back(std::move(e));i->second.state=ok?ActionState::succeeded:ActionState::failed;view_.busy=false;return true;}
bool GuiRuntime::cancel(const std::string& id){auto i=actions_.find(id);if(i==actions_.end()||terminal(i->second.state)||i->second.state==ActionState::dispatched)return false;i->second.state=ActionState::cancelled;return true;}
bool GuiRuntime::navigate(std::string r){if(r.empty()||r.find("..")!=std::string::npos)return false;view_.route=std::move(r);view_.selected.reset();return true;}
bool GuiRuntime::select(std::string id){if(!actions_.contains(id))return false;view_.selected=std::move(id);return true;}
void GuiRuntime::set_query(std::string q){view_.query=std::move(q);}
void GuiRuntime::notify(Notification n){if(n.id.empty()||n.message.empty())return;notifications_.push_back(std::move(n));while(notifications_.size()>100)notifications_.pop_front();}
std::vector<std::string> GuiRuntime::searchable_actions() const {std::vector<std::string> out;std::string q=view_.query;std::transform(q.begin(),q.end(),q.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});for(const auto&[id,a]:actions_){std::string h=a.label+" "+a.intent+" "+a.target;std::transform(h.begin(),h.end(),h.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});if(q.empty()||h.find(q)!=std::string::npos)out.push_back(id);}std::sort(out.begin(),out.end());return out;}
}
