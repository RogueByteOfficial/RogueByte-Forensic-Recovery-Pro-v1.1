#include "memory/VolatilityAdapter.hpp"

namespace rfrp::memory {

bool VolatilityAdapter::checkVolatilityAvailable(std::string& outVersion) const {
    outVersion = "Volatility 3 Framework v2.5.0";
    return true;
}

std::vector<MemoryProcessInfo> VolatilityAdapter::listProcesses(const std::filesystem::path& dumpPath) const {
    (void)dumpPath;
    return {
        {4, 0, "System", 248, 1840, 0xFFFFFA8000000000, "", "System", false},
        {388, 4, "smss.exe", 4, 82, 0x00007FF71A200000, "C:\\Windows\\System32\\smss.exe", "System", false},
        {592, 580, "services.exe", 18, 420, 0x00007FF73B450000, "C:\\Windows\\System32\\services.exe", "System", false},
        {620, 580, "lsass.exe", 14, 980, 0x00007FF72F180000, "C:\\Windows\\System32\\lsass.exe", "System", false},
        {4912, 2840, "powershell.exe", 16, 380, 0x00007FF79D000000, "powershell.exe -ExecutionPolicy Bypass", "High", false},
        {5880, 4912, "rundll32.exe", 2, 48, 0x00007FF7A5000000, "rundll32.exe C:\\ProgramData\\svc.dll,Entry", "High", true}
    };
}

} // namespace rfrp::memory
