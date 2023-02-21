#include <cstdio>
#include <cstdlib>

#include "definitions.hpp"
#include "endian.hpp"
#include "colour.hpp"
#include "vec2.hpp"
#include "program.hpp"

int main(int argc, char** argv) {
    Endian e = Big;
    bool debug = false;
    vec2 cur_cell = {0, 0};
    vec2 direction = {1, 0};

    if (argc < 2) {
        printf("Please provide a file\n");
    }

    char* debug_str = getenv("DEBUG");

    if (debug_str != nullptr) {
        debug = true;
    }

    Program program(argv[1]);



    return 0;
}
