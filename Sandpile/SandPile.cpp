#include "SandPile.h"

SandPile ParseTSV(const char*& input_filename) {
    SandPile sandpile{};
    std::ifstream tsv_file(input_filename);
    if (!tsv_file.is_open()) {
        std::cerr << "Error: programme can't open this .tsv file";
        exit(1);
    }
    Point current{};
    auto** tmp = new uint64_t*[INT16_MAX];
    for (uint16_t i = 0; i < INT16_MAX; i++) {
        tmp[i] = new uint64_t [INT16_MAX];
    }
    for (int16_t i = 0; i < INT16_MAX; i++) {
        for (int16_t j = 0; j < INT16_MAX; j++) {
            tmp[i][j] = 0;
        }
    }
    while (tsv_file >> current.x >> current.y >> current.sand) {
        if (current.x + 1 > sandpile.width) {
            sandpile.width++;
        }
        if (current.y + 1 > sandpile.height) {
            sandpile.height++;
        }
        tmp[current.x][current.y] = current.sand;
    }
    if (sandpile.width < 1) {
        sandpile.width = 1;
    }
    if (sandpile.height < 1) {
        sandpile.height = 1;
    }
    sandpile.field = new uint64_t*[sandpile.width];
    for (int16_t i = 0; i < sandpile.width; i++) {
        sandpile.field[i] = new uint64_t[sandpile.height];
    }
    for (int16_t i = 0; i < sandpile.width; i++) {
        for (int16_t j = 0; j < sandpile.height; j++) {
            sandpile.field[i][j] = tmp[i][j];
        }
    }
    for (int16_t i = 0; i < INT16_MAX; i++) {
        delete[] tmp[i];
    }
    delete[] tmp;
    tsv_file.close();


    return sandpile;
}

bool Topple(SandPile& sandPile) {
    for (int16_t i = 0; i < sandPile.width; i++) {
        for (int16_t j = 0; j < sandPile.height; j++) {
            if (sandPile.field[i][j] >= 4) {
                return false;
            }
        }
    }

    return true;
}

