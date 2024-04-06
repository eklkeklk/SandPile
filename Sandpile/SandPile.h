#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

struct SandPile { //sandpile model's struct with dynamic two-dim array and its width and length
    uint64_t** field;
    int16_t width;
    int16_t height;

    SandPile(int16_t _width = 0, int16_t _height = 0) : width(_width), height(_height), field(nullptr) {}
};

struct Point { //struct with field's points coordinates
    int16_t x;
    int16_t y;
    uint64_t sand;
};

SandPile ParseTSV(const char*& input_filename); //function, that processes field's condition in the beginning

void ScatterSandpile(SandPile& sandpile); //function that scatters sandpile's model

uint64_t** IncreaseFieldUp(uint64_t**& matrix, int16_t width, int16_t length); //function that increases sandpile's field

uint64_t** IncreaseFieldDown(uint64_t**& matrix, int16_t width, int16_t length); //function that increases sandpile's field

uint64_t** IncreaseFieldLeft(uint64_t**& matrix, int16_t width, int16_t length); //function that increases sandpile's field

uint64_t** IncreaseFieldRight(uint64_t**& matrix, int16_t width, int16_t length); //function that increases sandpile's field

bool Topple(SandPile& sandPile);