#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <filesystem>

namespace rfrp {

enum class EvidenceType {
    DiskImage,
    RamDump,
    RawBinary,
    LogFile,
    CarvedArtifact
};

enum class ValidationStatus {
    Valid,
    Truncated,
    Oversized,
    HeaderOnly
};

struct AuditRecord {
    std::string id;
    std::string timestamp;
    std::string operatorName;
    std::string action;
    std::string target;
    std::string outcome;
    std::string details;
};

struct FileSignature {
    std::string id;
    std::string extension;
    std::string category;
    std::string description;
    std::vector<uint8_t> headerBytes;
    std::vector<uint8_t> trailerBytes;
    uint64_t minSize;
    uint64_t maxSize;
};

struct CarvedResult {
    std::string id;
    std::string extension;
    std::string fileType;
    uint64_t startOffset;
    uint64_t endOffset;
    uint64_t sizeBytes;
    std::string sha256;
    bool headerValid;
    bool trailerValid;
    ValidationStatus status;
    std::filesystem::path outputPath;
};

struct MemoryProcessInfo {
    uint32_t pid;
    uint32_t ppid;
    std::string name;
    uint32_t threads;
    uint32_t handles;
    uint64_t baseAddress;
    std::string commandLine;
    std::string integrity;
    bool unlinked;
};

} // namespace rfrp
