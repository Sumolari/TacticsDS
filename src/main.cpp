// Copyright 2015 FMAW

#include "./FMAW.h"  // Import our awesome framework!

//------------------------------------------------------------------------------
// Graphic references
//------------------------------------------------------------------------------

#include "./gfx_ball.h"
#include "./gfx_bg.h"
#include "./gfx_brick.h"
#include "./gfx_gradient.h"

//------------------------------------------------------------------------------
// Background...
//------------------------------------------------------------------------------

#define BACKDROP_COLOR RGB8(190, 255, 255)

//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

// Gravity constant (add to vertical velocity).
#define GRAVITY         FMAW::FixedReal(0.3125, 8)

// Friction in the air...
#define AIR_FRICTION    FMAW::FixedReal(0.3, 12)
// Friction when the ball hits ground.
#define GROUND_FRICTION FMAW::FixedReal(0.12, 8)
// The level of the brick platform.
#define PLATFORM_LEVEL  FMAW::FixedReal(144, 8)
// The amount of Y velocity that is absorbed when you hit the ground
#define BOUNCE_DAMPER   FMAW::FixedReal(0.08, 8)

#define BALL_RADIUS     FMAW::FixedReal(8, 8)
#define BALL_DIAM       16

#define MIN_HEIGHT      FMAW::FixedReal(4.7, 8)

#define MIN_YVEL        FMAW::FixedReal(4.7, 8)
#define MAX_XVEL        FMAW::FixedReal(3.9, 12)

#define X_TWEAK         FMAW::FixedReal(0.125, 12)
#define Y_TWEAK         FMAW::FixedReal(0.1, 8)

//------------------------------------------------------------------------------
// Ball class
//------------------------------------------------------------------------------

class Ball : public FMAW::Character {

  public:
    // X velocity.
    FMAW::FixedReal xvel;
    // Y velocity.
    FMAW::FixedReal yvel;

    /**
     * Creates a new ball using a new sprite.
     */
    Ball(): FMAW::Character(FMAW::Sprite())  {};

    /**
     * Creates a new ball given its sprite.
     */
    Ball(FMAW::Sprite sprite): FMAW::Character(sprite) {};

    /**
     * Updates this ball's position based on its velocity.
     */
    virtual void update();

    /**
     * Renders this ball in given frame.
     * @param camera_x [description]
     * @param camera_y [description]
     */
    virtual void render(int camera_x, int camera_y);
};

void Ball::update() {
    this->xvel *= FMAW::FixedReal(1, 12) - AIR_FRICTION;
    if (this->xvel < FMAW::FixedReal(0, 12) - MAX_XVEL) {
        this->xvel = FMAW::FixedReal(0, 12) - MAX_XVEL;
    } else if (this->xvel > MAX_XVEL) {
        this->xvel = MAX_XVEL;
    }
    this->x += FMAW::FixedReal(this->xvel.toDouble(), 8);

    this->yvel += GRAVITY;
    this->y += this->yvel;

    if (this->y + BALL_RADIUS >= PLATFORM_LEVEL) {
        this->xvel *= (FMAW::FixedReal(1, 8) - GROUND_FRICTION);
        // Check if the ball has been squished to minimum height.
        if (this->y > PLATFORM_LEVEL - MIN_HEIGHT) {
            // Mount Y on platform.
            this->y = PLATFORM_LEVEL - MIN_HEIGHT;
            // Negate Y velocity, also apply the bounce damper.
            this->yvel = FMAW::FixedReal(0, 8) -
                         (this->yvel * (FMAW::FixedReal(1, 8) - BOUNCE_DAMPER));
            if (this->yvel > FMAW::FixedReal(0, 8) - MIN_YVEL)
                this->yvel = FMAW::FixedReal(0, 8) - MIN_YVEL;
        }
        this->height = ((PLATFORM_LEVEL - this->y) * FMAW::FixedReal(2, 8)).toInt();
    } else {
        this->height = BALL_DIAM;
    }
}

void Ball::render(int camera_x, int camera_y) {
    int x, y;
    x = (this->getXPosition() - BALL_RADIUS * 2).toInt() - camera_x;
    y = (this->getYPosition() - BALL_RADIUS * 2).toInt() - camera_y;

    if (x <= -16 || y <= -16 || x >= 256 || y >= 192) {
        this->sprite.disable();
        return;
    }

    this->sprite.setPosition(x, y);
    this->sprite.setSizeMode(FMAW::square16x16);

    this->sprite.enableDoubleSize();

    FMAW::Transform t = FMAW::Transform(0);
    t.setIdentity();
    FMAW::FixedReal div = FMAW::FixedReal(1, 8) / FMAW::FixedReal(BALL_DIAM, 8);
    FMAW::FixedReal pa = FMAW::FixedReal(this->height, 8) * div;
    FMAW::FixedReal pd = FMAW::FixedReal(1, 8) / pa;
    t.applyScaling(pa, pd);

    this->sprite.applyTransform(t);
}

//------------------------------------------------------------------------------
// Game objects
//------------------------------------------------------------------------------

FMAW::FixedReal g_camera_x;
FMAW::FixedReal g_camera_y;

