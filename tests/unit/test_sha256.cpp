#include <iostream>
#include <cassert>
#include "hashing/Sha256Validator.hpp"

int main() {
    using namespace rfrp::hashing;
    std::string emptyHash = Sha256Validator::calculateBufferHash(nullptr, 0);
    assert(emptyHash == "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");

    const uint8_t abc[] = {'a', 'b', 'c'};
    std::string abcHash = Sha256Validator::calculateBufferHash(abc, 3);
    assert(abcHash == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");

    assert(Sha256Validator::verifyBufferHash(abc, 3, "BA7816BF8F01CFEA414140DE5DAE2223B00361A396177A9CB410FF61F20015AD"));
    std::cout << "[PASS] SHA-256 test vectors passed.\n";
    return 0;
}
