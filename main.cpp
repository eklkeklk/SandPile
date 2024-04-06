#include "ArgumentParsing/ArgumentParsing.h"
#include "BMP/bmp.h"

int main(int argc, char** argv) {
    Arguments args{};
    args.input_filename = GetFilenameFromConsole(argc, argv);
    args.output_filename = GetPathToSaveImagesFromConsole(argc, argv);
    args.freq = GetFreqFromConsole(argc, argv);
    args.max_iter = GetMaxIterationsFromConsole(argc, argv);
    SandPile sandpile = ParseTSV(args.input_filename);
    uint64_t counter = 0;
    while (counter <= args.max_iter) {
        counter++;
        ScatterSandpile(sandpile);
        if (Topple(sandpile)) {
            break;
        } else if (args.freq != 0 && counter % args.freq == 0) {
            SaveImage(args.output_filename, sandpile);
        }
    }
    SaveImage(args.output_filename, sandpile);
    for (int16_t i = 0; i < sandpile.width; i++) {
        delete[] sandpile.field[i];
    }
    delete[] sandpile.field;
    return 0;
}