Ball g_ball;

//------------------------------------------------------------------------------
// Main code section
//------------------------------------------------------------------------------

/**
 * Sets up graphics.
 */
void setupGraphics(void) {
    FMAW::Tile ball_tile(FMAW::TileAttributes(
                             gfx_ballTiles,
                             gfx_ballTilesLen,
                             gfx_ballPal,
                             gfx_ballPalLen,
                             FMAW::TypeSprite,
                             FMAW::ScreenMain));

    FMAW::Tile bg_tile(FMAW::TileAttributes(
                           gfx_bgTiles,
                           gfx_bgTilesLen,
                           gfx_bgPal,
                           gfx_bgPalLen,
                           FMAW::TypeBackground,
                           FMAW::ScreenMain));

    FMAW::Tile brick_tile(FMAW::TileAttributes(
                              gfx_brickTiles,
                              gfx_brickTilesLen,
                              gfx_brickPal,
                              gfx_brickPalLen,
                              FMAW::TypeBackground,
                              FMAW::ScreenMain));

    FMAW::Tile gradient_tile(FMAW::TileAttributes(
                                 gfx_gradientTiles,
                                 gfx_gradientTilesLen,
                                 gfx_gradientPal,
                                 gfx_gradientPalLen,
                                 FMAW::TypeBackground,
                                 FMAW::ScreenMain));

    FMAW::setBackgroundColor(BACKDROP_COLOR);

    FMAW::Background bgBricks(0);
    bgBricks.setScreenBaseBlock(1);
    bgBricks.clearAllTiles();

    // Set tilemap entries for 6 first rows of background 0 (bricks).
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 32; x++) {
            int tile_id = x + y * 32;  // Product optimized at compile time!

            // Either odd columns of even rows or even columns of odd rows...
            // if (( x % 2 == 0 && y % 2 == 1 ) || (x % 2 == 1 && y % 2 == 0 ))
            if ((x & 1) ^ (y & 1))
                bgBricks.enableHorizontalFlip(tile_id);

            bgBricks.setTile(tile_id, brick_tile);
        }
    }
    // Did we say 6 first rows? We wanted 6 LAST rows!
    bgBricks.setVerticalOffset(112);

    FMAW::Background bgGradient(1);
    bgGradient.setScreenBaseBlock(2);
    bgGradient.clearAllTiles();

    // Set tilemap entries for 8 first rows of background 1 (gradient).
    for (int y = 0; y < 8; y++) {
        int tile_index = gradient_tile.imgMemory + y;
        int y32 = y * 32;

        for (int x = 0; x < 32; x++) {
            int tile_id = x + y32;
            bgGradient.setTile(tile_id, tile_index);
            bgGradient.setPalette(tile_id, gradient_tile.palMemory);
        }
    }

    FMAW::Background::useBackdropAsAlphaDst();
    bgGradient.useAsAlphaBlendingSrc();
    FMAW::Background::setAlphaBlendingMode(FMAW::babmAlphaBlending);
    FMAW::Background::setAlphaBlendingCoefficientOne(4);
    FMAW::Background::setAlphaBlendingCoefficientTwo(16);

    g_ball.sprite.setTile(ball_tile);
    g_ball.sprite.enable();
    g_ball.setPosition({128, 64});
    g_ball.update();
    g_ball.xvel = FMAW::FixedReal(0.39, 12);
    g_ball.yvel = FMAW::FixedReal(0, 8);
}

/**
 * Updates game logic.
 */
void update_logic() {
    FMAW::Timer::check();
    g_ball.update();
}

/**
 * Renders graphics.
 */
void update_graphics() {
    g_ball.render(g_camera_x.toInt(), g_camera_y.toInt());

    FMAW::Camera::setHorizontalOffset(g_camera_x);
}

/**
 * Main.
 */
int main(void) {
    FMAW::init(update_graphics, update_logic);
    setupGraphics();

    auto update_camera = [](int ID) {
        // Desired camera X:
        FMAW::FixedReal cx = g_ball.getXPosition() - FMAW::FixedReal(128, 8);

        // Difference between desired and current position.
        FMAW::FixedReal dx = cx - g_camera_x;

        if ((dx > FMAW::FixedReal(0.04, 8)) || (dx < FMAW::FixedReal(-0.04, 8))) {
            dx *= FMAW::FixedReal(0.005, 8);
        }

        g_camera_x += dx;
        g_camera_y = 0;
    };
    FMAW::Timer::enqueue_function(update_camera, 5, true);

    auto moveUp = []() {
        g_ball.yvel -= Y_TWEAK;
    };
    FMAW::Input::whileButtonArrowUpPressed(moveUp);

    auto moveDown = []() {
        g_ball.yvel += Y_TWEAK;
    };
    FMAW::Input::whileButtonArrowDownPressed(moveDown);

    auto moveLeft = []() {
        g_ball.xvel -= X_TWEAK;
    };
    FMAW::Input::whileButtonArrowLeftPressed(moveLeft);

    auto moveRight = []() {
        g_ball.xvel += X_TWEAK;
    };
    FMAW::Input::whileButtonArrowRightPressed(moveRight);

    FMAW::start();

    return 0;
}
