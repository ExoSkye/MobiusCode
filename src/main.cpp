#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <fcntl.h>
#include <csignal>

#include "../shared/definitions.hpp"
#include "endian.hpp"
#include "colour.hpp"
#include "../shared/vec2.hpp"
#include "program.hpp"
#include "tape.hpp"

#define C(r, g, b, a) ((u32)r << 24 | (u32)g << 16 | (u32)b << 8 | (u32)a)

void handle_filename_open(Tape* tape, u64 start, FILE** f) {
    u64 I = start;
    u64 len;

    while (tape->at(I) != 0) {
        len++;
        I++;
    }

    char* data = (char*)malloc(len);

    for (u64 i = 0; i < len; i++) {
        data[i] = tape->at(i + start);
        I++;
    }

    *f = fopen(data, "aw+");
}

u64 iter = 0;

void sigint_handler(int s) {
    printf("Iters run: %lu\n", iter);
    fflush(stdout);
    exit(0);
}

int main(int argc, char** argv) {
    signal(SIGINT, sigint_handler);

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

    // Registers

    vec2 C1, C2;
    s64 R1 = 1, R2 = 1;
    u64 I;
    int F, G;
    FILE* f, *g;
    u8 A1, A2, A3, A4;
    Colour C{0, 0, 0, 0};
    int S;
    u64 i;
    Tape tape;

    while (running) {
        iter += 1;
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
                std::swap(direction.x, direction.y);
                direction.x *= -1;
                break;

            case (C(0, 127, 63, 0)):
                if (R1 > 0)
                    direction = {0, 1};
                break;

            case (C(0, 63, 127, 0)):
                if (R1 > 0)
                    direction = {0, -1};
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
                program.insert(C, C1);
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
                f = fdopen(F, "aw+");
                break;

            case (C(255, 0, 0, 0)): // Open File G
                G = R1;
                g = fdopen(G, "aw+");
                break;

            case (C(0, 255, 0, 0)): // Close File F
                if (F == 1) {
                    fflush(f);
                } else if (F == 2) {
                    fflush(f);
                } else if (F != 0) {
                    fclose(f);
                }

                F = -1;
                break;

            case (C(0, 0, 255, 0)): // Close File G
                if (G == 1) {
                    fflush(g);
                } else if (G == 2) {
                    fflush(g);
                } else if (G != 0) {
                    fclose(g);
                }

                G = -1;
                break;

            case (C(255, 255, 0, 0)): // Write R1 to F
                fwrite(&R1, sizeof(R1), 1, f);
                break;

            case (C(0, 0, 255, 255)): // Read R1 from F
                fread(&R1, sizeof(R1), 1, f);
                break;

            case (C(255, 127, 0, 0)): // Write R1 to G
                fwrite(&R1, sizeof(R1), 1, g);
                break;

            case (C(0, 0, 127, 255)): // Read R1 from G
                fread(&R1, sizeof(R1), 1, g);
                break;

            // Tape operations

            case (C(63, 0, 0, 0)): // Inc I
                I++;
                break;

            case (C(0, 0, 0, 63)): // Dec I
                I--;
                break;

            case (C(0, 63, 0, 0)): // R1 = Tape[I]
                R1 = tape.at(I);
                break;

            case (C(0, 0, 63, 0)): // Tape[I] = R2
                tape.at(I) = R2;
                break;

            // File opens with filepath cos i'm an idiot

            case (C(127, 63, 127, 0)):
                handle_filename_open(&tape, I, &f);
                break;

            case (C(0, 127, 63, 127)):
                handle_filename_open(&tape, I, &g);
                break;

            default: // Assume NOP
                break;
        }

        tape.gc();

        if (!no_advance) {
            cur_cell += direction;
        }
    }

    return 0;
}
