#include "reporting/ForensicReportGenerator.hpp"
#include <fstream>
#include <sstream>

namespace rfrp::reporting {

bool ForensicReportGenerator::generateHtmlReport(
    const core::ForensicCaseInfo& caseInfo,
    const std::vector<CarvedResult>& carvedResults,
    const std::filesystem::path& outputPath,
    bool arabic
) {
    std::ofstream out(outputPath);
    if (!out.is_open()) return false;

    out << "<!DOCTYPE html>\n<html lang=\"" << (arabic ? "ar" : "en") << "\" dir=\"" << (arabic ? "rtl" : "ltr") << "\">\n"
        << "<head><meta charset=\"utf-8\"><title>Forensic Report - " << caseInfo.id << "</title>\n"
        << "<style>body{font-family:sans-serif;margin:40px;line-height:1.6;}table{width:100%;border-collapse:collapse;}th,td{border:1px solid #ccc;padding:8px;}th{background:#f4f4f4;}</style></head>\n"
        << "<body>\n"
        << "<h1>" << (arabic ? "تقرير التحقيق الجنائي الرقمي" : "Digital Forensics Examination Report") << "</h1>\n"
        << "<p><b>Developer:</b> SidoDev-Dz | <b>Brand:</b> RogueByte | <b>Tool:</b> RogueByte Forensic Recovery Pro v2.4.0</p>\n"
        << "<hr/>\n"
        << "<h3>Case Identification</h3>\n"
        << "<p><b>Case ID:</b> " << caseInfo.id << "<br/><b>Investigator:</b> " << caseInfo.investigator << "<br/><b>Organization:</b> " << caseInfo.organization << "</p>\n"
        << "<h3>Recovered Artifacts (" << carvedResults.size() << ")</h3>\n"
        << "<table><tr><th>Extension</th><th>Start Offset</th><th>Size</th><th>SHA-256</th></tr>\n";

    for (const auto& res : carvedResults) {
        out << "<tr><td>." << res.extension << "</td><td>0x" << std::hex << res.startOffset << std::dec << "</td><td>" << res.sizeBytes << " B</td><td><code>" << res.sha256 << "</code></td></tr>\n";
    }

    out << "</table>\n"
        << "<p><i>Notice: Matching SHA-256 confirms byte-for-byte identity of examined blocks.</i></p>\n"
        << "</body></html>\n";

    return true;
}

bool ForensicReportGenerator::generateJsonReport(
    const core::ForensicCaseInfo& caseInfo,
    const std::vector<CarvedResult>& carvedResults,
    const std::filesystem::path& outputPath
) {
    std::ofstream out(outputPath);
    if (!out.is_open()) return false;

    out << "{\n  \"caseId\": \"" << caseInfo.id << "\",\n  \"carvedCount\": " << carvedResults.size() << "\n}\n";
    return true;
}

} // namespace rfrp::reporting
