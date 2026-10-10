#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "rfrp/Types.hpp"

namespace rfrp::memory {

class VolatilityAdapter {
public:
    VolatilityAdapter() = default;
    bool checkVolatilityAvailable(std::string& outVersion) const;
    std::vector<MemoryProcessInfo> listProcesses(const std::filesystem::path& dumpPath) const;
};

} // namespace rfrp::memory
