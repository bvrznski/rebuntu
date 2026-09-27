// rebuntu::adapters::firmware::implementation — Firmware Observation Adapter Implementation (Phase 5.33)
//
// This module implements Rebuntu's firmware/BIOS observation adapter:
//   - Observes BIOS/firmware metadata via sysfs DMI/SMBIOS interface
//   - Provides safe, read-only access to firmware information
//   - Exposes firmware vendor, version, release date, and platform info
//   - Tracks firmware table availability (ACPI/EFI)

#include "types.hpp"

#include <system/core/contracts.hpp>

#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include <iomanip>

namespace rebuntu::adapters::firmware {

namespace fs = std::filesystem;

// ============================================================================
// Helper functions for reading sysfs files
// ============================================================================

static std::optional<std::string> read_sysfs_file(std::string_view path) {
    std::ifstream file(std::string{path});
    if (!file.is_open()) {
        return std::nullopt;
    }
    
    std::stringstream ss;
    ss << file.rdbuf();
    std::string content = ss.str();
    
    // Trim trailing whitespace/newlines
    while (!content.empty() && (content.back() == '\n' || content.back() == '\r')) {
        content.pop_back();
    }
    
    return content;
}

static bool path_exists(std::string_view path) {
    std::ifstream file(std::string{path});
    return file.good();
}

// ============================================================================
// DMISystemInfoReader — Reads DMI/SMBIOS information from sysfs
// ============================================================================

struct DMISystemInfoReader {
    static std::optional<DMISystemInfo> read() {
        auto result = DMISystemInfo{};
        auto start_time = std::chrono::system_clock::now();
        
        // Read product info
        result.product_name = read_sysfs_file("/sys/class/dmi/id/product_name");
        result.product_version = read_sysfs_file("/sys/class/dmi/id/product_version");
        result.product_sku = read_sysfs_file("/sys/class/dmi/id/product_sku");
        result.product_family = read_sysfs_file("/sys/class/dmi/id/product_family");
        
        // Read board info
        result.board_vendor = read_sysfs_file("/sys/class/dmi/id/board_vendor");
        result.board_name = read_sysfs_file("/sys/class/dmi/id/board_name");
        result.board_version = read_sysfs_file("/sys/class/dmi/id/board_version");
        // Note: board_serial may require elevated privilege
        result.board_serial = read_sysfs_file("/sys/class/dmi/id/board_serial");
        
        // Read chassis info
        result.chassis_vendor = read_sysfs_file("/sys/class/dmi/id/chassis_vendor");
        result.chassis_type = read_sysfs_file("/sys/class/dmi/id/chassis_type");
        result.chassis_version = read_sysfs_file("/sys/class/dmi/id/chassis_version");
        
        // Read system identity (may require elevated privilege for serial/UUID)
        result.system_uuid = read_sysfs_file("/sys/class/dmi/id/product_uuid");
        result.system_serial = read_sysfs_file("/sys/class/dmi/id/product_serial");
        
        // Read firmware info from DMI type 0 (BIOS information)
        result.bios_vendor = read_sysfs_file("/sys/class/dmi/id/bios_vendor");
        result.bios_version = read_sysfs_file("/sys/class/dmi/id/bios_version");
        result.bios_release_date = read_sysfs_file("/sys/class/dmi/id/bios_date");
        
        // Set timestamp
        result.captured_at = std::chrono::system_clock::now();
        result.capture_duration_ms = 
            std::chrono::duration_cast<std::chrono::milliseconds>(result.captured_at - start_time);
        
        return result;
    }
};

// ============================================================================
// FirmwareAdapterImpl — Implementation of FirmwareAdapter interface
// ============================================================================

class FirmwareAdapterImpl : public FirmwareAdapter {
public:
    FirmwareAdapterImpl() = default;
    
    ~FirmwareAdapterImpl() override = default;
    
