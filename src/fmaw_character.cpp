// Copyright 2015 FMAW

#include "./fmaw_character.h"

#include "./FMAW.h"

namespace FMAW {

void Character::render(FixedReal camera_x, FixedReal camera_y) {
    FixedReal x, y;
    x = (this->x - FixedReal(this->width, 8)) - camera_x;
    y = (this->y - FixedReal(this->height, 8)) - camera_y;

    if (x <= FixedReal(-16, 8) || y <= FixedReal(-16, 8) ||
            x >= FixedReal(256, 8) || y >= FixedReal(192, 8)) {
        this->sprite.disable();
        return;
    }

    this->sprite.setPosition(x, y);
}

void Character::print() {
    FMAW::printf("Character using sprite:");
    this->sprite.print();
}

}  // namespace FMAW
