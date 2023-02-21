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
