#ifndef BALL_H
#define BALL_H

#include "./FMAW.h"

// Gravity constant (add to vertical velocity).
#define GRAVITY         FixedReal(0.3125)

// Friction in the air...
#define AIR_FRICTION    1
// Friction when the ball hits ground.
#define GROUND_FRICTION 30
// The level of the brick platform.
#define PLATFORM_LEVEL  FixedReal(144)
// The amount of Y velocity that is absorbed when you hit the ground
#define BOUNCE_DAMPER   20

#define BALL_RADIUS     FixedReal(8)
#define BALL_DIAM       16

#define MIN_HEIGHT      FixedReal(4.7)

#define MIN_YVEL        FixedReal(4.7)
#define MAX_XVEL        BasicFixedReal<12>(3.9)

class Ball {

public:
    // X coordinate.
    FixedReal x;
    // Y coordinate.
    FixedReal y;
    // X velocity.
    BasicFixedReal<12> xvel;
    // Y velocity.
    FixedReal yvel;

    // Ball sprite.
    FMAW::Sprite sprite;

    // Height.
    FixedReal height;

    /**
     * Creates a new ball using a new sprite.
     */
    Ball(): sprite(FMAW::Sprite())  {};

    /**
     * Creates a new ball given its sprite.
     */
    Ball(FMAW::Sprite sprite): sprite(sprite) {};

    /**
     * Updates this ball's position based on its velocity.
     */
    void update();

    /**
     * Renders this ball in given frame.
     * @param camera_x [description]
     * @param camera_y [description]
     */
    void render(int camera_x, int camera_y);

    /**
     * Displays information about this ball.
     */
    void print();
};

#endif