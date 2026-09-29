// rebuntu::system::observation — Memory Observation Adapter (Phase 7.10)
//
// This module observes memory and swap state through native Linux interfaces:
//   - /proc/meminfo — total, available, free, swap info
//   - PSI (/proc/pressure/memory) — pressure stall information

#include <chrono>
#include <fstream>

#include "../types.hpp"

namespace rebuntu::system::observation {

struct MemoryObservationAdapter : public ObservationAdapter {
    // Domain: kMemory
    ObservationDomain domain() const override { return ObservationDomain::kMemory; }

    core::Outcome observe(
        std::optional<ObservationIdentity> subject,
        std::vector<Observation>& out_observations) override
    {
        if (!subject.has_value()) {
            return core::Outcome::success();
        }

        auto acquired_at = std::chrono::system_clock::now();

        parse_meminfo(subject.value(), acquired_at, out_observations);

        // PSI observation is optional - may not be available on all kernels
        if (auto psi = read_psi()) {
            auto& obs = out_observations.emplace_back();
            obs.subject = subject.value();
            obs.field = "psi";
            obs.raw_value = *psi;
            obs.source = "procfs";
            obs.acquired_at = acquired_at;
            obs.quality = ObservationQuality::kObserved;
        }

        return core::Outcome::success();
    }

    std::pair<bool, std::chrono::milliseconds> is_fresh(
        const Observation&,
        const FreshnessPolicy&) override
    {
        // Memory state can change rapidly; consider fresh for 10 seconds
        return {true, std::chrono::seconds{10}};
    }

    core::Outcome invalidate() override { return {}; }

    private:
    static void parse_meminfo(ObservationIdentity subject, const std::chrono::system_clock::time_point& acquired_at,
                              std::vector<Observation>& out_observations)
    {
        std::ifstream f("/proc/meminfo");
        if (!f.is_open()) {
            auto& obs = out_observations.emplace_back();
            obs.subject = subject;
            obs.field = "meminfo";
            obs.error = core::Error{"E_PROC_MEMINFO", "Cannot open /proc/meminfo"};
            obs.source = "procfs";
            obs.acquired_at = acquired_at;
            return;
        }

        // Parse key fields: MemTotal, MemAvailable, SwapTotal, SwapFree
        uint64_t mem_total_kb = 0;
        uint64_t mem_available_kb = 0;
        uint64_t swap_total_kb = 0;
        uint64_t swap_free_kb = 0;

        std::string line;
        while (std::getline(f, line)) {
            if (line.empty()) continue;

            auto colon_pos = line.find(':');
            if (colon_pos == std::string::npos) continue;

            auto field_name = line.substr(0, colon_pos);
            auto after_colon = line.substr(colon_pos + 1);

            size_t value_start = after_colon.find_first_not_of(" \t");
            if (value_start == std::string::npos) continue;

            uint64_t value_kb = 0;
            bool parsed = false;
            for (size_t i = value_start; i < after_colon.size(); ++i) {
                char c = after_colon[i];
                if (isdigit(c)) {
                    value_kb = value_kb * 10 + (c - '0');
                    parsed = true;
                } else if (parsed && (c == 'k' || c == 'K')) {
                    break;
                } else if (!isspace(c)) {
                    break;
                }
            }

            if (field_name == "MemTotal") {
                mem_total_kb = value_kb;
            } else if (field_name == "MemAvailable") {
                mem_available_kb = value_kb;
            } else if (field_name == "SwapTotal") {
                swap_total_kb = value_kb;
            } else if (field_name == "SwapFree") {
                swap_free_kb = value_kb;
            }
        }

        f.close();

        // Memory total
        auto& total_obs = out_observations.emplace_back();
        total_obs.subject = subject;
        total_obs.field = "total_kb";
        total_obs.raw_value = std::to_string(mem_total_kb);
        total_obs.normalized_value = std::to_string(mem_total_kb);
        total_obs.source = "procfs";
        total_obs.acquired_at = acquired_at;
        total_obs.quality = ObservationQuality::kObserved;

        // Memory available (may be unknown on older kernels)
        auto& avail_obs = out_observations.emplace_back();
        avail_obs.subject = subject;
        avail_obs.field = "available_kb";
        if (mem_available_kb > 0) {
            avail_obs.raw_value = std::to_string(mem_available_kb);
            avail_obs.normalized_value = std::to_string(mem_available_kb);
        } else {
            avail_obs.error = core::Error{"E_MEMAVAIL_UNKNOWN", "MemAvailable field not found"};
        }
        avail_obs.source = "procfs";
        avail_obs.acquired_at = acquired_at;
        avail_obs.quality = ObservationQuality::kObserved;

        // Swap total
        auto& swap_total_obs = out_observations.emplace_back();
        swap_total_obs.subject = subject;
        swap_total_obs.field = "swap_total_kb";
        swap_total_obs.raw_value = std::to_string(swap_total_kb);
        swap_total_obs.normalized_value = std::to_string(swap_total_kb);
        swap_total_obs.source = "procfs";
        swap_total_obs.acquired_at = acquired_at;
        swap_total_obs.quality = ObservationQuality::kObserved;

        // Swap free
        auto& swap_free_obs = out_observations.emplace_back();
        swap_free_obs.subject = subject;
        swap_free_obs.field = "swap_free_kb";
        swap_free_obs.raw_value = std::to_string(swap_free_kb);
        swap_free_obs.normalized_value = std::to_string(swap_free_kb);
        swap_free_obs.source = "procfs";
        swap_free_obs.acquired_at = acquired_at;
        swap_free_obs.quality = ObservationQuality::kObserved;
    }

    static std::optional<std::string> read_psi()
    {
        // PSI is available at /proc/pressure/memory
        const char* path = "/proc/pressure/memory";
        std::ifstream f(path);
        if (!f.is_open()) return std::nullopt;

        std::string line;
        std::getline(f, line);
        f.close();

        // PSI format: "some 0.00 0.00 0.00" or "full 0.00 0.00 0.00"
        return line.empty() ? std::nullopt : std::make_optional(line);
    }
};

inline std::unique_ptr<ObservationAdapter> make_memory_observation_adapter() {
    return std::make_unique<MemoryObservationAdapter>();
}

} // namespace rebuntu::system::observation