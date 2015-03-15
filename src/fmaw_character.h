#ifndef FMAW_CHARACTER_H
#define FMAW_CHARACTER_H

#include "./fmaw_debug.h"
#include "./fmaw_types.h"
#include "./fmaw_sprite.h"

#include <map>
#include <functional>

namespace FMAW {

typedef enum {
    ATLinear = 0
} AnimationType;

typedef int animation_id;

typedef struct t_animation {
    /**
     * ID of this callback.
     */
    int ID;
    /**
     * ID of this callback when registered with Timer API.
     */
    int callback_id;
    /**
     * Position of the Character when animation started.
     */
    Point initialPosition;
    /**
     * Final position of the Character.
     */
    Point finalPosition;
    /**
     * Duration of the animation, in milliseconds.
     */
    unsigned int duration;
    /**
     * Remaining duration of the animation, in milliseconds.
     */
    unsigned int remainingDuration;
    /**
     * Type of animation to perform.
     */
    AnimationType type;
    /**
     * Callback to be called when animation is finished.
     */
    std::function<void(bool)> callback;
} Animation;

class Character {
  protected:
    // Width of the character.
    int width;
    // Height of the character.
    int height;
    // Animations to be performed.
    std::map<animation_id, Animation> animations;
    // X coordinate.
    FixedReal x;
    // Y coordinate.
    FixedReal y;
    /**
     * Initializes this character.
     */
    virtual void init();

  public:
    // Sprite of this character.
    FMAW::Sprite sprite;

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
     * Sets X position of this character.
     * @param x New X coordinate.
     */
    virtual void setXPosition(FixedReal x);

    /**
     * Sets Y position of this character.
     * @param y New Y coordinate.
     */
    virtual void setYPosition(FixedReal y);

    /**
     * Sets new position of this character.
     * @param x New X coordinate.
     * @param y New Y coordinate.
     */
    virtual void setPosition(FixedReal x, FixedReal y);

    /**
     * Sets X and Y position of this character.
     * @param position New position.
     */
    virtual void setPosition(Point position);

    /**
     * Moves this character to given position animatedly.
     * @param position Final position of the character.
     * @param duration Time it'll take to move the character.
     * @return         Identifier of the animation that will be performed.
     */
    animation_id animateToPosition(Point position, unsigned int duration);

    /**
     * Moves this character to given position animatedly.
     * @param position Final position of the character.
     * @param duration Time it'll take to move the character.
     * @param callback Function that will be called when animation finishes.
     *                 It'll receive whether animation finished successfully
     *                 (true) or not (false).
     */
    animation_id animateToPosition(Point position, unsigned int duration,
                                   std::function<void(bool)> callback);

    /**
     * Moves this character to given position animatedly.
     * @param position Final position of the character.
     * @param duration Time it'll take to move the character.
     * @param type     Type of animation to be performed.
     * @param callback Function that will be called when animation finishes.
     *                 It'll receive whether animation finished successfully
     *                 (true) or not (false).
     */
    animation_id animateToPosition(Point position, unsigned int duration,
                                   AnimationType type,
                                   std::function<void(bool)> callback);

    /**
     * Cancels animation with given ID.
     * @param  id ID of animation to cancel.
     * @return    Whether animation was cancelled or not.
     */
    bool cancelAnimation(animation_id id);

    /**
     * Returns current X position of this character.
     * @return Current X position of this character.
     */
    virtual FixedReal getXPosition();

    /**
     * Returns current Y position of this character.
     * @return Current Y position of this character.
     */
    virtual FixedReal getYPosition();

    /**
     * Returns current position of this character.
     * @return Current position of this character.
     */
    virtual Point getPosition();

    /**
     * Updates this character's attribute.
     * This method should be called manually once per frame.
     */
    virtual void update();

    /**
     * Renders this character in Zero frame.
     */
    virtual void render();

    /**
     * Renders this character in given frame.
     * @param camera_x Position of the camera in the X-axis.
     * @param camera_y Position of the camera in the Y-axis.
     */
    virtual void render(FixedReal camera_x, FixedReal camera_y);

    /**
     * Displays information about this character.
     */
    virtual void print();

    virtual ~Character();
};

}

#endif