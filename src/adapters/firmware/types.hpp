// rebuntu::adapters::firmware — Firmware/BIOS Observation Adapter (Phase 5.33)
//
// This module implements Rebuntu's firmware/BIOS observation adapter:
//   - Observes BIOS/firmware metadata via sysfs DMI/SMBIOS interface
//   - Provides safe, read-only access to firmware information
//   - Exposes firmware vendor, version, release date, and platform info
//   - Tracks firmware table availability (ACPI/EFI)
//
// Native Interfaces Used:
//   - /sys/class/dmi/id/* — DMI/SMBIOS system identification data
//   - /sys/firmware/acpi — ACPI tables and interface info
//   - /sys/firmware/efi — EFI firmware variables and metadata
//   - /sys/class/firmware — Firmware loading timeout configuration
//
// Key Distinctions:
//   - Firmware observation = reading metadata only, no mutation allowed
//   - DMI/SMBIOS = system hardware identification (vendor/product/version)
//   - BIOS/UEFI = boot firmware version and configuration state
//   - EFI variables = runtime UEFI variable storage
//
// Safety Boundaries:
//   - No firmware write/mutation operations (Phase 5.33 is observation only)
//   - DMI data is readable via sysfs without root privilege on most systems
//   - Firmware tables are read-only from userspace via /sys
//   - EFI variables require explicit capability for modification

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <chrono>
#include <vector>

namespace rebuntu::adapters::firmware {

// ============================================================================
// FirmwareKind — Type of firmware component
//
// Represents different categories of firmware entities:
//   - kBIOS: Legacy BIOS (CSM mode, 16-bit boot)
//   - kUEFI: Unified Extensible Firmware Interface
//   - kFallback: Fallback/alternative firmware (e.g., Coreboot)
// ============================================================================
enum class FirmwareKind {
    kBIOS,           // Legacy BIOS (CSM)
    kUEFI,           // UEFI firmware
    kFallback,       // Alternative firmware (Coreboot, etc.)
};

inline std::string to_string(FirmwareKind kind) {
    switch (kind) {
        case FirmwareKind::kBIOS:      return "bios";
        case FirmwareKind::kUEFI:      return "uefi";
        case FirmwareKind::kFallback:  return "fallback";
    }
    return "unknown";
}

// ============================================================================
// FirmwarePlatform — Platform firmware state
//
// Represents the current firmware configuration and capabilities:
//   - kStandard: Standard boot mode
//   - kSetup: Entering firmware setup (UEFI BIOS Setup)
//   - kOSMaintenance: OS-initiated maintenance mode
// ============================================================================
enum class FirmwarePlatform {
    kStandard,        // Normal boot mode
    kSetup,           // In firmware setup utility
    kOSMaintenance,   // OS maintenance mode
};

inline std::string to_string(FirmwarePlatform platform) {
    switch (platform) {
        case FirmwarePlatform::kStandard:       return "standard";
        case FirmwarePlatform::kSetup:          return "setup";
        case FirmwarePlatform::kOSMaintenance:  return "os-maintenance";
    }
    return "unknown";
}

// ============================================================================
// FirmwareTableType — Types of firmware tables available
//
// Represents different firmware table categories:
//   - kACPI: Advanced Configuration and Power Interface tables
//   - kSMBIOS: System Management BIOS tables (DMI data)
//   - kEFIVars: UEFI runtime variables
//   - kESRT: EFI System Resource Table (firmware update info)
// ============================================================================
enum class FirmwareTableType {
    kACPI,           // ACPI tables (FADT, MADT, etc.)
    kSMBIOS,         // SMBIOS/DMI tables
    kEFIVars,        // UEFI runtime variables
    kESRT,           // EFI System Resource Table
};

inline std::string to_string(FirmwareTableType type) {
    switch (type) {
        case FirmwareTableType::kACPI:    return "acpi";
        case FirmwareTableType::kSMBIOS:  return "smbios";
        case FirmwareTableType::kEFIVars: return "efivars";
        case FirmwareTableType::kESRT:    return "esrt";
    }
    return "unknown";
}

// ============================================================================
// DMISystemInfo — DMI/SMBIOS system identification
//
// Represents hardware identity information from the system firmware:
//   - Product name/version/sku
//   - Board/vendor info
//   - Chassis information
//   - System serial numbers (where accessible)
// ============================================================================
struct DMISystemInfo {
    // Product identity
    std::optional<std::string> product_name;
    std::optional<std::string> product_version;
    std::optional<std::string> product_sku;
    std::optional<std::string> product_family;
    
