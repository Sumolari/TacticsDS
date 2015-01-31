#include <nds.h>
#include <nds/debug.h>

#include "./sprite.h"

namespace FMAW {

void clearAllSprites(void) {
    for ( sprite_id id = 0; id < TOTAL_SPRITES; id++ )
        disableSprite( id );
}

void disableSprite( sprite_id id ) {
    sprites[id].attr0 = ATTR0_DISABLED;
}

}