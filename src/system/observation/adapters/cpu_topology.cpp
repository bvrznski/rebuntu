// rebuntu::system::observation — CPU Topology Observation Adapter (Phase 7.10)
//
// This module observes CPU topology, load counters, frequency governors through
// native Linux interfaces: /proc/cpuinfo and sysfs cpufreq.

#include <chrono>
#include <fstream>

#include "../types.hpp"

namespace rebuntu::system::observation {

struct CPUTopologyObservationAdapter : public ObservationAdapter {
    // Domain: kCPU
    ObservationDomain domain() const override { return ObservationDomain::kCPU; }

    core::Outcome observe(
        std::optional<ObservationIdentity> subject,
        std::vector<Observation>& out_observations) override
    {
        if (!subject.has_value()) {
            return core::Outcome::success();
        }

        auto& obs = out_observations.emplace_back();
        obs.subject = subject.value();
        obs.source = "procfs";
        obs.acquired_at = std::chrono::system_clock::now();

        parse_cpuinfo(obs);

        if (auto gov = read_cpufreq_governor()) {
            obs.field = "cpufreq_governor";
            obs.raw_value = std::move(gov);
            obs.quality = ObservationQuality::kObserved;
        } else {
            obs.error = core::Error{"E_CPUFREQ_GOVERNOR_ABSENT", "cpufreq governor not present"};
            obs.quality = ObservationQuality::kUnknown;
        }

        return core::Outcome::success();
    }

    std::pair<bool, std::chrono::milliseconds> is_fresh(
        const Observation&,
        const FreshnessPolicy&) override
    {
        return {true, std::chrono::milliseconds{0}};
    }

    core::Outcome invalidate() override { return {}; }

private:
    static void parse_cpuinfo(Observation& obs)
    {
        std::ifstream f("/proc/cpuinfo");
        if (!f.is_open()) {
            obs.error = core::Error{"E_PROC_CPUINFO", "Cannot open /proc/cpuinfo"};
            return;
        }

        size_t online_count = 0;

        std::string line;
        while (std::getline(f, line)) {
            if (line.empty()) continue;

            auto pos = line.find("processor");
            if (pos == std::string::npos) continue;

            size_t num_start = line.find_first_not_of(' ', pos + 10);
            if (num_start == std::string::npos) continue;

            while (num_start < line.size() && isdigit(line[num_start])) {
                ++num_start;
            }

            auto online_pos = line.find("online");
            if (online_pos != std::string::npos) {
                size_t val_start = line.find_first_not_of(' ', online_pos + 7);
                if (val_start == std::string::npos) continue;

                size_t after_online = val_start + 6;
                while (after_online < line.size() && isspace(line[after_online])) {
                    ++after_online;
                }

                if (after_online < line.size() && line.substr(after_online, 3) == ": 1") {
                    ++online_count;
                }
            } else {
                ++online_count;
            }
        }

        f.close();

        obs.field = "online_cpus";
        obs.raw_value = std::to_string(online_count);
        obs.normalized_value = std::to_string(static_cast<int>(online_count));
        obs.quality = ObservationQuality::kObserved;
    }

    static std::optional<std::string> read_cpufreq_governor()
    {
        const char* path = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor";
        std::ifstream f(path);
        if (!f.is_open()) return std::nullopt;

        std::string line, governor;
        while (std::getline(f, line)) {
            auto start = line.find_first_not_of(" \t\r\n");
            auto end   = line.find_last_not_of(" \t\r\n");
            if (start == std::string::npos) return std::nullopt;
            governor = line.substr(start, end - start + 1);

            std::transform(governor.begin(), governor.end(), governor.begin(),
                [](unsigned char c){ return std::tolower(c); });

            if (governor == "performance") {
                return "performance";
            } else if (governor == "powersave" || governor == "ondemand" ||
                       governor == "schedutil" || governor == "conservative") {
                return "balanced";
            }
        }

        f.close();
        return std::nullopt;
    }
};

inline std::unique_ptr<ObservationAdapter> make_cpu_topology_adapter() {
    return std::make_unique<CPUTopologyObservationAdapter>();
}

} // namespace rebuntu::system::observation