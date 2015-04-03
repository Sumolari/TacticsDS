#ifndef FMAW_SOUND_H
#define FMAW_SOUND_H

#include <map>

namespace FMAW {

namespace Sound {

typedef unsigned int playID;

typedef struct FX {
    // MaxMod, low-level ID.
    unsigned int id;
    short unsigned int rate;
    short unsigned int handle;
    unsigned char volume;
    unsigned char panning;
} FX;

FX effectWithSoundID(int ID);

/**
 * Initializes sound API.
 */
void init();

/**
 * Registers given special effect.
 * @param  fx Effect to register.
 * @return    ID of registered FX.
 */
int registerFX(FX fx);

/**
 * Starts playing given special effect, will return an identifier to cancel this
 * exact reproduction.
 * @param  effectID ID of special effect to play.
 * @return          ID of this reproduction, so it can be cancelled later.
 */
playID playEffect(int effectID);

/**
 * Stops playing given reproduction of special effect.
 * @param  reproductionID ID of reproduction to stop.
 * @return                Whether reproduction has been stopped or not.
 */
bool stopEffect(playID reproductionID);

/**
 * Starts playing given background music.
 * @param musicID Music to be played in background.
 */
void setBackgroundMusic(int musicID);

/**
 * Pauses background music.
 */
void stopBackgroundMusic();

}  // namespace Sound

}  // namespace FMAW

#endif