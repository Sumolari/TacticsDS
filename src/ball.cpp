// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./ball.h"

#include <nds.h>

void Ball::update() {
    this->x += FixedReal(this->xvel.toDouble());

    this->xvel *= 256 - AIR_FRICTION;
    this->xvel /= 256;
    this->xvel = FMAW::clampBasicFixedReal(this->xvel, -MAX_XVEL, MAX_XVEL);

    this->yvel += GRAVITY;
    this->y += this->yvel;


    if (this->y + BALL_RADIUS >= PLATFORM_LEVEL) {
        this->xvel *= 256 - GROUND_FRICTION;
        this->xvel /= 256;
        this->y = PLATFORM_LEVEL - BALL_RADIUS;
        this->yvel *= 256 - BOUNCE_DAMPER;
        this->yvel /= 256;
        this->yvel = FixedReal(-this->yvel.toDouble());

        if (this->yvel.toDouble() > -MIN_YVEL.toDouble())
            this->yvel = -MIN_YVEL;

    }
}

void Ball::render(int camera_x, int camera_y) {
    FixedReal x, y;
    x = (this->x - BALL_RADIUS) - FixedReal(camera_x);
    y = (this->y - BALL_RADIUS) - FixedReal(camera_y);

    if (x <= 0 || y <= 0 || x >= 256 || y >= 192) {
        this->sprite.disable();
        return;
    }

    this->sprite.setPosition(x.toInt(), y.toInt());
    this->sprite.setSizeMode(FMAW::square16x16);
}

void Ball::print() {
    FMAW::printf("Ball using sprite:");
    this->sprite.print();
}
