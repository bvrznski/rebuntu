// rebuntu::modules::cpu_memory_thermal_monitor — CPU / Memory / Thermal Monitor Implementation (Phase 5.9)
//
// This module provides comprehensive resource monitoring for Rebuntu:
//   - CPU utilization, load average, run queue pressure
//   - Memory availability, swap activity, PSI (Pressure Stall Information)
//   - OOM events, thermal temperature, thermal throttling

#include "monitor.hpp"
#include <system/core/contracts.hpp>

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

namespace rebuntu::modules::cpu_memory_thermal_monitor {

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<ResourceMonitor> make_resource_monitor(
    const ResourceMonitorConfig& config) {
    return std::make_unique<ResourceMonitor>(config);
}

// ============================================================================
// ResourceMonitor implementation
// ============================================================================

ResourceMonitor::ResourceMonitor(ResourceMonitorConfig config)
    : config_(std::move(config)),
      running_(false),
      cpu_assessment_(),
      memory_assessment_(),
      thermal_assessment_(),
      events_(std::make_unique<EventRegistry>()) {
    
    // Initialize assessments with proper states
    cpu_assessment_.state = ResourceState::kUnknown;
    memory_assessment_.state = ResourceState::kUnknown;
    thermal_assessment_.state = ResourceState::kUnknown;
}

ResourceMonitor::~ResourceMonitor() {
    stop();
}

core::Outcome ResourceMonitor::start() {
    if (running_) {
        return core::Outcome::success();
    }
    
    metrics_.started_at = std::chrono::system_clock::now();
    history_window_ = HistoryWindow{
        .window_start = std::chrono::system_clock::now(),
        .cpu_samples{},
        .memory_samples{},
        .window_minutes = std::chrono::minutes(5)
    };
    
    running_ = true;
    return core::Outcome::success();
}

core::Outcome ResourceMonitor::stop() {
    if (!running_) {
        return core::Outcome::success();
    }
    
    running_ = false;
    return core::Outcome::success();
}

void ResourceMonitor::set_config(const ResourceMonitorConfig& config) {
    config_ = config;
}

ResourceMonitorMetrics ResourceMonitor::metrics() const {
    return metrics_;
}

// ============================================================================
// Native acquisition methods
// ============================================================================

std::optional<CPUResource> ResourceMonitor::acquire_cpu_resource() {
    CPUResource result;
    
    // Try to read /proc/stat for CPU statistics
    std::ifstream stat_file("/proc/stat");
    if (!stat_file.is_open()) {
        metrics_.source_metrics["/proc/stat"].failures++;
        return std::nullopt;
    }
    
    metrics_.source_metrics["/proc/stat"].acquisitions++;
    auto acquire_start = std::chrono::steady_clock::now();
    
    // Read and parse first line (cpu line)
    std::string line;
    if (!std::getline(stat_file, line) || line.empty()) {
        metrics_.source_metrics["/proc/stat"].failures++;
        return std::nullopt;
    }
    
    // Parse: "cpu  user nice system idle iowait irq softirq steal guest guest_nice"
    std::istringstream iss(line);
    std::string cpu_label;
    if (!(iss >> cpu_label)) {
        metrics_.source_metrics["/proc/stat"].failures++;
        return std::nullopt;
    }
    
    // Parse numeric values
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
    if (!(iss >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal)) {
        metrics_.source_metrics["/proc/stat"].failures++;
        return std::nullopt;
    }
    
    // Calculate totals
    unsigned long long total_idle = idle + iowait;
    unsigned long long total_user = user + nice + steal;
    unsigned long long total_system = system + irq + softirq;
    unsigned long long total = total_user + total_system + total_idle;
    
    if (total > 0) {
        result.user_percent = static_cast<double>(total_user * 100) / total;
        result.system_percent = static_cast<double>(total_system * 100) / total;
        result.idle_percent = static_cast<double>(total_idle * 100) / total;
    }
    
    result.iowait_percent = (total > 0) ? 
        static_cast<double>(iowait * 100) / total : 0.0;
    result.interrupt_percent = (total > 0) ?
        static_cast<double>(irq * 100) / total : 0.0;
    result.softirq_percent = (total > 0) ?
        static_cast<double>(softirq * 100) / total : 0.0;
    
    result.measured_at = std::chrono::system_clock::now();
    auto acquire_end = std::chrono::steady_clock::now();
    result.measurement_window_ms = 
        std::chrono::duration_cast<std::chrono::milliseconds>(acquire_end - acquire_start);
    
    // Try to read /proc/loadavg for load average
    std::ifstream load_file("/proc/loadavg");
    if (load_file.is_open()) {
        double avg1, avg5, avg15;
        int running_procs, total_procs;
        
        if (load_file >> avg1 >> avg5 >> avg15 
                >> running_procs >> total_procs) {
            result.load_avg_1min = avg1;
            result.load_avg_5min = avg5;
            result.load_avg_15min = avg15;
            result.running_processes = running_procs;
            result.total_processes = total_procs;
        }
    }
    
    // Try to read /proc/cpuinfo for CPU count
    std::ifstream cpuinfo("/proc/cpuinfo");
    if (cpuinfo.is_open()) {
        int logical_count = 0;
        std::set<int> physical_ids;
        
        std::string line;
        while (std::getline(cpuinfo, line)) {
            if (line.starts_with("processor")) {
                logical_count++;
            } else if (line.starts_with("physical id")) {
                size_t colon_pos = line.find(':');
                if (colon_pos != std::string::npos) {
                    try {
                        physical_ids.insert(std::stoi(line.substr(colon_pos + 1)));
                    } catch (...) {}
                }
            }
        }
        
        result.logical_cpu_count = logical_count;
        result.physical_cpu_count = static_cast<int>(physical_ids.size());
    }
    
    return result;
}

std::optional<MemoryResource> ResourceMonitor::acquire_memory_resource() {
    MemoryResource result;
    
    std::ifstream meminfo("/proc/meminfo");
    if (!meminfo.is_open()) {
        metrics_.source_metrics["/proc/meminfo"].failures++;
        return std::nullopt;
    }
    
    metrics_.source_metrics["/proc/meminfo"].acquisitions++;
    auto acquire_start = std::chrono::steady_clock::now();
    
    // Parse meminfo lines
    std::string line;
    while (std::getline(meminfo, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        size_t colon_pos = line.find(':');
        if (colon_pos == std::string::npos) continue;
        
        std::string key = line.substr(0, colon_pos);
        std::string value_part = line.substr(colon_pos + 1);
        
        // Remove leading whitespace
        size_t val_start = value_part.find_first_not_of(" \t");
        if (val_start != std::string::npos) {
            value_part = value_part.substr(val_start);
        }
        
        // Parse value and unit (kB)
        int64_t value_kB = 0;
        if (!value_part.empty() && value_part.back() == 'k') {
            try {
                value_kB = std::stoll(value_part.substr(0, value_part.length() - 1));
            } catch (...) {}
        }
        
        // Convert to bytes
        uint64_t value_bytes = static_cast<uint64_t>(value_kB) * 1024;
        
        if (key == "MemTotal") {
            result.total_bytes = value_bytes;
        } else if (key == "MemAvailable" || key == "MemFree") {
            // Prefer MemAvailable, fall back to MemFree
            if (key == "MemAvailable" || result.available_bytes == 0) {
                result.available_bytes = value_bytes;
            }
        } else if (key == "Buffers") {
            result.buffers_bytes = value_bytes;
        } else if (key == "Cached") {
            result.cached_bytes = value_bytes;
        } else if (key == "SwapTotal") {
            result.swap_total_bytes = value_bytes;
        } else if (key == "SwapFree") {
            result.swap_free_bytes = value_bytes;
        }
    }
    
    // Calculate derived values
    result.used_bytes = result.total_bytes - result.available_bytes;
    result.free_bytes = result.available_bytes;  // Simplified
    
    if (result.swap_total_bytes > 0) {
        result.swap_used_bytes = result.swap_total_bytes - result.swap_free_bytes;
    }
    
    result.measured_at = std::chrono::system_clock::now();
    auto acquire_end = std::chrono::steady_clock::now();
    result.measurement_window_ms = 
        std::chrono::duration_cast<std::chrono::milliseconds>(acquire_end - acquire_start);
    
    return result;
}

std::optional<ThermalResource> ResourceMonitor::acquire_thermal_resource() {
    ThermalResource result;
    
    // Scan /sys/class/thermal/ for thermal zones
    namespace fs = std::filesystem;
    
    std::error_code ec;
    fs::path thermal_path("/sys/class/thermal");
    
    if (!fs::exists(thermal_path, ec)) {
        metrics_.source_metrics["/sys/class/thermal"].failures++;
        return std::nullopt;
    }
    
    metrics_.source_metrics["/sys/class/thermal"].acquisitions++;
    
    for (const auto& entry : fs::directory_iterator(thermal_path, ec)) {
        if (ec) break;
        
        const auto& path = entry.path();
        std::string zone_name = path.filename().string();
        
        // Try to read temperature
        std::ifstream temp_file(path / "temp");
        if (!temp_file.is_open()) continue;
        
        int64_t temp_mCelsius;
        if (temp_file >> temp_mCelsius) {
            ThermalResource::TemperatureReading reading;
            reading.zone_name = zone_name;
            reading.temperature_celsius = static_cast<double>(temp_mCelsius) / 1000.0;
            reading.measured_at = std::chrono::system_clock::now();
            result.temperatures.push_back(std::move(reading));
        }
        
        // Try to read trip points
        fs::path trips_path = path / "trip_points";
        if (fs::exists(trips_path, ec)) {
            for (const auto& trip : fs::directory_iterator(trips_path, ec)) {
                if (ec) break;
                
                std::ifstream trip_file(trip.path());
                if (!trip_file.is_open()) continue;
                
                int64_t threshold_mCelsius;
                if (trip_file >> threshold_mCelsius) {
                    // Find the matching temperature reading
                    for (auto& r : result.temperatures) {
                        if (r.zone_name == zone_name) {
                            if (trip.path().filename().string() == "temp_crit") {
                                r.critical_threshold_celsius = 
                                    static_cast<double>(threshold_mCelsius) / 1000.0;
                            } else if (trip.path().filename().string() == "temp_warning") {
                                r.warning_threshold_celsius =
                                    static_cast<double>(threshold_mCelsius) / 1000.0;
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Check thermal throttling state
    std::ifstream throttling_file("/sys/devices/system/cpu/cpu0/cpufreq/thermal_pressure");
    if (throttling_file.is_open()) {
        uint32_t pressure;
        if (throttling_file >> pressure) {
            result.throttling = ThermalResource::ThrottlingState{};
            result.throttling->is_throttled = (pressure > 0);
            result.throttling->last_throttle_at = std::chrono::system_clock::now();
        }
    }
    
    // Try to get cooling device state
    fs::path cooling_path("/sys/class/thermal");
    for (const auto& entry : fs::directory_iterator(cooling_path, ec)) {
        if (ec) break;
        
        const auto& path = entry.path();
        std::string zone_name = path.filename().string();
        
        // Check for cooling devices associated with this thermal zone
        fs::path device_path = path / "device" / "power";
        if (fs::exists(device_path, ec)) {
            std::ifstream max_state_file(device_path / "max_state");
            std::ifstream cur_state_file(device_path / "cur_state");
            
            int max_state = 0, cur_state = 0;
            if (max_state_file >> max_state && cur_state_file >> cur_state) {
                ThermalResource::CoolingDevice device;
                device.name = zone_name + "_cooling";
                device.max_state = max_state;
                device.current_state = cur_state;
                device.measured_at = std::chrono::system_clock::now();
                result.cooling_devices.push_back(std::move(device));
            }
        }
    }
    
    if (!result.temperatures.empty()) {
        result.measured_at = std::chrono::system_clock::now();
        return result;
    }
    
    // No thermal data found
    metrics_.source_metrics["/sys/class/thermal"].failures++;
    return std::nullopt;
}

// ============================================================================
// Assessment methods
// ============================================================================

CPUAssessment ResourceMonitor::assess_cpu(std::chrono::system_clock::time_point now) {
    CPUAssessment assessment;
    
    // Acquire current data
    auto cpu_data = acquire_cpu_resource();
    
    if (!cpu_data.has_value()) {
        assessment.state = ResourceState::kUnknown;
        return assessment;
    }
    
    assessment.current = std::move(*cpu_data);
    assessment.assessed_at = now;
    
    // Check utilization state
    double user_util = assessment.current->user_percent;
    if (user_util >= config_.cpu_utilization_critical_percent) {
        assessment.state = ResourceState::kCritical;
    } else if (user_util >= config_.cpu_utilization_warning_percent) {
        assessment.state = ResourceState::kPressured;
    } else if (user_util > 0) {
        assessment.state = ResourceState::kNormal;
    }
    
    // Load assessment
    assessment.load = CPUAssessment::LoadAssessment{};
    auto& load = *assessment.load;
    
    double load_avg = assessment.current->load_avg_1min;
    int cpu_count = assessment.current->logical_cpu_count.value_or(1);
    load.load_per_cpu = load_avg / static_cast<double>(cpu_count);
    load.is_high_load = (load_avg > cpu_count);
    
    // Check if load is increasing
    if (history_window_.has_value() && !history_window_->cpu_samples.empty()) {
        const auto& prev_sample = history_window_->cpu_samples.back();
        double prev_avg = prev_sample.load_avg_1min;
        load.is_increasing = (load_avg > prev_avg * 1.05);  // 5% increase
        if (prev_avg > 0) {
            load.load_trend_percent_change = ((load_avg - prev_avg) / prev_avg) * 100.0;
        }
    }
    
    return assessment;
}

MemoryAssessment ResourceMonitor::assess_memory(std::chrono::system_clock::time_point now) {
    MemoryAssessment assessment;
    
    // Acquire current data
    auto mem_data = acquire_memory_resource();
    
    if (!mem_data.has_value()) {
        assessment.state = ResourceState::kUnknown;
        return assessment;
    }
    
    assessment.current = std::move(*mem_data);
    assessment.assessed_at = now;
    
    // Calculate memory usage percentage
    double used_percent = 0.0;
    if (assessment.current->total_bytes > 0) {
        used_percent = static_cast<double>(assessment.current->used_bytes * 100) / 
                       assessment.current->total_bytes;
    }
    
    double available_percent = 100.0 - used_percent;
    
    // Memory pressure assessment (from PSI or utilization)
    bool is_under_pressure = false;
    
    if (config_.enable_psi_monitoring) {
        // Check memory PSI thresholds
        auto psi_data = acquire_memory_resource();  // Re-acquire to check for PSI
        
        if (psi_data->memory_full_stall_percent_10s.has_value() &&
            *psi_data->memory_full_stall_percent_10s > config_.memory_pressure_warning_percent_10s) {
            is_under_pressure = true;
        }
    }
    
    // Determine state
    if (used_percent >= 95.0 || is_under_pressure) {
        assessment.state = ResourceState::kCritical;
    } else if (used_percent >= 85.0 || is_under_pressure) {
        assessment.state = ResourceState::kConstrained;
    } else if (used_percent >= config_.swap_utilization_warning_percent / 2.0) {
        assessment.state = ResourceState::kPressured;
    } else {
        assessment.state = ResourceState::kNormal;
    }
    
    // Swap assessment
    assessment.swap = MemoryAssessment::SwapAssessment{};
    auto& swap = *assessment.swap;
    
    if (assessment.current->swap_total_bytes > 0) {
        swap.is_swap_used = true;
        swap.swap_utilization_percent = 
            static_cast<double>(assessment.current->swap_used_bytes * 100) /
            assessment.current->swap_total_bytes;
        swap.is_swapping_heavily = (swap.swap_utilization_percent > config_.swap_utilization_warning_percent);
    }
    
    // OOM risk assessment
    assessment.oom_risk = MemoryAssessment::OOMRisk{};
    auto& oom = *assessment.oom_risk;
    
    oom.available_memory_percent = available_percent;
    
    if (available_percent < 5.0) {
        oom.risk_level = "high";
        oom.is_oom_active = true;  // Very low memory indicates recent OOM activity
    } else if (available_percent < 10.0) {
        oom.risk_level = "medium";
    } else {
        oom.risk_level = "low";
    }
    
    return assessment;
}

ThermalAssessment ResourceMonitor::assess_thermal(std::chrono::system_clock::time_point now) {
    ThermalAssessment assessment;
    
    // Acquire current data
    auto thermal_data = acquire_thermal_resource();
    
    if (!thermal_data.has_value()) {
        assessment.state = ResourceState::kUnknown;
        return assessment;
    }
    
    assessment.assessed_at = now;
    assessment.temperatures = std::move(thermal_data->temperatures);
    
    // Find maximum temperature
    double max_temp = 0.0;
    for (const auto& t : assessment.temperatures) {
        if (t.temperature_celsius > max_temp) {
            max_temp = t.temperature_celsius;
        }
    }
    
    // Throttling assessment
    if (thermal_data->throttling.has_value()) {
        assessment.throttling = ThermalAssessment::ThrottlingAssessment{};
        auto& throttling = *assessment.throttling;
        
        throttling.is_throttled = thermal_data->throttling->is_throttled;
        throttling.throttle_count_in_window = thermal_data->throttling->throttle_count;
        
        // Adjust state if throttled
        if (throttling.is_throttled) {
            assessment.state = ResourceState::kCritical;
        }
    }
    
    // Cooling assessment
    assessment.cooling = ThermalAssessment::CoolingAssessment{};
    auto& cooling = *assessment.cooling;
    
    for (const auto& cd : thermal_data->cooling_devices) {
        if (cd.current_state > 0) {
            cooling.cooling_active = true;
            if (cd.max_state > cooling.max_cooling_state) {
                cooling.max_cooling_state = cd.max_state;
            }
        }
    }
    
    // Determine state based on temperature
    double warning_threshold = static_cast<double>(config_.temperature_warning_celsius);
    double critical_threshold = static_cast<double>(config_.temperature_critical_celsius);
    
    if (max_temp >= critical_threshold) {
        assessment.state = ResourceState::kCritical;
    } else if (max_temp >= warning_threshold) {
        assessment.state = ResourceState::kPressured;
    } else if (max_temp > 0) {
        assessment.state = ResourceState::kNormal;
    }
    
    return assessment;
}

// ============================================================================
// Main assessment entry point
// ============================================================================

ResourceMonitorResult ResourceMonitor::assess_resources(
    std::chrono::system_clock::time_point assessment_time) {
    
    ResourceMonitorResult result;
    auto start_time = std::chrono::steady_clock::now();
    
    // Record evidence from acquisition
    struct EvidenceRecord {
        std::string source_path;
        bool success;
        std::optional<std::chrono::milliseconds> duration_ms;
    };
    std::vector<EvidenceRecord> evidence_records;
    
    // Assess CPU
    auto cpu_result = assess_cpu(assessment_time);
    if (cpu_result.current.has_value()) {
        result.cpu_assessment = cpu_result;
        
        // Record evidence
        evidence_records.push_back({"/proc/stat", true, 
            std::chrono::duration_cast<std::chrono::milliseconds>(
                cpu_result.current->measurement_window_ms.value_or(std::chrono::milliseconds(0)))});
    } else {
        evidence_records.push_back({"/proc/stat", false, std::nullopt});
        result.cpu_assessment = make_initial_cpu_assessment();
    }
    
    // Assess memory
    auto mem_result = assess_memory(assessment_time);
    if (mem_result.current.has_value()) {
        result.memory_assessment = mem_result;
        
        evidence_records.push_back({"/proc/meminfo", true,
            std::chrono::duration_cast<std::chrono::milliseconds>(
                mem_result.current->measurement_window_ms.value_or(std::chrono::milliseconds(0)))});
    } else {
        evidence_records.push_back({"/proc/meminfo", false, std::nullopt});
        result.memory_assessment = make_initial_memory_assessment();
    }
    
    // Assess thermal
    auto thermal_result = assess_thermal(assessment_time);
    bool thermal_success = !thermal_result.temperatures.empty();
    
    if (thermal_success) {
        result.thermal_assessment = thermal_result;
        
        evidence_records.push_back({"/sys/class/thermal", true, std::nullopt});
    } else {
        evidence_records.push_back({"/sys/class/thermal", false, std::nullopt});
        result.thermal_assessment = make_initial_thermal_assessment();
    }
    
    // Determine overall outcome
    if (result.cpu_assessment.has_value() && 
        result.memory_assessment.has_value()) {
        result.outcome = ResourceMonitorResult::Outcome::kSuccess;
    } else if (thermal_success) {
        result.outcome = ResourceMonitorResult::Outcome::kPartial;
    } else {
        result.outcome = ResourceMonitorResult::Outcome::kUnknown;
    }
    
    // Update metrics
    metrics_.cpu_observations++;
    metrics_.memory_observations++;
    metrics_.thermal_observations++;
    
    for (const auto& rec : evidence_records) {
        if (rec.success) {
            metrics_.source_metrics[rec.source_path].acquisitions++;
            if (rec.duration_ms.has_value()) {
                metrics_.source_metrics[rec.source_path].total_acquisition_time += *rec.duration_ms;
            }
        } else {
            metrics_.source_metrics[rec.source_path].failures++;
        }
    }
    
    // Update history window
    if (history_window_.has_value() && result.cpu_assessment.has_value()) {
        history_window_->cpu_samples.push_back(result.cpu_assessment->current.value());
        
        // Keep only samples within window
        auto cutoff = std::chrono::system_clock::now() - history_window_->window_minutes;
        while (!history_window_->cpu_samples.empty() &&
               history_window_->cpu_samples.front().measured_at < cutoff) {
            history_window_->cpu_samples.erase(history_window_->cpu_samples.begin());
        }
    }
    
    // Generate events based on assessments
    generate_events(result);
    
    auto end_time = std::chrono::steady_clock::now();
    result.assessment_duration_ms = 
        std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    return result;
}

// ============================================================================
// Event generation helpers
// ============================================================================

void ResourceMonitor::generate_events(const ResourceMonitorResult& result) {
    auto now = std::chrono::system_clock::now();
    
    // Check CPU events
    if (result.cpu_assessment.has_value()) {
        const auto& cpu = *result.cpu_assessment;
        if (cpu.current.has_value()) {
            double user_pct = cpu.current->user_percent;
            
            if (user_pct >= config_.cpu_utilization_critical_percent) {
                std::ostringstream id;
                id << "cpu_crit_" << events_->next_id_counter++;
                
                ResourceEvent event;
                event.event_type = ResourceEventType::kCPUUtilizationCritical;
                event.event_id = id.str();
                event.timestamp = now;
                event.affected_subsystem = ResourceAssessment::Subsystem::kCPU;
                event.value_at_event.measurement_value = user_pct;
                event.value_at_event.threshold_type = "critical";
                event.value_at_event.threshold_value = config_.cpu_utilization_critical_percent;
                event.description = "CPU utilization critical: " + 
                    std::to_string(static_cast<int>(user_pct)) + "%";
                
                events_->pending_events[event.event_id] = std::move(event);
            } else if (user_pct >= config_.cpu_utilization_warning_percent) {
                std::ostringstream id;
                id << "cpu_warn_" << events_->next_id_counter++;
                
                ResourceEvent event;
                event.event_type = ResourceEventType::kCPUUtilizationWarning;
                event.event_id = id.str();
                event.timestamp = now;
                event.affected_subsystem = ResourceAssessment::Subsystem::kCPU;
                event.value_at_event.measurement_value = user_pct;
                event.value_at_event.threshold_type = "warning";
                event.value_at_event.threshold_value = config_.cpu_utilization_warning_percent;
                event.description = "CPU utilization warning: " + 
                    std::to_string(static_cast<int>(user_pct)) + "%";
                
                events_->pending_events[event.event_id] = std::move(event);
            }
        }
    }
    
    // Check thermal events
    if (result.thermal_assessment.has_value()) {
        const auto& thermal = *result.thermal_assessment;
        
        for (const auto& temp : thermal.temperatures) {
            double temp_c = temp.temperature_celsius;
            
            if (temp.critical_threshold_celsius.has_value() &&
                temp_c >= *temp.critical_threshold_celsius) {
                std::ostringstream id;
                id << "thermal_crit_" << temp.zone_name << "_" << events_->next_id_counter++;
                
                ResourceEvent event;
                event.event_type = ResourceEventType::kThermalCritical;
                event.event_id = id.str();
                event.timestamp = now;
                event.affected_subsystem = ResourceAssessment::Subsystem::kThermal;
                event.subject = temp.zone_name;
                event.value_at_event.measurement_value = temp_c;
                event.value_at_event.threshold_type = "critical";
                event.value_at_event.threshold_value = *temp.critical_threshold_celsius;
                event.description = "Critical thermal threshold exceeded in zone " + 
                    temp.zone_name + ": " + std::to_string(static_cast<int>(temp_c)) + "C";
                
                events_->pending_events[event.event_id] = std::move(event);
            } else if (temp.warning_threshold_celsius.has_value() &&
                       temp_c >= *temp.warning_threshold_celsius) {
                std::ostringstream id;
                id << "thermal_warn_" << temp.zone_name << "_" << events_->next_id_counter++;
                
                ResourceEvent event;
                event.event_type = ResourceEventType::kThermalWarning;
                event.event_id = id.str();
                event.timestamp = now;
                event.affected_subsystem = ResourceAssessment::Subsystem::kThermal;
                event.subject = temp.zone_name;
                event.value_at_event.measurement_value = temp_c;
                event.value_at_event.threshold_type = "warning";
                event.value_at_event.threshold_value = *temp.warning_threshold_celsius;
                event.description = "Temperature warning in zone " + 
                    temp.zone_name + ": " + std::to_string(static_cast<int>(temp_c)) + "C";
                
                events_->pending_events[event.event_id] = std::move(event);
            }
        }
    }
}

std::vector<ResourceEvent> ResourceMonitor::get_pending_events() {
    std::vector<ResourceEvent> result;
    
    for (const auto& [id, event] : events_->pending_events) {
        if (events_->acknowledged_ids.count(id) == 0) {
            result.push_back(event);
        }
    }
    
    return result;
}

void ResourceMonitor::acknowledge_event(const std::string& event_id) {
    events_->acknowledged_ids.insert(event_id);
}

// ============================================================================
// Factory functions for initial objects
// ============================================================================

CPUAssessment make_initial_cpu_assessment() {
    CPUAssessment assessment;
    assessment.state = ResourceState::kUnknown;
    assessment.assessed_at = std::chrono::system_clock::now();
    return assessment;
}

MemoryAssessment make_initial_memory_assessment() {
    MemoryAssessment assessment;
    assessment.state = ResourceState::kUnknown;
    assessment.assessed_at = std::chrono::system_clock::now();
    return assessment;
}

ThermalAssessment make_initial_thermal_assessment() {
    ThermalAssessment assessment;
    assessment.state = ResourceState::kUnknown;
    assessment.assessed_at = std::chrono::system_clock::now();
    return assessment;
}

ResourceMonitorResult make_resource_monitor_result(
    ResourceMonitorResult::Outcome outcome) {
    
    ResourceMonitorResult result;
    result.outcome = outcome;
    result.assessed_at = std::chrono::system_clock::now();
    return result;
}

}  // namespace rebuntu::modules::cpu_memory_thermal_monitor