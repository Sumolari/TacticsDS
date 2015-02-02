// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./ball.h"

#include <nds.h>

void Ball::update() {
    this->x += (this->xvel >> 4);

    this->xvel = (this->xvel * (256 - AIR_FRICTION)) >> 8;
    this->xvel = FMAW::clampInt(this->xvel, -MAX_XVEL, MAX_XVEL);

    this->yvel += GRAVITY;
    this->y += this->yvel;

    if (this->y + BALL_RADIUS >= PLATFORM_LEVEL) {
        this->xvel = (this->xvel * (256 - GROUND_FRICTION)) >> 8;

        // Check if the ball has been squished to minimum height.
        if (this->y > PLATFORM_LEVEL - MIN_HEIGHT) {
            // Mount Y on platform.
            this->y = PLATFORM_LEVEL - MIN_HEIGHT;
            // Negate Y velocity, also apply the bounce damper.
            this->yvel = -(this->yvel * (256 - BOUNCE_DAMPER)) >> 8;

            if (this->yvel > -MIN_YVEL)
                this->yvel = -MIN_YVEL;
        }

        this->height = (PLATFORM_LEVEL - this->y) * 2;
    } else {
        this->height = BALL_DIAM << 8;
    }
}

void Ball::render(int camera_x, int camera_y) {
    FixedReal x, y;
    x = ((this->x - BALL_RADIUS * 2) >> 8) - camera_x;
    y = ((this->y - BALL_RADIUS * 2) >> 8) - camera_y;

    if (x <= -16 || y <= -16 || x >= 256 || y >= 192) {
        this->sprite.disable();
        return;
    }

    this->sprite.setPosition(x, y);
    this->sprite.setSizeMode(FMAW::square16x16);

    this->sprite.enableDoubleSize();

    FMAW::Transform t = FMAW::Transform(0);
    t.setIdentity();
    int pa = (this->height * (65536 / BALL_DIAM)) >> 16;
    int pd = 65536 / pa;
    t.applyScaling(pa, pd);

    this->sprite.applyTransform(t);
}

void Ball::print() {
    FMAW::printf("Ball using sprite:");
    this->sprite.print();
}
