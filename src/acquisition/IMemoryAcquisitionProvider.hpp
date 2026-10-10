/**
 * RogueByte Forensic Recovery Pro (RFRP)
 * Platform-Neutral Memory Acquisition Provider Interface
 * Developer: SidoDev-Dz | Brand: RogueByte
 */

#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <memory>

namespace rfrp::acquisition {

struct MemoryAcquisitionRequest {
    std::filesystem::path destinationPath;
    bool verifySha256OnCompletion;
    bool writeBlockerAssumed;
    std::string operatorNotes;
};

struct MemoryAcquisitionResult {
    bool success;
    std::filesystem::path outputPath;
    uint64_t bytesWritten;
    std::string calculatedSha256;
    std::vector<std::string> warnings;
    std::string errorMessage;
};

struct MemoryAcquisitionCapabilities {
    std::string providerName;
    std::string supportedOs;
    std::vector<std::string> supportedArchitectures;
    bool requiresKernelDriver;
    bool requiresRootOrAdmin;
    std::string outputFormat;
    std::vector<std::string> knownLimitations;
};

class IMemoryAcquisitionProvider {
public:
    virtual ~IMemoryAcquisitionProvider() = default;
    virtual MemoryAcquisitionCapabilities getCapabilities() const = 0;
    virtual bool isAvailableOnHost(std::string& outDiagnostic) const = 0;
    virtual MemoryAcquisitionResult executeAcquisition(
        const MemoryAcquisitionRequest& request,
        std::function<void(int percent)> progressCallback
    ) = 0;
};

} // namespace rfrp::acquisition
