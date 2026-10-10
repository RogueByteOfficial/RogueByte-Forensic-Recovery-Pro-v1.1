cmake_minimum_required(VERSION 3.22)

project(RogueByteForensicRecoveryPro
    VERSION 2.4.0
    DESCRIPTION "RogueByte Forensic Recovery Pro (RFRP) - Native Digital Forensics Suite"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive- /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -fstack-protector-strong)
endif()

# 1. Cryptography (OpenSSL or Windows Native BCrypt Platform API)
find_package(OpenSSL QUIET)
if(OpenSSL_FOUND)
    message(STATUS "[+] Found OpenSSL: using OpenSSL for cryptographic operations")
    add_compile_definitions(RFRP_USE_OPENSSL=1)
    set(CRYPTO_LIBS OpenSSL::Crypto)
elseif(WIN32)
    message(STATUS "[+] OpenSSL not found; using Windows native BCrypt platform cryptography")
    add_compile_definitions(RFRP_USE_BCRYPT=1)
    set(CRYPTO_LIBS bcrypt)
else()
    message(STATUS "[*] Using embedded FIPS 180-4 standard SHA-256 implementation")
    set(CRYPTO_LIBS "")
endif()

# 2. Database (SQLite3)
find_package(SQLite3 QUIET)
if(SQLite3_FOUND)
    message(STATUS "[+] Found system SQLite3 library")
    set(SQLITE_SOURCES "")
    set(SQLITE_LIBS SQLite::SQLite3)
else()
    message(STATUS "[+] System SQLite3 not found; using embedded SQLite3 amalgamation")
    set(SQLITE_SOURCES third_party/sqlite/sqlite3.c)
    set(SQLITE_LIBS "")
endif()

# Core Library
add_library(rfrp_core
    src/hashing/Sha256Validator.cpp
    src/carving/SignatureRegistry.cpp
    src/carving/SignatureCarver.cpp
    src/core/CaseManager.cpp
    src/acquisition/windows/WinPmemProvider.cpp
    src/acquisition/linux/LimeProvider.cpp
    src/memory/VolatilityAdapter.cpp
    src/reporting/ForensicReportGenerator.cpp
    src/database/CaseDatabase.cpp
    src/platform/PlatformUtils.cpp
    src/evidence/EvidenceItem.cpp
    ${SQLITE_SOURCES}
)

target_include_directories(rfrp_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/sqlite
)

if(CRYPTO_LIBS)
    target_link_libraries(rfrp_core PUBLIC ${CRYPTO_LIBS})
endif()
if(SQLITE_LIBS)
    target_link_libraries(rfrp_core PUBLIC ${SQLITE_LIBS})
endif()

# CLI Application
add_executable(rfrp_cli
    app/cli/main_cli.cpp
)

target_link_libraries(rfrp_cli PRIVATE
    rfrp_core
)

enable_testing()
add_subdirectory(tests)
