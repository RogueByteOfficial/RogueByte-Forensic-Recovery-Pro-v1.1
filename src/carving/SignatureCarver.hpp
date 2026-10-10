#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <functional>
#include <filesystem>
#include "rfrp/Types.hpp"
#include "carving/SignatureRegistry.hpp"

namespace rfrp::carving {

class SignatureCarver {
public:
    SignatureCarver();

    std::vector<CarvedResult> carveFile(
        const std::filesystem::path& sourcePath,
        const std::filesystem::path& outputDirectory,
        bool sectorAlignedOnly = true,
        uint32_t sectorSize = 512,
        std::function<void(int progressPercent, size_t foundCount)> progressCallback = nullptr
    );

    std::vector<CarvedResult> carveBuffer(
        const uint8_t* buffer,
        size_t bufferSize,
        const std::filesystem::path& outputDirectory,
        bool sectorAlignedOnly = true,
        uint32_t sectorSize = 512,
        std::function<void(int progressPercent, size_t foundCount)> progressCallback = nullptr
    );

    const SignatureRegistry& getRegistry() const { return m_registry; }

private:
    SignatureRegistry m_registry;
};

} // namespace rfrp::carving
