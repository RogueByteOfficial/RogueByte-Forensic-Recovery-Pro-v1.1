#include "carving/SignatureRegistry.hpp"

namespace rfrp::carving {

SignatureRegistry::SignatureRegistry() {
    initDefaultSignatures();
}

void SignatureRegistry::initDefaultSignatures() {
    m_signatures.push_back({
        "sig-jpeg", "jpg", "Image", "JPEG/JFIF Image",
        {0xFF, 0xD8, 0xFF}, {0xFF, 0xD9}, 128, 50 * 1024 * 1024
    });
    m_signatures.push_back({
        "sig-png", "png", "Image", "Portable Network Graphics",
        {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A},
        {0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82},
        64, 50 * 1024 * 1024
    });
    m_signatures.push_back({
        "sig-pdf", "pdf", "Document", "Adobe Portable Document Format",
        {0x25, 0x50, 0x44, 0x46, 0x2D}, {0x25, 0x25, 0x45, 0x4F, 0x46},
        256, 100 * 1024 * 1024
    });
    m_signatures.push_back({
        "sig-zip", "zip", "Archive", "ZIP Archive",
        {0x50, 0x4B, 0x03, 0x04}, {0x50, 0x4B, 0x05, 0x06},
        128, 200 * 1024 * 1024
    });
    m_signatures.push_back({
        "sig-sqlite", "sqlite3", "Database", "SQLite 3 Database",
        {0x53, 0x51, 0x4C, 0x69, 0x74, 0x65, 0x20, 0x66, 0x6F, 0x72, 0x6D, 0x61, 0x74, 0x20, 0x33, 0x00},
        {}, 512, 100 * 1024 * 1024
    });
    m_signatures.push_back({
        "sig-elf", "elf", "Executable", "Linux ELF Executable",
        {0x7F, 0x45, 0x4C, 0x46}, {}, 256, 50 * 1024 * 1024
    });
    m_signatures.push_back({
        "sig-pe", "exe", "Executable", "Windows PE Executable",
        {0x4D, 0x5A}, {}, 512, 50 * 1024 * 1024
    });
}

const std::vector<FileSignature>& SignatureRegistry::getSignatures() const {
    return m_signatures;
}

const FileSignature* SignatureRegistry::findById(const std::string& id) const {
    for (const auto& sig : m_signatures) {
        if (sig.id == id) return &sig;
    }
    return nullptr;
}

void SignatureRegistry::registerCustomSignature(const FileSignature& sig) {
    m_signatures.push_back(sig);
}

} // namespace rfrp::carving
