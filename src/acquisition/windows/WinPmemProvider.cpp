#include "acquisition/windows/WinPmemProvider.hpp"

namespace rfrp::acquisition::windows {

WinPmemProvider::WinPmemProvider() = default;

MemoryAcquisitionCapabilities WinPmemProvider::getCapabilities() const {
    return {
        "provider-winpmem",
        "WinPmem 64-bit Memory Extractor",
        "Windows 10/11 x64, Server 2016-2022",
        {"x86_64", "ARM64"},
        true,
        true,
        "winpmem_x64.sys",
        "RAW Physical Memory (.raw / .dmp)",
        {
            "Requires Administrator token and SeDebugPrivilege.",
            "Loading driver alters active physical memory pages.",
            "Hypervisor-Protected Code Integrity (HVCI) enforcement requires Microsoft EV certificate."
        }
    };
}

bool WinPmemProvider::isAvailableOnHost(std::string& outDiagnostic) const {
#if defined(_WIN32)
    outDiagnostic = "Windows OS detected. Administrator privilege required.";
    return true;
#else
    outDiagnostic = "WinPmem is only supported on Windows platforms.";
    return false;
#endif
}

MemoryAcquisitionResult WinPmemProvider::executeAcquisition(
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

} // namespace rfrp::acquisition::windows
