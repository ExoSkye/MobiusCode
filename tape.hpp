//
// Created by kai on 22/02/23.
//

#ifndef MOBIUSCODE_TAPE_HPP
#define MOBIUSCODE_TAPE_HPP


#include <map>
#include "definitions.hpp"

class Tape {
private:
    std::map<u64, s64> tape_data;

public:
    s64& at(u64 idx);
    void gc();
};


#endif //MOBIUSCODE_TAPE_HPP