    FirmwareObservationResult observe_firmware() override {
        auto result = FirmwareObservationResult{};
        auto start_time = std::chrono::system_clock::now();
        
        // Check if UEFI is present
        bool has_uefi = path_exists("/sys/firmware/efi");
        
        // Determine firmware kind based on presence of EFI
        FirmwareKind firmware_kind;
        if (has_uefi) {
            firmware_kind = FirmwareKind::kUEFI;
        } else if (path_exists("/sys/class/dmi/id/bios_vendor")) {
            firmware_kind = FirmwareKind::kBIOS;
        } else {
            firmware_kind = FirmwareKind::kFallback;
        }
        
        // Build firmware identity
        result.state.identity.vendor = read_sysfs_file("/sys/class/dmi/id/bios_vendor").value_or("unknown");
        result.state.identity.kind = firmware_kind;
        result.state.identity.source = "sysfs";
        
        if (auto version = read_sysfs_file("/sys/class/dmi/id/bios_version")) {
            result.state.identity.version = *version;
        }
        
        if (auto date = read_sysfs_file("/sys/class/dmi/id/bios_date")) {
            result.state.identity.release_date = *date;
        }
        
        // Read DMI system information
        auto dmi_info_opt = DMISystemInfoReader::read();
        if (dmi_info_opt) {
            result.state.dmi_info = *dmi_info_opt;
            result.dmi_components.push_back(*dmi_info_opt);
        }
        
        // Check available firmware tables
        result.state.available_tables = get_available_tables();
        
        // EFI-specific state
        result.state.is_uefi = has_uefi;
        if (has_uefi) {
            auto efivars_path = fs::path{"/sys/firmware/efi/efivars"};
            if (fs::exists(efivars_path)) {
                uint64_t total_size = 0;
                for (const auto& entry : fs::directory_iterator(efivars_path)) {
                    if (entry.is_regular_file()) {
                        total_size += entry.file_size();
                    }
                }
                result.state.efivars_size = total_size;
            }
        }
        
        // Get firmware timeout configuration
        result.state.firmware_timeout_seconds = get_firmware_timeout();
        
        // Determine platform mode
        result.state.platform_mode = determine_platform_mode();
        
        // Set timestamps and completion info
        result.observed_at = std::chrono::system_clock::now();
        result.elapsed_ms = 
            std::chrono::duration_cast<std::chrono::milliseconds>(result.observed_at - start_time);
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Firmware observation completed successfully";
        
        return result;
    }
    
    std::optional<DMISystemInfo> get_dmi_system_info() override {
        return DMISystemInfoReader::read();
    }
    
    bool has_uefi() const override {
        return path_exists("/sys/firmware/efi");
    }
    
    std::vector<FirmwareTableType> available_tables() const override {
        std::vector<FirmwareTableType> tables;
        
        if (path_exists("/sys/class/dmi/id/bios_vendor")) {
            tables.push_back(FirmwareTableType::kSMBIOS);
        }
        
        if (path_exists("/sys/firmware/acpi/tables")) {
            tables.push_back(FirmwareTableType::kACPI);
        }
        
        if (path_exists("/sys/firmware/efi/efivars")) {
            tables.push_back(FirmwareTableType::kEFIVars);
        }
        
        if (path_exists("/sys/firmware/efi/esrt")) {
            tables.push_back(FirmwareTableType::kESRT);
        }
        
        return tables;
    }
    
    std::optional<int> get_firmware_timeout() const override {
        auto timeout_str = read_sysfs_file("/sys/class/firmware/timeout");
        if (timeout_str) {
            try {
                return std::stoi(*timeout_str);
            } catch (...) {
                // Return nullopt on parse error
            }
        }
        return std::nullopt;
    }

private:
    FirmwarePlatform determine_platform_mode() const {
        // Platform mode is typically determined by firmware state
        // For now, we default to standard mode as it's the most common
        // More sophisticated detection would require additional kernel interfaces
        
        // Check if we're in setup mode (UEFI)
        // This would normally check EFI variables or boot flags
        // For safety, we report standard unless there's clear evidence otherwise
        
        return FirmwarePlatform::kStandard;
    }
    
    std::vector<FirmwareTableInfo> get_available_tables() const {
        std::vector<FirmwareTableInfo> tables;
        
        // Check SMBIOS/DMI tables via sysfs
        auto smbios_path = fs::path{"/sys/firmware/dmi/tables"};
        if (fs::exists(smbios_path)) {
            for (const auto& entry : fs::directory_iterator(smbios_path)) {
                if (entry.is_regular_file()) {
                    FirmwareTableInfo info;
                    info.type = "smbios";
                    
                    auto filename = entry.path().filename().string();
                    if (filename == "DMI") {
                        info.signature = "DMI";
                        info.size = static_cast<uint32_t>(entry.file_size());
                    }
                    
                    info.captured_at = std::chrono::system_clock::now();
                    tables.push_back(info);
                }
            }
        }
        
        // Check EFI System Resource Table (ESRT) for firmware update info
        auto esrt_path = fs::path{"/sys/firmware/efi/esrt"};
        if (fs::exists(esrt_path)) {
            FirmwareTableInfo info;
            info.type = "esrt";
            info.signature = "ESRT";
            
            // Try to read ESRT entry count
            auto entries_path_str = (esrt_path / "entries").string();
            if (path_exists(entries_path_str)) {
                if (auto content = read_sysfs_file(entries_path_str)) {
                    try {
                        info.size = static_cast<uint32_t>(std::stoul(*content));
                    } catch (...) {
                        // Ignore parse errors
                    }
                }
            }
            
            info.captured_at = std::chrono::system_clock::now();
            tables.push_back(info);
        }
        
        return tables;
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<FirmwareAdapter> make_sysfs_firmware_adapter() {
    return std::make_unique<FirmwareAdapterImpl>();
}

}  // namespace rebuntu::adapters::firmware