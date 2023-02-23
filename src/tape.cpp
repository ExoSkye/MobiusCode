//
// Created by kai on 22/02/23.
//

#include "tape.hpp"

s64 &Tape::at(u64 idx) {
    if (!this->tape_data.contains(idx)) {
        this->tape_data[idx] = 0;
    }

    return this->tape_data.at(idx);
}

void Tape::gc() {
    for (auto ptr = this->tape_data.begin(); ptr != this->tape_data.end(); ptr++) {
        if (ptr->second == 0) {
            this->tape_data.erase(ptr);
        }
    }
}
