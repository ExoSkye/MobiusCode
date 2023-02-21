//
// Created by kai on 21/02/23.
//

#ifndef MOBIUSCODE_COLOUR_HPP
#define MOBIUSCODE_COLOUR_HPP


#include "definitions.hpp"
#include "endian.hpp"
#include <compare>

class Colour {
public:
    Colour(u8 r, u8 g, u8 b, u8 a);
    explicit Colour(u8* data);
    void set(u8 r, u8 g, u8 b, u8 a);
    [[nodiscard]] u32 get(Endian e) const;
    auto operator<=>(const Colour&) const = default;

private:
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};


#endif //MOBIUSCODE_COLOUR_HPP
