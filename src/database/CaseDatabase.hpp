#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include "rfrp/Types.hpp"

namespace rfrp::database {

class CaseDatabase {
public:
    CaseDatabase() = default;
    ~CaseDatabase();
    bool open(const std::filesystem::path& dbPath);
    void close();
    bool logAudit(const AuditRecord& record);

private:
    void* m_sqliteHandle{nullptr};
};

} // namespace rfrp::database
