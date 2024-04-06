#include "ArgumentParsing.h"

char* GetFilenameFromConsole (int argc, char** argv) {
    char* filename = nullptr;
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-i") && i + 1 < argc) {
            if (argv[i + 1] == nullptr || argv[i + 1][0] == '-') {
                std::cerr << "User error";
                return nullptr;
            } else {
                filename = argv[i + 1];
            }
        } else if (!strncmp("--input=", argv[i], 8)) {
            filename = argv[i] + 8;
        }
    }

    return filename;
}

char* GetPathToSaveImagesFromConsole (int argc, char** argv) {
    char* output_path = nullptr;
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-o") && i + 1 < argc) {
            if (argv[i + 1] == nullptr || argv[i+ 1][0] == '-') {
                std::cerr << "User error";
                return nullptr;
            } else {
                output_path = argv[i + 1];
            }
        } else if (!strncmp("--output=", argv[i], 9)) {
            output_path = argv[i] + 9;
        }
    }

    return output_path;
}

uint64_t GetMaxIterationsFromConsole (int argc, char** argv) {
    uint64_t max_iter = UINT64_MAX;
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-m") && i + 1 < argc) {
            if (argv[i + 1] == nullptr || argv[i + 1][0] == '-') {
                std::cerr << "User error";
                return EXIT_FAILURE;
            } else {
                char** p_end = nullptr;
                max_iter = std::strtoll(argv[i + 1], p_end, 10);
            }
        } else if (!strncmp("--max-iter=", argv[i], 11) && i + 1 < argc) {
            char** p_end = nullptr;
            max_iter = std::strtoll(argv[i] + 11, p_end, 10);
        }
    }

    return max_iter;
}

uint64_t GetFreqFromConsole (int argc, char** argv) {
    uint64_t freq = 0;
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-f") && i + 1 < argc) {
            if (argv[i + 1] == nullptr || argv[i + 1][0] == '-') {
                std::cerr << "User error";
                return EXIT_FAILURE;
            } else {
                char** p_end = nullptr;
                freq = std::strtoll(argv[i + 1], p_end, 10);
            }
        } else if (!strncmp("--freq=", argv[i], 7)) {
            char** p_end = nullptr;
            freq = std::strtoll(argv[i] + 7, p_end, 10);
        }
    }

    return freq;
}