    // Board information
    std::optional<std::string> board_vendor;
    std::optional<std::string> board_name;
    std::optional<std::string> board_version;
    std::optional<std::string> board_serial;  // May require elevated privilege
    
    // Chassis information
    std::optional<std::string> chassis_vendor;
    std::optional<std::string> chassis_type;   // Numeric code (e.g., "3" = desktop)
    std::optional<std::string> chassis_version;
    
    // System identity
    std::optional<std::string> system_uuid;    // DMI system UUID
    std::optional<std::string> system_serial;  // System serial number
    
    // Firmware info (from SMBIOS type 0)
    std::optional<std::string> bios_vendor;
    std::optional<std::string> bios_version;
    std::optional<std::string> bios_release_date;
    
    // Provenance
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
};

// ============================================================================
// FirmwareIdentity — Stable identity for firmware components
//
// A firmware component is uniquely identified by its source and version.
// ============================================================================
struct FirmwareIdentity {
    std::string vendor;                // Firmware vendor (e.g., "American Megatrends Inc.")
    std::optional<std::string> version;  // Firmware version string
    std::optional<std::string> release_date;  // Release date if available
    
    // Platform-specific info
    FirmwareKind kind{FirmwareKind::kFallback};
    
    // Source of this firmware data
    std::string source{"sysfs"};
};

inline bool operator==(const FirmwareIdentity& a, const FirmwareIdentity& b) {
    return a.vendor == b.vendor && 
           a.version == b.version && 
           a.release_date == b.release_date &&
           a.kind == b.kind;
}

// ============================================================================
// FirmwareTableInfo — Information about a firmware table
//
// Represents metadata about available firmware tables:
//   - Table signature (e.g., "ACPI", "SMBIOS")
//   - Size and location in memory
//   - Revision information
// ============================================================================
struct FirmwareTableInfo {
    std::string type;              // Table type (from FirmwareTableType)
    std::optional<std::string> signature;  // Table signature (e.g., "_ACPI", "DmiS")
    std::optional<uint64_t> address;       // Physical memory address
    std::optional<uint32_t> size;          // Table size in bytes
    std::optional<uint8_t> revision;       // Table revision
    
    // Provenance
    std::chrono::system_clock::time_point captured_at{};
};

// ============================================================================
// FirmwareState — Complete firmware state observation
//
// Combines all firmware-related information into a coherent snapshot:
//   - BIOS/UEFI identity and version
//   - DMI/SMBIOS system information
//   - Available firmware tables
//   - EFI variable configuration
// ============================================================================
struct FirmwareState {
    // Core firmware identity
    FirmwareIdentity identity;
    
    // System hardware info from DMI/SMBIOS
    DMISystemInfo dmi_info;
    
    // Firmware table availability
    std::vector<FirmwareTableInfo> available_tables;
    
    // EFI-specific state (if UEFI)
    bool is_uefi{false};
    std::optional<uint64_t> efivars_size;  // Total EFIVAR size in bytes
    
    // Firmware timeout configuration
    std::optional<int> firmware_timeout_seconds;
    
    // Platform mode
    FirmwarePlatform platform_mode{FirmwarePlatform::kStandard};
    
    // Provenance
    std::chrono::system_clock::time_point observed_at{};
};

// ============================================================================
// FirmwareObservationResult — Result of firmware observation
// ============================================================================
struct FirmwareObservationResult {
    core::SemanticStatus status;
    std::string description;
    
    // Complete firmware state
    FirmwareState state;
    
    // Individual DMI components (for detailed analysis)
    std::vector<DMISystemInfo> dmi_components;
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    std::optional<core::Error> error;
};

// ============================================================================
// FirmwareAdapter — Interface for firmware observation adapter
//
// Provides safe, read-only access to firmware metadata:
//   - Query system information without modification capability
//   - Verify firmware state integrity
//   - Track available firmware interfaces (ACPI/EFI)
// ============================================================================
class FirmwareAdapter {
public:
    virtual ~FirmwareAdapter() = default;
    
    // Observe complete firmware state
    virtual FirmwareObservationResult observe_firmware() = 0;
    
    // Get DMI/SMBIOS system information
    virtual std::optional<DMISystemInfo> get_dmi_system_info() = 0;
    
    // Check if UEFI firmware is present
    virtual bool has_uefi() const = 0;
    
    // List available firmware table types
    virtual std::vector<FirmwareTableType> available_tables() const = 0;
    
    // Get firmware timeout configuration (in seconds)
    virtual std::optional<int> get_firmware_timeout() const = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<FirmwareAdapter> make_sysfs_firmware_adapter();

}  // namespace rebuntu::adapters::firmware