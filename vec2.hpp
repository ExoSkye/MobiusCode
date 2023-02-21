//
// Created by kai on 21/02/23.
//

#ifndef MOBIUSCODE_VEC2_HPP
#define MOBIUSCODE_VEC2_HPP

class vec2 {
public:
    auto operator<=>(const vec2&) const = default;

    s64 x;
    s64 y;
};

#endif //MOBIUSCODE_VEC2_HPP