uint64_t** IncreaseFieldUp(uint64_t**& matrix, int16_t width, int16_t height) {
    height = static_cast<int16_t>(height + 1);
    auto** new_matrix = new uint64_t*[width];
    for (int16_t i = 0; i < width; i++) {
        new_matrix[i] = new uint64_t[height];
    }
    for (int16_t i = 0; i < width; i++) {
        for (int16_t j = 1; j < height; j++) {
            new_matrix[i][j] = matrix[i][j - 1];
        }
    }
    for (int16_t i = 0; i < width; i++) {
        new_matrix[i][0] = 0;
    }
    for (int16_t i = 0; i < width; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return new_matrix;
}

uint64_t** IncreaseFieldDown(uint64_t**& matrix, int16_t width, int16_t height) {
    height = static_cast<int16_t>(height + 1);
    auto** new_matrix = new uint64_t*[width];
    for (int16_t i = 0; i < width; i++) {
        new_matrix[i] = new uint64_t[height];
    }
    for (int16_t i = 0; i < width; i++) {
        for (int16_t j = 0; j < height - 1; j++) {
            new_matrix[i][j] = matrix[i][j];
        }
    }
    for (int16_t i = 0; i < width; i++) {
        new_matrix[i][height - 1] = 0;
    }
    for (int16_t i = 0; i < width; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return new_matrix;
}

uint64_t** IncreaseFieldLeft(uint64_t**& matrix, int16_t width, int16_t height) {
    width = static_cast<int16_t>(width + 1);
    auto** new_matrix = new uint64_t*[width];
    for (int16_t i = 0; i < width; i++) {
        new_matrix[i] = new uint64_t[height];
    }
    for (int16_t i = 1; i < width; i++) {
        for (int16_t j = 0; j < height; j++) {
            new_matrix[i][j] = matrix[i - 1][j];
        }
    }
    for (int16_t j = 0; j < height; j++) {
        new_matrix[0][j] = 0;
    }
    for (int16_t i = 0; i < width - 1; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return new_matrix;
}

uint64_t** IncreaseFieldRight(uint64_t**& matrix, int16_t width, int16_t height) {
    width = static_cast<int16_t>(width + 1);
    auto** new_matrix = new uint64_t*[width];
    for (int16_t i = 0; i < width; i++) {
        new_matrix[i] = new uint64_t[height];
    }
    for (int16_t i = 0; i < width - 1; i++) {
        for (int16_t j = 0; j < height; j++) {
            new_matrix[i][j] = matrix[i][j];
        }
    }
    for (int16_t j = 0; j < height; j++) {
        new_matrix[width - 1][j] = 0;
    }
    for (int16_t i = 0; i < width - 1; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return new_matrix;
}

void ScatterSandpile(SandPile& sandpile) {
    auto** matrix = new uint64_t*[sandpile.width];
    for (int16_t i = 0; i < sandpile.width; i++) {
        matrix[i] = new uint64_t[sandpile.height];
    }
    for (int16_t i = 0; i < sandpile.width; i++) {
        for (int16_t j = 0; j < sandpile.height; j++) {
            matrix[i][j] = sandpile.field[i][j];
        }
    }
    int32_t difference_of_width_left = 0;
    int32_t difference_of_height_up = 0;
    int32_t difference_of_width_right = 0;
    int32_t difference_of_height_down = 0;
    for (int16_t i = 0; i < sandpile.width; i++) {
        for (int16_t j = 0; j < sandpile.height; j++) {
            if (sandpile.field[i][j] >= 4) {
                if (j - 1 + difference_of_height_up < 0) {
                    matrix = IncreaseFieldUp(matrix, static_cast<int16_t>(sandpile.width + difference_of_width_left + difference_of_width_right), static_cast<int16_t>(sandpile.height + difference_of_height_up + difference_of_height_down));
                    difference_of_height_up++;
                }
                if (i - 1 + difference_of_width_left < 0) {
                    matrix = IncreaseFieldLeft(matrix, static_cast<int16_t>(sandpile.width + difference_of_width_left + difference_of_width_right), static_cast<int16_t>(sandpile.height + difference_of_height_up + difference_of_height_down));
                    difference_of_width_left++;
                }
                if (i + 1 >= sandpile.width + difference_of_width_right) {
                    matrix = IncreaseFieldRight(matrix, static_cast<int16_t>(sandpile.width + difference_of_width_left + difference_of_width_right), static_cast<int16_t>(sandpile.height + difference_of_height_up + difference_of_height_down));
                    difference_of_width_right++;
                }
                if (j + 1 >= sandpile.height + difference_of_height_down) {
                    matrix = IncreaseFieldDown(matrix, static_cast<int16_t>(sandpile.width + difference_of_width_left + difference_of_width_right), static_cast<int16_t>(sandpile.height + difference_of_height_up + difference_of_height_down));
                    difference_of_height_down++;
                }
                matrix[i + difference_of_width_left][j + difference_of_height_up] -= 4;
                matrix[i - 1 + difference_of_width_left][j + difference_of_height_up]++;
                matrix[i + 1 + difference_of_width_left][j + difference_of_height_up]++;
                matrix[i + difference_of_width_left][j - 1 + difference_of_height_up]++;
                matrix[i + difference_of_width_left][j + 1 + difference_of_height_up]++;
            }
        }
    }
    sandpile.width = static_cast<int16_t>(sandpile.width + difference_of_width_left + difference_of_width_right);
    sandpile.height = static_cast<int16_t>(sandpile.height + difference_of_height_up + difference_of_height_down);
    for (int16_t i = 0; i < static_cast<int16_t>(sandpile.width - difference_of_width_left - difference_of_width_right); i++) {
        delete[] sandpile.field[i];
    }
    delete[] sandpile.field;
    sandpile.field = new uint64_t*[sandpile.width];
    for (int16_t i = 0; i < sandpile.width; i++) {
        sandpile.field[i] = new uint64_t[sandpile.height];
    }
    for (int16_t i = 0; i < sandpile.width; i++) {
        for (int16_t j = 0; j < sandpile.height; j++) {
            sandpile.field[i][j] = matrix[i][j];
        }
    }
    for (int16_t i = 0; i < sandpile.width; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}