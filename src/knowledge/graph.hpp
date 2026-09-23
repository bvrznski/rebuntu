#pragma once
#include <map>
#include <set>
#include <string>
#include <vector>
namespace rebuntu::knowledge { struct Edge{std::string from,relation,to;}; class Graph{public:void relate(Edge);std::vector<Edge> outgoing(const std::string&)const;std::set<std::string> reachable(const std::string&,std::size_t depth=4)const;private:std::multimap<std::string,Edge>edges_;}; }
