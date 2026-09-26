// rebuntu::modules::gpu_health_monitor — GPU Health Monitor Implementation (Phase 5.10)
//
// This module provides comprehensive GPU health monitoring for Rebuntu:
//   - Device presence and identity (UUID, PCI bus ID)
//   - Driver state and reachability
//   - Utilization (memory, graphics, encoder, decoder)
//   - Temperature, power draw, clocks

#include "monitor.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstring>
#include <set>

namespace fs = std::filesystem;

namespace rebuntu::modules::gpu_health_monitor {

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<GPUMonitor> make_gpu_monitor(
    const GPUMonitorConfig& config) {
    return std::make_unique<GPUMonitor>(config);
}

// ============================================================================
// GPUMonitor implementation
// ============================================================================

GPUMonitor::GPUMonitor(GPUMonitorConfig config)
    : config_(std::move(config)),
      running_(false),
      assessment_(),
      events_(std::make_unique<EventRegistry>()) {
    // Initialize assessment with proper state
    assessment_.global_state.provider_state = GPUProviderState::kUnknown;
}

GPUMonitor::~GPUMonitor() {
    stop();
}

core::Outcome GPUMonitor::start() {
    if (running_) {
        return core::Outcome::success();
    }
    
    metrics_.started_at = std::chrono::system_clock::now();
    running_ = true;
    return core::Outcome::success();
}

core::Outcome GPUMonitor::stop() {
    if (!running_) {
        return core::Outcome::success();
    }
    
    running_ = false;
    return core::Outcome::success();
}

void GPUMonitor::set_config(const GPUMonitorConfig& config) {
    config_ = config;
}

GPUMonitorMetrics GPUMonitor::metrics() const {
    return metrics_;
}

// ============================================================================
// Native acquisition methods (stub implementations for now)
// ============================================================================

std::optional<GPUIdentity> GPUMonitor::acquire_gpu_identity(int device_index) {
    // This will be implemented with actual provider integration
    // For now, returns nullopt - no GPU detected
    return std::nullopt;
}

std::optional<GPUPower> GPUMonitor::acquire_power_data() {
    // Stub implementation - no data available
    return std::nullopt;
}

std::optional<GPUTemperature> GPUMonitor::acquire_temperature_data() {
    // Stub implementation - no data available
    return std::nullopt;
}

std::optional<GPUClocks> GPUMonitor::acquire_clocks_data() {
    // Stub implementation - no data available
    return std::nullopt;
}

std::optional<GPUUtilization> GPUMonitor::acquire_utilization_data() {
    // Stub implementation - no data available
    return std::nullopt;
}

std::optional<GPUECC> GPUMonitor::acquire_ecc_data() {
    // Stub implementation - no data available
    return std::nullopt;
}

std::optional<GPUDisplay> GPUMonitor::acquire_display_data() {
    // Stub implementation - no data available
    return std::nullopt;
}

// ============================================================================
// Assessment methods
// ============================================================================

GPUAssessment GPUMonitor::assess_gpu_health_internal(std::chrono::system_clock::time_point now) {
    GPUAssessment assessment;
    
    assessment.assessed_at = now;
    
    // Check for provider availability (native: check if nvidia driver is loaded)
    // For now, assume no provider available
    assessment.global_state.provider_state = GPUProviderState::kNotInstalled;
    
    // Try to detect devices via native Linux sources
    std::vector<GPUIdentity> detected_devices;
    
    // Native source 1: Check /sys/class/drm/ for NVIDIA GPUs
    std::error_code ec;
    fs::path drm_path("/sys/class/drm");
    
    if (fs::exists(drm_path, ec)) {
        for (const auto& entry : fs::directory_iterator(drm_path, ec)) {
            if (ec) break;
            
            std::string device_name = entry.path().filename().string();
            
            // Check if this is an NVIDIA GPU
            if (device_name.find("nvidia") != std::string::npos ||
                device_name.starts_with("card")) {
                
                // Try to read PCI bus ID
                fs::path pci_path = entry.path() / "device" / "vendor";
                std::ifstream vendor_file(pci_path);
                
                if (vendor_file.is_open()) {
                    int64_t vendor_id;
                    if (vendor_file >> std::hex >> vendor_id) {
                        // NVIDIA vendor ID is 0x10de
                        if (vendor_id == 0x10de) {
                            GPUIdentity device;
                            
                            // Get PCI bus ID from device path
                            fs::path pcie_path = entry.path() / "device" / "uevent";
                            std::ifstream uevent_file(pcie_path);
                            if (uevent_file.is_open()) {
                                std::string line;
                                while (std::getline(uevent_file, line)) {
                                    if (line.starts_with("PCI_SLOT_NAME=")) {
                                        device.pci_bus_id = line.substr(strlen("PCI_SLOT_NAME="));
                                    }
                                }
                            }
                            
                            // Set default brand for NVIDIA
                            device.brand = "NVIDIA";
                            device.device_index = detected_devices.size();
                            device.uuid = device.pci_bus_id;  // PCI bus ID as UUID fallback
                            
                            detected_devices.push_back(std::move(device));
                        }
                    }
                }
            }
        }
    }
    
    assessment.global_state.devices = std::move(detected_devices);
    assessment.global_state.total_device_count = 
        static_cast<int>(assessment.global_state.devices.size());
    assessment.global_state.available_device_count = 
        static_cast<int>(assessment.global_state.devices.size());
    
    // Build device assessments
    for (const auto& identity : assessment.global_state.devices) {
        GPUDeviceAssessment dev_assess;
        dev_assess.identity = identity;
        dev_assess.state = GPUState::kIdle;  // Default to idle
        
        // Attempt to acquire device data
        auto power_data = acquire_power_data();
        if (power_data.has_value()) {
            dev_assess.power = *power_data;
        }
        
        auto temp_data = acquire_temperature_data();
        if (temp_data.has_value()) {
            dev_assess.temperature = *temp_data;
            
            // Check temperature thresholds
            double max_temp = dev_assess.temperature.gpu_celsius;
            double mem_temp = dev_assess.temperature.memory_celsius.value_or(0.0);
            if (mem_temp > max_temp) max_temp = mem_temp;
            
            if (max_temp >= config_.temperature_critical_celsius) {
                dev_assess.state = GPUState::kFault;
            } else if (max_temp >= config_.temperature_warning_celsius) {
                dev_assess.state = GPUState::kThrottled;
            }
        }
        
        auto clocks_data = acquire_clocks_data();
        if (clocks_data.has_value()) {
            dev_assess.clocks = *clocks_data;
            
            // Check throttling
            if (dev_assess.clocks.power_limit_throttled ||
                dev_assess.clocks.thermal_limit_throttled) {
                if (dev_assess.state != GPUState::kFault) {
                    dev_assess.state = GPUState::kThrottled;
                }
            }
        }
        
        auto util_data = acquire_utilization_data();
        if (util_data.has_value()) {
            dev_assess.utilization = *util_data;
            
            // Check utilization thresholds
            double gpu_util = dev_assess.utilization.graphics_percent;
            
            if (gpu_util >= config_.utilization_critical_percent) {
                dev_assess.state = GPUState::kActive;
            } else if (gpu_util >= config_.utilization_warning_percent) {
                if (dev_assess.state == GPUState::kIdle) {
                    dev_assess.state = GPUState::kActive;
                }
            }
        }
        
        auto ecc_data = acquire_ecc_data();
        if (ecc_data.has_value()) {
            dev_assess.ecc = *ecc_data;
        }
        
        auto display_data = acquire_display_data();
        if (display_data.has_value()) {
            dev_assess.display = *display_data;
        }
        
        assessment.devices.push_back(std::move(dev_assess));
    }
    
    // Determine overall state
    int fault_count = 0;
    int throttled_count = 0;
    
    for (const auto& dev : assessment.devices) {
        if (dev.state == GPUState::kFault) {
            fault_count++;
        } else if (dev.state == GPUState::kThrottled) {
            throttled_count++;
        }
    }
    
    if (fault_count > 0) {
        assessment.system_wide_state.any_fault = true;
        assessment.system_wide_state.throttled_device_count = throttled_count;
        assessment.system_wide_state.degraded_device_count = fault_count;
    } else if (throttled_count > 0) {
        assessment.system_wide_state.throttled_device_count = throttled_count;
    }
    
    return assessment;
}

// ============================================================================
// Main assessment entry point
// ============================================================================

GPUMonitorResult GPUMonitor::assess_gpu_health(
    std::chrono::system_clock::time_point assessment_time) {
    
    GPUMonitorResult result;
    auto start_time = std::chrono::steady_clock::now();
    
    metrics_.observations++;
    
    // Perform assessment
    result.assessment = assess_gpu_health_internal(assessment_time);
    
    if (!result.assessment.devices.empty()) {
        result.outcome = GPUMonitorResult::Outcome::kSuccess;
    } else if (result.assessment.global_state.provider_state == GPUProviderState::kAvailable) {
        // Provider is available but no devices found
        result.outcome = GPUMonitorResult::Outcome::kPartial;
    } else {
        // No provider or no data
        result.outcome = GPUMonitorResult::Outcome::kUnknown;
    }
    
    metrics_.device_assessments++;
    
    auto end_time = std::chrono::steady_clock::now();
    result.assessment_duration_ms = 
        std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    // Generate events based on assessment
    generate_events(result);
    
    return result;
}

// ============================================================================
// Event generation helpers
// ============================================================================

void GPUMonitor::generate_events(const GPUMonitorResult& result) {
    auto now = std::chrono::system_clock::now();
    
    const auto& devices = result.assessment.devices;
    
    if (devices.empty()) {
        return;  // No devices to generate events for
    }
    
    for (const auto& dev : devices) {
        // Check temperature events
        double max_temp = dev.temperature.gpu_celsius;
        
        if (dev.temperature.memory_celsius.has_value() &&
            *dev.temperature.memory_celsius > max_temp) {
            max_temp = *dev.temperature.memory_celsius;
        }
        
        if (max_temp >= config_.temperature_critical_celsius) {
            std::ostringstream id;
            id << "temp_crit_" << dev.identity.uuid << "_" << events_->next_id_counter++;
            
            GPUEvent event;
            event.event_type = GPUEventType::kTemperatureCritical;
            event.event_id = id.str();
            event.timestamp = now;
            event.gpu_uuid = dev.identity.uuid;
            event.value_at_event = max_temp;
            event.threshold_type = "critical";
            event.threshold_value = static_cast<double>(config_.temperature_critical_celsius);
            event.description = "GPU temperature critical: " + 
                std::to_string(static_cast<int>(max_temp)) + "C";
            
            events_->pending_events[event.event_id] = std::move(event);
        } else if (max_temp >= config_.temperature_warning_celsius) {
            std::ostringstream id;
            id << "temp_warn_" << dev.identity.uuid << "_" << events_->next_id_counter++;
            
            GPUEvent event;
            event.event_type = GPUEventType::kTemperatureWarning;
            event.event_id = id.str();
            event.timestamp = now;
            event.gpu_uuid = dev.identity.uuid;
            event.value_at_event = max_temp;
            event.threshold_type = "warning";
            event.threshold_value = static_cast<double>(config_.temperature_warning_celsius);
            event.description = "GPU temperature warning: " + 
                std::to_string(static_cast<int>(max_temp)) + "C";
            
            events_->pending_events[event.event_id] = std::move(event);
        }
        
        // Check utilization events
        if (dev.utilization.graphics_percent >= config_.utilization_critical_percent) {
            std::ostringstream id;
            id << "util_crit_" << dev.identity.uuid << "_" << events_->next_id_counter++;
            
            GPUEvent event;
            event.event_type = GPUEventType::kUtilizationCritical;
            event.event_id = id.str();
            event.timestamp = now;
            event.gpu_uuid = dev.identity.uuid;
            event.value_at_event = static_cast<double>(dev.utilization.graphics_percent);
            event.threshold_type = "critical";
            event.threshold_value = static_cast<double>(config_.utilization_critical_percent);
            event.description = "GPU utilization critical: " + 
                std::to_string(dev.utilization.graphics_percent) + "%";
            
            events_->pending_events[event.event_id] = std::move(event);
        } else if (dev.utilization.graphics_percent >= config_.utilization_warning_percent) {
            std::ostringstream id;
            id << "util_warn_" << dev.identity.uuid << "_" << events_->next_id_counter++;
            
            GPUEvent event;
            event.event_type = GPUEventType::kUtilizationWarning;
            event.event_id = id.str();
            event.timestamp = now;
            event.gpu_uuid = dev.identity.uuid;
            event.value_at_event = static_cast<double>(dev.utilization.graphics_percent);
            event.threshold_type = "warning";
            event.threshold_value = static_cast<double>(config_.utilization_warning_percent);
            event.description = "GPU utilization warning: " + 
                std::to_string(dev.utilization.graphics_percent) + "%";
            
            events_->pending_events[event.event_id] = std::move(event);
        }
    }
}

std::vector<GPUEvent> GPUMonitor::get_pending_events() {
    std::vector<GPUEvent> result;
    
    for (const auto& [id, event] : events_->pending_events) {
        if (events_->acknowledged_ids.count(id) == 0) {
            result.push_back(event);
        }
    }
    
    return result;
}

void GPUMonitor::acknowledge_event(const std::string& event_id) {
    events_->acknowledged_ids.insert(event_id);
}

// ============================================================================
// Factory functions for initial objects
// ============================================================================

GPUDeviceAssessment make_initial_gpu_device_assessment(const GPUIdentity& identity) {
    GPUDeviceAssessment assessment;
    assessment.identity = identity;
    assessment.state = GPUState::kUnknown;
    assessment.assessed_at = std::chrono::system_clock::now();
    return assessment;
}

GPUAssessment make_initial_gpu_assessment() {
    GPUAssessment assessment;
    assessment.global_state.provider_state = GPUProviderState::kUnknown;
    assessment.assessed_at = std::chrono::system_clock::now();
    return assessment;
}

GPUMonitorResult make_gpu_monitor_result(GPUMonitorResult::Outcome outcome) {
    GPUMonitorResult result;
    result.outcome = outcome;
    result.assessment = make_initial_gpu_assessment();
    result.assessed_at = std::chrono::system_clock::now();
    return result;
}

}  // namespace rebuntu::modules::gpu_health_monitor