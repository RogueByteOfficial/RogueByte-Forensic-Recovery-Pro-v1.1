#pragma once
#include <string>
#include <filesystem>
#include <vector>
#include <cstdint>

namespace rfrp::hashing {

class Sha256Validator {
public:
    static std::string calculateBufferHash(const uint8_t* data, size_t length);
    static std::string calculateFileHash(const std::filesystem::path& path);
    static bool verifyFileHash(const std::filesystem::path& path, const std::string& expectedHex);
    static bool verifyBufferHash(const uint8_t* data, size_t length, const std::string& expectedHex);
};

} // namespace rfrp::hashing
