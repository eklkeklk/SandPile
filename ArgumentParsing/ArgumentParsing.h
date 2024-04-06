#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>

struct Arguments {
    const char* input_filename;
    const char* output_filename;
    uint64_t max_iter;
    uint64_t freq;
};

char* GetFilenameFromConsole (int argc, char** argv);

char* GetPathToSaveImagesFromConsole (int argc, char** argv);

uint64_t GetMaxIterationsFromConsole (int argc, char** argv);

uint64_t GetFreqFromConsole (int argc, char** argv);