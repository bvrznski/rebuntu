#pragma once
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>
namespace rebuntu::shell {
enum class Intent { query, mutate, execute, explain, unknown }; enum class Scope { automatic_scope,user,session,system };
struct CommandIR { std::string verb, object; std::vector<std::string> arguments, qualifiers; std::map<std::string,std::string> options; Intent intent{Intent::unknown}; Scope scope{Scope::automatic_scope}; bool native_fallback{false}; };
struct Resolution { bool ok{false}; CommandIR command; std::string error; std::vector<std::string> alternatives; };
class Vocabulary { public: Vocabulary(); bool verb(std::string_view)const; bool predicate(std::string_view)const; bool object(std::string_view)const; std::vector<std::string> complete(std::string_view)const; private:std::set<std::string> verbs_,predicates_,objects_;};
class Parser { public: explicit Parser(Vocabulary v={}):v_(std::move(v)){} Resolution parse(std::string_view)const; private:Vocabulary v_;};
std::string render_json(const CommandIR&); std::string render_human(const CommandIR&);
}