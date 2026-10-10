#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "rfrp/Types.hpp"
#include "core/CaseManager.hpp"

namespace rfrp::reporting {

class ForensicReportGenerator {
public:
    static bool generateHtmlReport(
        const core::ForensicCaseInfo& caseInfo,
        const std::vector<CarvedResult>& carvedResults,
        const std::filesystem::path& outputPath,
        bool arabic = false
    );

    static bool generateJsonReport(
        const core::ForensicCaseInfo& caseInfo,
        const std::vector<CarvedResult>& carvedResults,
        const std::filesystem::path& outputPath
    );
};

} // namespace rfrp::reporting
