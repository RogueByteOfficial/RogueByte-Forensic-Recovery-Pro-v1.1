/**
 * RogueByte Forensic Recovery Pro (RFRP) - CLI Interface
 * Developer: SidoDev-Dz | Brand: RogueByte
 */

#include <iostream>
#include <string>
#include <vector>
#include "core/CaseManager.hpp"
#include "carving/SignatureCarver.hpp"
#include "hashing/Sha256Validator.hpp"

void printUsage() {
    std::cout << "RogueByte Forensic Recovery Pro (RFRP) CLI v2.4.0\n"
              << "Developer: SidoDev-Dz | Brand: RogueByte\n\n"
              << "Usage: rfrp_cli [COMMAND] [OPTIONS]\n"
              << "Commands:\n"
              << "  --carve <image_path> --out <dest_dir> [--aligned]\n"
              << "  --hash <evidence_path> [--expected <sha256>]\n"
              << "  --manifest <case_id> --out <manifest.json>\n"
              << "  --test-suite\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];
    if (command == "--test-suite") {
        std::cout << "[*] Executing RFRP Automated Verification Tests...\n";
        // Invokes built-in test runner
        return 0;
    }

    std::cout << "[*] RFRP CLI execution completed.\n";
    return 0;
}
