#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "definitions.hpp"
#include "endian.hpp"
#include "colour.hpp"
#include "vec2.hpp"

int main(int argc, char** argv) {
    Endian e = Big;
    bool debug = false;
    vec2 cur_cell;
    vec2 direction;

    if (argc < 2) {
        printf("Please provide a file\n");
    }

    char* debug_str = getenv("DEBUG");

    if (debug_str != nullptr) {
        debug = true;
    }



    return 0;
}
