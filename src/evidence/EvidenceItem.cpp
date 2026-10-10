#include "evidence/EvidenceItem.hpp"
#include "hashing/Sha256Validator.hpp"

namespace rfrp::evidence {

EvidenceItem::EvidenceItem(
    std::string id,
    std::filesystem::path path,
    EvidenceType type,
    std::string registeredBy
) : m_id(std::move(id)),
    m_path(std::move(path)),
    m_type(type),
    m_registeredBy(std::move(registeredBy))
{
    std::error_code ec;
    m_sizeBytes = std::filesystem::file_size(m_path, ec);
    if (ec) m_sizeBytes = 0;
}

bool EvidenceItem::computeAndVerifyHash() {
    m_sha256 = hashing::Sha256Validator::calculateFileHash(m_path);
    return !m_sha256.empty();
}

} // namespace rfrp::evidence
