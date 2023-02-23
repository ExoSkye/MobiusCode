//
// Created by kai on 21/02/23.
//

#ifndef MOBIUSCODE_PROGRAM_HPP
#define MOBIUSCODE_PROGRAM_HPP


#include <map>
#include "colour.hpp"
#include "../shared/vec2.hpp"

class Program {
private:
    std::map<vec2, Colour> data;

    Program() = delete;

public:
    explicit Program(const char* fpath);


    Colour& at(vec2 pos);
    void insert(Colour& c, vec2& pos);
};


#endif //MOBIUSCODE_PROGRAM_HPP
