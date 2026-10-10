#pragma once
#include <string>
#include <vector>
#include "rfrp/Types.hpp"

namespace rfrp::carving {

class SignatureRegistry {
public:
    SignatureRegistry();
    const std::vector<FileSignature>& getSignatures() const;
    const FileSignature* findById(const std::string& id) const;
    void registerCustomSignature(const FileSignature& sig);

private:
    void initDefaultSignatures();
    std::vector<FileSignature> m_signatures;
};

} // namespace rfrp::carving
