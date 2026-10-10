#include "platform/PlatformUtils.hpp"
#if defined(_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#include <sys/utsname.h>
#endif

namespace rfrp::platform {

std::string PlatformUtils::getOperatingSystemName() {
#if defined(_WIN32)
    return "Microsoft Windows";
#elif defined(__linux__)
    struct utsname buf;
    if (uname(&buf) == 0) return std::string("Linux ") + buf.release;
    return "Linux";
#elif defined(__APPLE__)
    return "Apple macOS";
#else
    return "POSIX Compatible";
#endif
}

std::string PlatformUtils::getArchitecture() {
#if defined(__x86_64__) || defined(_M_X64)
    return "x86_64";
#elif defined(__aarch64__) || defined(_M_ARM64)
    return "ARM64";
#else
    return "x86";
#endif
}

bool PlatformUtils::isElevated() {
#if defined(_WIN32)
    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if (hToken) CloseHandle(hToken);
    return fRet;
#else
    return (geteuid() == 0);
#endif
}

} // namespace rfrp::platform
