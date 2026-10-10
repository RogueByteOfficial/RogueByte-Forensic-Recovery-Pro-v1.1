#include "database/CaseDatabase.hpp"
#include <sqlite3.h>

namespace rfrp::database {

CaseDatabase::~CaseDatabase() {
    close();
}

bool CaseDatabase::open(const std::filesystem::path& dbPath) {
    sqlite3* db = nullptr;
    int rc = sqlite3_open(dbPath.string().c_str(), &db);
    if (rc != SQLITE_OK) {
        if (db) sqlite3_close(db);
        return false;
    }
    m_sqliteHandle = db;

    const char* schema = "CREATE TABLE IF NOT EXISTS audit_log ("
                         "id TEXT PRIMARY KEY, timestamp TEXT, operator TEXT, "
                         "action TEXT, target TEXT, outcome TEXT, details TEXT);";
    char* err = nullptr;
    sqlite3_exec(db, schema, nullptr, nullptr, &err);
    if (err) sqlite3_free(err);
    return true;
}

void CaseDatabase::close() {
    if (m_sqliteHandle) {
        sqlite3_close(static_cast<sqlite3*>(m_sqliteHandle));
        m_sqliteHandle = nullptr;
    }
}

bool CaseDatabase::logAudit(const AuditRecord& record) {
    if (!m_sqliteHandle) return false;
    sqlite3* db = static_cast<sqlite3*>(m_sqliteHandle);

    const char* sql = "INSERT INTO audit_log (id, timestamp, operator, action, target, outcome, details) VALUES (?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) return false;

    sqlite3_bind_text(stmt, 1, record.id.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, record.timestamp.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, record.operatorName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, record.action.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, record.target.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, record.outcome.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 7, record.details.c_str(), -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

} // namespace rfrp::database
