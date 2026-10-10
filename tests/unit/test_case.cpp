#include <iostream>
#include <cassert>
#include "core/CaseManager.hpp"

int main() {
    using namespace rfrp::core;
    CaseManager manager;
    assert(!manager.hasActiveCase());

    bool init = manager.initializeCase("RFRP-TEST-001", "Test Triage", "SidoDev-Dz", "RogueByte", "Unit test");
    assert(init);
    assert(manager.hasActiveCase());
    assert(manager.getCaseInfo().id == "RFRP-TEST-001");
    assert(!manager.getCaseInfo().auditLog.empty());

    std::cout << "[PASS] Case management unit test passed.\n";
    return 0;
}
