#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "rfrp/Types.hpp"

namespace rfrp::core {

struct ForensicCaseInfo {
    std::string id;
    std::string name;
    std::string investigator;
    std::string organization;
    std::string agencyReference;
    std::string createdTimestamp;
    std::string description;
    std::vector<AuditRecord> auditLog;
};

class CaseManager {
public:
    CaseManager();

    bool initializeCase(
        const std::string& caseId,
        const std::string& caseName,
        const std::string& investigator,
        const std::string& organization,
        const std::string& description,
        const std::string& agencyRef = ""
    );

    bool saveCaseManifest(const std::filesystem::path& outputPath) const;
    bool loadCaseManifest(const std::filesystem::path& inputPath);

    void addAuditEntry(
        const std::string& action,
        const std::string& target,
        const std::string& outcome,
        const std::string& details
    );

    const ForensicCaseInfo& getCaseInfo() const { return m_case; }
    bool hasActiveCase() const { return !m_case.id.empty(); }

private:
    ForensicCaseInfo m_case;
    std::string getCurrentIsoTime() const;
};

} // namespace rfrp::core
