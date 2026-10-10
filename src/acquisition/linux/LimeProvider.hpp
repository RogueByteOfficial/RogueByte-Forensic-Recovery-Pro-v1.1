#pragma once
#include "acquisition/interfaces/IMemoryAcquisitionProvider.hpp"

namespace rfrp::acquisition::linux {

class LimeProvider : public IMemoryAcquisitionProvider {
public:
    LimeProvider();
    MemoryAcquisitionCapabilities getCapabilities() const override;
    bool isAvailableOnHost(std::string& outDiagnostic) const override;
    MemoryAcquisitionResult executeAcquisition(
        const MemoryAcquisitionRequest& request,
        std::function<void(int percent)> progressCallback
    ) override;
};

} // namespace rfrp::acquisition::linux
