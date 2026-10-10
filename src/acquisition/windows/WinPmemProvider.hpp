#pragma once
#include "acquisition/interfaces/IMemoryAcquisitionProvider.hpp"

namespace rfrp::acquisition::windows {

class WinPmemProvider : public IMemoryAcquisitionProvider {
public:
    WinPmemProvider();
    MemoryAcquisitionCapabilities getCapabilities() const override;
    bool isAvailableOnHost(std::string& outDiagnostic) const override;
    MemoryAcquisitionResult executeAcquisition(
        const MemoryAcquisitionRequest& request,
        std::function<void(int percent)> progressCallback
    ) override;
};

} // namespace rfrp::acquisition::windows
