#pragma once
#include <iostream>
#include <fstream>
#include "../Sandpile/SandPile.h"

void SaveImage(const char*& output_filename, SandPile& sandpile); //function that saves sandpile in .bmp file

std::string GetNewPath(const char*& path);