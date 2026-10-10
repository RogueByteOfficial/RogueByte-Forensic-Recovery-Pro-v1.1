#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <functional>
#include <memory>

namespace rfrp::acquisition {

struct MemoryAcquisitionRequest {
    std::filesystem::path destinationPath;
    bool verifySha256OnCompletion{true};
    bool writeBlockerAssumed{false};
    std::string operatorNotes;
};

struct MemoryAcquisitionResult {
    bool success{false};
    std::filesystem::path outputPath;
    uint64_t bytesWritten{0};
    std::string calculatedSha256;
    std::vector<std::string> warnings;
    std::string errorMessage;
};

struct MemoryAcquisitionCapabilities {
    std::string providerId;
    std::string providerName;
    std::string supportedOs;
    std::vector<std::string> supportedArchitectures;
    bool requiresKernelDriver{true};
    bool requiresRootOrAdmin{true};
    std::string driverName;
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
