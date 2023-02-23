#include <map>
#include <cstdio>
#include <cstring>
#include <csignal>
#include <cstdlib>
#include "vec2.hpp"
#include "definitions.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


struct Colour {
    auto operator<=>(const Colour&) const = default;

    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

FILE* f = nullptr;

void write_func(void *context, void *data, int size) {
    fwrite(data, size, 1, f);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Please provide a filename (or `-` for stdout)\n");
        return -1;
    }

    std::map<vec2, Colour> map;

    Colour c;
    vec2 pos;

    while (true) {
        int res = scanf("%li %li: %hhi %hhi %hhi %hhi\n", &pos.x, &pos.y, &c.r, &c.g, &c.b, &c.a);

        if (res != 6) {
            break;
        }

        map[pos] = c;
    }

    u64 max_x = 0, max_y = 0;

    for (auto pair : map) {
        max_x = std::max(max_x, pair.first.x);
        max_y = std::max(max_y, pair.first.y);
    }

    u8* data = (u8*)malloc(sizeof(u8) * max_x * max_y * 4);

    for (auto pair : map) {
        data[max_y * pair.first.y + pair.first.x * 4] = pair.second.r;
        data[max_y * pair.first.y + pair.first.x * 4 + 1] = pair.second.g;
        data[max_y * pair.first.y + pair.first.x * 4 + 2] = pair.second.b;
        data[max_y * pair.first.y + pair.first.x * 4 + 3] = pair.second.a;
    }

    if (*argv[1] == '-') {
        f = stdout;
    } else {
        f = fopen(argv[1], "w+");
    }

    stbi_write_png_compression_level = 0;

    stbi_write_png_to_func(write_func, nullptr, max_x, max_y, 4, data, 0);

    fflush(f);

    if (f != stdout) {
        fclose(f);
    }

    exit(0);
}