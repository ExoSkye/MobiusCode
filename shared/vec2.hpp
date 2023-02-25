//
// Created by kai on 21/02/23.
//

#ifndef MOBIUSCODE_VEC2_HPP
#define MOBIUSCODE_VEC2_HPP

#include "definitions.hpp"

class vec2 {
public:
    auto operator<=>(const vec2&) const = default;
    vec2 operator+(const vec2& other) const {
        return vec2 {
            other.x + x,
            other.y + y
        };
    };

    void operator+=(const vec2& other) {
        *this = *this + other;
    }

    s64 x;
    s64 y;
};

#endif //MOBIUSCODE_VEC2_HPP
