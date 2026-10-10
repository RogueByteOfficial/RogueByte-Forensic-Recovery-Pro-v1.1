#pragma once
#include <string>

namespace rfrp::platform {

class PlatformUtils {
public:
    static std::string getOperatingSystemName();
    static std::string getArchitecture();
    static bool isElevated();
};

} // namespace rfrp::platform
