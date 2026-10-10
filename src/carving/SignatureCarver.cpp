#include "carving/SignatureCarver.hpp"
#include "hashing/Sha256Validator.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>

namespace rfrp::carving {

SignatureCarver::SignatureCarver() = default;

std::vector<CarvedResult> SignatureCarver::carveFile(
    const std::filesystem::path& sourcePath,
    const std::filesystem::path& outputDirectory,
    bool sectorAlignedOnly,
    uint32_t sectorSize,
    std::function<void(int, size_t)> progressCallback
) {
    std::ifstream file(sourcePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return {};

    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    if (fileSize <= 0) return {};

    std::vector<uint8_t> buffer(fileSize);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize)) return {};

    return carveBuffer(buffer.data(), buffer.size(), outputDirectory, sectorAlignedOnly, sectorSize, progressCallback);
}

std::vector<CarvedResult> SignatureCarver::carveBuffer(
    const uint8_t* buffer,
    size_t bufferSize,
    const std::filesystem::path& outputDirectory,
    bool sectorAlignedOnly,
    uint32_t sectorSize,
    std::function<void(int, size_t)> progressCallback
) {
    std::vector<CarvedResult> results;
    if (!buffer || bufferSize == 0) return results;

    if (!outputDirectory.empty()) {
        std::error_code ec;
        std::filesystem::create_directories(outputDirectory, ec);
    }

    const auto& signatures = m_registry.getSignatures();
    const size_t step = sectorAlignedOnly ? sectorSize : 1;

    for (size_t offset = 0; offset < bufferSize; offset += step) {
        if (progressCallback && (offset % (64 * 1024) == 0 || offset + step >= bufferSize)) {
            int pct = static_cast<int>((offset * 100) / bufferSize);
            progressCallback(pct, results.size());
        }

        for (const auto& sig : signatures) {
            if (offset + sig.headerBytes.size() > bufferSize) continue;

            bool headerMatch = true;
            for (size_t i = 0; i < sig.headerBytes.size(); ++i) {
                if (buffer[offset + i] != sig.headerBytes[i]) {
                    headerMatch = false;
                    break;
                }
            }
            if (!headerMatch) continue;

            size_t endOffset = 0;
            bool trailerMatch = false;
            ValidationStatus status = ValidationStatus::HeaderOnly;

            if (!sig.trailerBytes.empty()) {
                size_t maxSearch = std::min(bufferSize, offset + sig.maxSize);
                size_t tLen = sig.trailerBytes.size();

                for (size_t j = offset + sig.headerBytes.size(); j + tLen <= maxSearch; ++j) {
                    bool tMatch = true;
                    for (size_t k = 0; k < tLen; ++k) {
                        if (buffer[j + k] != sig.trailerBytes[k]) {
                            tMatch = false;
                            break;
                        }
                    }
                    if (tMatch) {
                        endOffset = j + tLen;
                        trailerMatch = true;
                        status = ValidationStatus::Valid;
                        break;
                    }
                }

                if (!trailerMatch) {
                    endOffset = std::min(bufferSize, offset + sig.maxSize);
                    status = ValidationStatus::Truncated;
                }
            } else {
                endOffset = std::min(bufferSize, offset + std::max<size_t>(4096, sig.minSize * 2));
                status = ValidationStatus::Valid;
            }

            size_t candidateSize = endOffset - offset;
            if (candidateSize < sig.minSize) continue;

            std::string sha256 = hashing::Sha256Validator::calculateBufferHash(&buffer[offset], candidateSize);

            std::ostringstream idStream;
            idStream << "carved-" << results.size() + 1 << "-0x" << std::hex << offset;

            std::filesystem::path recoveredPath;
            if (!outputDirectory.empty()) {
                std::ostringstream filename;
                filename << "recovered_0x" << std::hex << offset << "." << sig.extension;
                recoveredPath = outputDirectory / filename.str();

                std::ofstream out(recoveredPath, std::ios::binary);
                if (out.is_open()) {
                    out.write(reinterpret_cast<const char*>(&buffer[offset]), candidateSize);
                }
            }

            results.push_back({
                idStream.str(),
                sig.extension,
                sig.category,
                static_cast<uint64_t>(offset),
                static_cast<uint64_t>(endOffset),
                static_cast<uint64_t>(candidateSize),
                sha256,
                true,
                trailerMatch,
                status,
                recoveredPath
            });

            if (status == ValidationStatus::Valid && candidateSize > 512) {
                offset = endOffset - (sectorAlignedOnly ? 0 : 1);
                break;
            }
        }
    }

    if (progressCallback) progressCallback(100, results.size());
    return results;
}

} // namespace rfrp::carving
