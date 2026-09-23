#include "operations.hpp"
namespace rebuntu::runtime::installation::lifecycle {
std::vector<Action> plan_removal(Kind k,const std::vector<Artifact>& as){std::vector<Action> o;if(k!=Kind::uninstall&&k!=Kind::purge)return o;for(auto&a:as){if(!a.rebuntu_owned)continue;if(a.user_authored&&k!=Kind::purge)continue;o.push_back({"remove",a.path});}return o;}
}
