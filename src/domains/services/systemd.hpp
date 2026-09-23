#pragma once
#include <map>
#include <string>
namespace rebuntu::domains::service {struct UnitState{std::string id,load,active,sub,unit_file;};UnitState parse_systemctl_show(const std::string&);bool valid_unit_name(const std::string&);}
