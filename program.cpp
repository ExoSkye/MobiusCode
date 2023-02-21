//
// Created by kai on 21/02/23.
//

#include "program.hpp"

#define STBI_ONLY_BMP
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include "stb_image.h"

Program::Program(const char *fpath) {
    FILE* f = fopen(fpath, "r");
    int x, y, channels;
    u8* data = stbi_load_from_file(f, &x, &y, &channels, 4);

    if (data == nullptr) {
        printf("ERROR: Couldn't load image\nReason: %s", stbi_failure_reason());
        exit(-1);
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            this->data.insert_or_assign(vec2{i, j}, Colour(&data[j * y + i]));
        }
    }

    stbi_image_free(data);
}

Colour& Program::at(vec2 pos) {
    return this->data.at(pos);
}

void Program::insert(Colour c, vec2 pos) {
    this->data.insert_or_assign(pos, c);
}
