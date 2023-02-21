//
// Created by kai on 21/02/23.
//

#include "program.hpp"

Colour &Program::at(vec2 pos) {
    return this->data.at(pos);
}

void Program::insert(Colour c, vec2 pos) {
    this->data.insert_or_assign(pos, c);
}

Program::Program(const char *fpath) {

}
