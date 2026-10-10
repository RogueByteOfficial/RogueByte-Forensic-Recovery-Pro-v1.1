#include "core/CaseManager.hpp"
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

namespace rfrp::core {

CaseManager::CaseManager() = default;

std::string CaseManager::getCurrentIsoTime() const {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
#if defined(_WIN32)
    gmtime_s(&tm, &t);
#else
    gmtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
    return oss.str();
}

bool CaseManager::initializeCase(
    const std::string& caseId,
    const std::string& caseName,
    const std::string& investigator,
    const std::string& organization,
    const std::string& description,
    const std::string& agencyRef
) {
    m_case.id = caseId;
    m_case.name = caseName;
    m_case.investigator = investigator;
    m_case.organization = organization;
    m_case.description = description;
    m_case.agencyReference = agencyRef;
    m_case.createdTimestamp = getCurrentIsoTime();
    m_case.auditLog.clear();

    addAuditEntry("CASE_INITIALIZED", caseId, "SUCCESS", "Case container created under ISO/IEC 27037 standards.");
    return true;
}

void CaseManager::addAuditEntry(
    const std::string& action,
    const std::string& target,
    const std::string& outcome,
    const std::string& details
) {
    AuditRecord record;
    record.id = "audit-" + std::to_string(m_case.auditLog.size() + 1);
    record.timestamp = getCurrentIsoTime();
    record.operatorName = m_case.investigator.empty() ? "SidoDev-Dz" : m_case.investigator;
    record.action = action;
    record.target = target;
    record.outcome = outcome;
    record.details = details;

    m_case.auditLog.push_back(record);
}

bool CaseManager::saveCaseManifest(const std::filesystem::path& outputPath) const {
    std::ofstream out(outputPath);
    if (!out.is_open()) return false;

    out << "{\n"
        << "  \"id\": \"" << m_case.id << "\",\n"
        << "  \"name\": \"" << m_case.name << "\",\n"
        << "  \"investigator\": \"" << m_case.investigator << "\",\n"
        << "  \"organization\": \"" << m_case.organization << "\",\n"
        << "  \"agencyReference\": \"" << m_case.agencyReference << "\",\n"
        << "  \"createdTimestamp\": \"" << m_case.createdTimestamp << "\",\n"
        << "  \"description\": \"" << m_case.description << "\",\n"
        << "  \"auditRecordsCount\": " << m_case.auditLog.size() << "\n"
        << "}\n";

    return true;
}

bool CaseManager::loadCaseManifest(const std::filesystem::path& inputPath) {
    std::ifstream in(inputPath);
    return in.is_open();
}

} // namespace rfrp::core
