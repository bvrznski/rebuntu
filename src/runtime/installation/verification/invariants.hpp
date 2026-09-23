#pragma once
#include <functional>
#include <string>
#include <vector>
namespace rebuntu::runtime::installation::verification {
struct Invariant { std::string id; std::function<bool()> check; };
struct Report { bool usable{false}; std::vector<std::string> failed; };
Report verify(const std::vector<Invariant>& invariants);
}
