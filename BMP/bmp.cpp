#include "bmp.h"

std::string GetNewPath(const char*& path) {
    static int number_of_pictures = 0;
    number_of_pictures++;
    std::string new_path = static_cast<std::string>(path) + "/sandpile_" + std::to_string(number_of_pictures) + ".bmp";

    return new_path;
}

void SaveImage(const char*& output_filename, SandPile& sandpile) {
    std::ofstream bmp_file;
    bmp_file.open(GetNewPath(output_filename), std::ios_base::binary);
    if (!bmp_file) {
        std::cerr << "Error: can't open output file" << std::endl;
        exit(1);
    }

    uint8_t bmp_file_info_long[4]; //for info that take 4 cells
    uint8_t bmp_file_info[2]; //for info that take 2 cells (short)

    const int32_t file_header = 14; //14 info cells
    const int32_t info_header = 40; //40 info cells
    const int32_t colour_table = 20; //20 info cells
    const int32_t number_of_bits = 4; //number of bits for every pixel
    const int32_t number_of_colours = 5; //number of colours

    bmp_file_info[0] = 'B'; //Type
    bmp_file_info[1] = 'M';
    bmp_file << bmp_file_info[0] << bmp_file_info[1];

    uint16_t image_height = sandpile.height;
    if (image_height % 8 != 0) {
        image_height = image_height + 8 - (image_height % 8);
    }

    int64_t file_size = file_header + info_header + colour_table + (image_height * sandpile.width) / 2; //Size
    bmp_file_info_long[3] = static_cast<uint8_t>(file_size >> 8 >> 8 >> 8);
    file_size = file_size % (256 * 256 * 256);
    bmp_file_info_long[2] = static_cast<uint8_t>(file_size >> 8 >> 8);
    file_size = file_size % (256 * 256);
    bmp_file_info_long[1] = static_cast<uint8_t>(file_size >> 8);
    file_size = file_size % (256 * 256);
    bmp_file_info_long[0] = static_cast<uint8_t>(file_size);
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info[0] = 0;
    bmp_file_info[1] = 0;
    bmp_file << bmp_file_info[0] << bmp_file_info[1]; //Reserved 1
    bmp_file << bmp_file_info[0] << bmp_file_info[1]; //Reserved 2

    bmp_file_info_long[0] = static_cast<uint8_t>(file_header + info_header + colour_table);
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info_long[0] = static_cast<uint8_t>(info_header); //Info size
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    int32_t tmp;
    tmp = sandpile.height;
    bmp_file_info_long[3] = static_cast<uint8_t>(tmp >> 8 >> 8 >> 8);
    tmp = tmp % (256 * 256 * 256);
    bmp_file_info_long[2] = static_cast<uint8_t>(tmp >> 8 >> 8);
    tmp = tmp % (256 * 256);
    bmp_file_info_long[1] = static_cast<uint8_t>(tmp >> 8);
    tmp = tmp % (256 * 256);
    bmp_file_info_long[0] = static_cast<uint8_t>(tmp);
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    tmp = sandpile.width;
    bmp_file_info_long[3] = static_cast<uint8_t>(tmp >> 8 >> 8 >> 8);
    tmp = tmp % (256 * 256 * 256);
    bmp_file_info_long[2] = static_cast<uint8_t>(tmp >> 8 >> 8);
    tmp = tmp % (256 * 256);
    bmp_file_info_long[1] = static_cast<uint8_t>(tmp >> 8);
    tmp = tmp % (256 * 256);
    bmp_file_info_long[0] = static_cast<uint8_t>(tmp);
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info[0] = 1; //Planes
    bmp_file_info[1] = 0;
    bmp_file << bmp_file_info[0] << bmp_file_info[1];

    bmp_file_info[0] = static_cast<uint8_t>(number_of_bits); //Number of bits
    bmp_file_info[1] = 0;
    bmp_file << bmp_file_info[0] << bmp_file_info[1];

    bmp_file_info_long[0] = 0; //Compression
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info_long[0] = 0; //Image size
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info_long[0] = 0; //X pixels per meter
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info_long[0] = 0; //Y pixels per meter
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info_long[0] = static_cast<uint8_t>(number_of_colours); //Number of used colours
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    bmp_file_info_long[0] = static_cast<uint8_t>(number_of_colours); //Number of important colours
    bmp_file_info_long[1] = 0;
    bmp_file_info_long[2] = 0;
    bmp_file_info_long[3] = 0;
    bmp_file << bmp_file_info_long[0] << bmp_file_info_long[1] << bmp_file_info_long[2] << bmp_file_info_long[3];

    uint8_t white[] = {255, 255, 255, 0};
    bmp_file << white[0] << white[1] << white[2] << white[3];
    uint8_t green[] = {0, 255, 0, 0};
    bmp_file << green[0] << green[1] << green[2] << green[3];
    uint8_t yellow[] = {0, 255, 255, 0};
    bmp_file << yellow[0] << yellow[1] << yellow[2] << yellow[3];
    uint8_t purple[] = {255, 0, 255, 0};
    bmp_file << purple[0] << purple[1] << purple[2] << purple[3];
    uint8_t black[] = {0, 0, 0, 0};
    bmp_file << black[0] << black[1] << black[2] << black[3];

    uint8_t two_pixels; //8 bits for 2 pixels
    uint8_t first_pixel;
    uint8_t second_pixel;
    for (int i = static_cast<int16_t>(sandpile.width - 1); i >= 0; --i) {
        for (uint16_t j = 0; j < image_height; j += 2) {
            if (j >= sandpile.height) {
                first_pixel = 0;
                second_pixel = 0;
            } else if ((j + 1 >= sandpile.height)) {
                if (sandpile.field[i][j] > 4) { //compress number of sand if it's more than 4
                    first_pixel = 4;
                } else {
                    first_pixel = sandpile.field[i][j];
                }
                second_pixel = 0;
            } else {
                if (sandpile.field[i][j] > 4) {
                    first_pixel = 4;
                } else {
                    first_pixel = sandpile.field[i][j];
                }
                if (sandpile.field[i][j + 1] > 4) {
                    second_pixel = 4;
                } else {
                    second_pixel = sandpile.field[i][j + 1];
                }
            }
            two_pixels = (first_pixel << 4) + second_pixel; //4 bits for first pixel and another 4 for second pixel
            bmp_file << two_pixels;
        }
    }
}