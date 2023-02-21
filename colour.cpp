#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
//
// Created by kai on 21/02/23.
//

#include "colour.hpp"

u32 Colour::get(Endian e) const {
    if (e == Endian::Big) {
        return (r << 24 | g << 16 | b << 8 | a);
    } else {
        return (a << 24 | b << 16 | g << 8 | r);
    }
}

void Colour::set(u8 _r, u8 _g, u8 _b, u8 _a) {
    this->r = _r;
    this->g = _g;
    this->b = _b;
    this->a = _a;
}

Colour::Colour(u8 r, u8 g, u8 b, u8 a) {
    set(r, g, b, a);
}

Colour::Colour(u8 *data) {
    set(data[0], data[1], data[2], data[3]);
}

#pragma clang diagnostic pop