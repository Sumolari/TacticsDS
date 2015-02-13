#ifndef FMAW_CHARACTER_H
#define FMAW_CHARACTER_H

#include "./fmaw_debug.h"
#include "./fmaw_types.h"
#include "./fmaw_sprite.h"

namespace FMAW {

class Character {
protected:
    // Width of the character.
    int width;
    // Height of the character.
    int height;
    // X coordinate.
    FixedReal x;
    // Y coordinate.
    FixedReal y;
    // Sprite of this bug.
    FMAW::Sprite sprite;

    /**
     * Initializes this character.
     */
    virtual void init() = 0;

public:
    /**
     * Creates a new character using a new sprite.
     */
    Character(): sprite(FMAW::Sprite()) {};

    /**
     * Creates a new character given its sprite.
     */
    Character(FMAW::Sprite sprite): sprite(sprite) {
        FMAW::printf("Character will be forced to use sprite %d", sprite.id);
    };

    /**
     * Updates this character's attribute.
     * This method should be called manually once per frame.
     */
    virtual void update() = 0;

    /**
     * Renders this character in given frame.
     * @param camera_x Position of the camera in the X-axis.
     * @param camera_y Position of the camera in the Y-axis.
     */
    virtual void render(int camera_x, int camera_y);

    /**
     * Displays information about this character.
     */
    virtual void print();
};

}

#endif