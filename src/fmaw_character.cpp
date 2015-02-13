// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./fmaw_character.h"

#include "./FMAW.h"

namespace FMAW {

void Character::render(int camera_x, int camera_y) {
    FixedReal x, y;
    x = ((this->x - this->width) >> 8) - camera_x;
    y = ((this->y - this->height) >> 8) - camera_y;

    if (x <= -16 || y <= -16 || x >= 256 || y >= 192) {
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
