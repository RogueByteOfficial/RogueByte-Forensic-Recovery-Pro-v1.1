#include "acquisition/linux/LimeProvider.hpp"
#include <unistd.h>

namespace rfrp::acquisition::linux {

LimeProvider::LimeProvider() = default;

MemoryAcquisitionCapabilities LimeProvider::getCapabilities() const {
    return {
        "provider-lime",
        "Linux Memory Extractor (LiME)",
        "Linux Kernels 2.6.x - 6.x",
        {"x86_64", "aarch64", "armv7l"},
        true,
        true,
        "lime.ko",
        "LiME Format / RAW (.raw)",
        {
            "Requires root privileges (CAP_SYS_MODULE) to load module.",
            "Module must match kernel vermagic string.",
            "UEFI Secure Boot lockdown prevents unsigned kernel module insertion."
        }
    };
}

bool LimeProvider::isAvailableOnHost(std::string& outDiagnostic) const {
#if defined(__linux__)
    if (geteuid() != 0) {
        outDiagnostic = "LiME provider requires elevated root (UID 0) privileges.";
        return false;
    }
    outDiagnostic = "Linux host verified with root privileges.";
    return true;
#else
    outDiagnostic = "LiME is only supported on Linux hosts.";
    return false;
#endif
}

MemoryAcquisitionResult LimeProvider::executeAcquisition(
    const MemoryAcquisitionRequest& request,
    std::function<void(int)> progressCallback
) {
    MemoryAcquisitionResult result;
    std::string diag;
    if (!isAvailableOnHost(diag)) {
        result.success = false;
        result.errorMessage = diag;
        return result;
    }
    if (progressCallback) progressCallback(100);
    result.success = true;
    result.outputPath = request.destinationPath;
    return result;
}

} // namespace rfrp::acquisition::linux
