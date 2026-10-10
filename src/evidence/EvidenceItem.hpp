#pragma once
#include <string>
#include <filesystem>
#include "rfrp/Types.hpp"

namespace rfrp::evidence {

class EvidenceItem {
public:
    EvidenceItem(
        std::string id,
        std::filesystem::path path,
        EvidenceType type,
        std::string registeredBy
    );

    const std::string& getId() const { return m_id; }
    const std::filesystem::path& getPath() const { return m_path; }
    EvidenceType getType() const { return m_type; }
    uint64_t getSizeBytes() const { return m_sizeBytes; }
    const std::string& getSha256() const { return m_sha256; }
    bool isReadOnlyEnforced() const { return m_readOnlyEnforced; }
    bool computeAndVerifyHash();

private:
    std::string m_id;
    std::filesystem::path m_path;
    EvidenceType m_type;
    uint64_t m_sizeBytes{0};
    std::string m_sha256;
    std::string m_registeredBy;
    bool m_readOnlyEnforced{true};
};

} // namespace rfrp::evidence
