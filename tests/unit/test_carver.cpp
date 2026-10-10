#include <iostream>
#include <vector>
#include <cassert>
#include "carving/SignatureCarver.hpp"

int main() {
    using namespace rfrp::carving;
    SignatureCarver carver;

    std::vector<uint8_t> buffer = {
        0x00, 0x00,
        0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
        0x00, 0x01, 0x02, 0x03,
        0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82,
        0x00, 0x00
    };

    auto results = carver.carveBuffer(buffer.data(), buffer.size(), "", false, 1);
    assert(results.size() == 1);
    assert(results[0].extension == "png");
    assert(results[0].startOffset == 2);
    assert(results[0].headerValid == true);
    assert(results[0].trailerValid == true);
    assert(results[0].status == rfrp::ValidationStatus::Valid);

    std::cout << "[PASS] Signature carving boundary test passed.\n";
    return 0;
}
