#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <fcntl.h>

#include "definitions.hpp"
#include "endian.hpp"
#include "colour.hpp"
#include "vec2.hpp"
#include "program.hpp"

#define C(r, g, b, a) ((u32)r << 24 | (u32)g << 16 | (u32)b << 8 | (u32)a)

int main(int argc, char** argv) {
    Endian e = Big;
    bool debug = false;
    vec2 cur_cell = {0, 0};
    vec2 direction = {1, 0};
    bool no_advance = false; // Used in gotos

    if (argc < 2) {
        printf("Please provide a file\n");
    }

    char* debug_str = getenv("DEBUG");

    if (debug_str != nullptr) {
        debug = true;
    }

    Program program(argv[1]);
    bool running = true;

    vec2 C1, C2;
    s64 R1, R2;
    u64 I;
    int F, G;
    u8 A1, A2, A3, A4;
    Colour C{0, 0, 0, 0};
    int S;
    FILE* fw, *fr, *gw, *gr;

    while (running) {
        Colour& current_colour = program.at(cur_cell);

        switch (current_colour.get(e)) {
            // NOP - do nothing
            case (C(0, 0, 0, 0)):
                break;

            // Control instructions

            case (C(255, 0, 0, 255)): // Exit
                running = false;
                break;

            case (C(0, 127, 0, 0)): // Goto C1
                cur_cell = C1;
                no_advance = true;
                break;

            case (C(0, 0, 127, 0)): // Goto C2
                cur_cell = C2;
                no_advance = true;
                break;

            case (C(0, 127, 127, 0)): // Turn 90 degrees right
                direction.x = (direction.x * cos(M_PI / 2)) - (direction.y * sin(M_PI / 2));
                direction.y = (direction.y * cos(M_PI / 2)) + (direction.x * sin(M_PI / 2));
                break;

            // Self modification

            case (C(127, 0, 127, 0)): // Save C1
                C1 = cur_cell;
                break;

            case (C(0, 127, 0, 127)): // Save C2
                C2 = cur_cell;
                break;

            case (C(63, 0, 63, 0)): // C1 = C2
                C1 = C2;
                break;

            case (C(0, 63, 0, 63)): // C2 = C1
                C2 = C1;
                break;

            case (C(255, 255, 255, 0)): // C1.rgba = C.rgba
                program.insert(current_colour, C1);
                break;

            // Arithmetic

            case (C(63, 127, 0, 0)): // R1 = R1 + R2
                R1 = R1 + R2;
                break;

            case (C(0, 0, 127, 63)): // R1 = R1 - R2
                R1 = R1 - R2;
                break;

            case (C(0, 63, 63, 0)): // Swap R1 and R2
                std::swap(R1, R2);
                break;

            case (C(63, 0, 0, 63)): // Set R1 = R2
                R1 = R2;
                break;

            // File I/O

            case (C(0, 0, 0, 255)): // Open File F
                F = R1;
                break;

            case (C(255, 0, 0, 0)): // Open File G
                G = R1;
                break;

            case (C(0, 255, 0, 0)): // Close File F
                F = -1;
                break;

            case (C(0, 0, 255, 0)): // Close File G
                G = -1;
                break;

            case (C(255, 255, 0, 0)): // Write R1 to F
                fw = fdopen(F, "w");
                fwrite(&R1, sizeof(R1), 1, fw);
                fclose(fw);
                break;

            case (C(0, 0, 255, 255)): // Read R1 from F
                fr = fdopen(F, "r");
                fread(&R1, sizeof(R1), 1, fr);
                fclose(fr);
                break;

            case (C(255, 127, 0, 0)): // Write R1 to G
                gw = fdopen(G, "w");
                fwrite(&R1, sizeof(R1), 1, gw);
                fclose(gw);
                break;

            case (C(0, 0, 127, 255)): // Read R1 from G
                gr = fdopen(F, "r");
                fread(&R1, sizeof(R1), 1, gr);
                fclose(gr);
                break;

            default: // Assume NOP
                break;
        }
    }

    return 0;
}
