#pragma once
#include <optional>
#include <string>
#include <vector>
namespace rebuntu::runtime::preferences {
struct PreferenceLayer { std::string source; int precedence{}; std::optional<std::string> value; };
struct PreferenceResolution { std::optional<std::string> requested; std::optional<std::string> effective; std::string source; std::string explanation; bool satisfied{false}; };
PreferenceResolution resolve(const std::vector<PreferenceLayer>& layers, const std::vector<std::string>& available, const std::optional<std::string>& fallback, const std::vector<std::string>& forbidden = {});
}
