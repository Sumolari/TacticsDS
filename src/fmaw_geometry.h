#ifndef FMAW_GEOMETRY_H
#define FMAW_GEOMETRY_H

#include "./fmaw_types.h"

#include <nds.h>

namespace FMAW {

typedef struct t_point {
    int x;
    int y;
} Point;

class Transform {

private:
    // Address of PA register.
    uint16 *PA;
    // Address of PB register.
    uint16 *PB;
    // Address of PC register.
    uint16 *PC;
    // Address of PD register.
    uint16 *PD;

    /**
     * Sets addresses of internal registers based on current ID of transform.
     */
    void selectRegister() {
        this->PA = OAM + this->id * 16 + 3;
        this->PB = this->PA + 3;
        this->PC = this->PB + 3;
        this->PD = this->PC + 3;
    }

public:
    // ID of this transform.
    uint8 id;
    // Next empty transform.
    static uint8 nextEmptyTransform;
    /**
     * Creates an empty, zero-filled, transform.
     */
    Transform() : id(nextEmptyTransform++) {
        this->selectRegister();
    };

    /**
     * Returns transform with given identifier.
     */
    Transform(uint8 id) : id(id) {
        this->selectRegister();
    };

    /**
     * Returns an AND-friendly bitmask to set the index of this Transform.
     * @return AND-friendly bitmask to set the index of this Transform.
     */
    uint16 IDbitMask() {
        return ((this->id & 0x001F)  << 9) | 0xC1FF;
    }

    /**
     * Sets this transform to identify transform.
     */
    void setIdentity() {
        *this->PA = FixedReal(1).raw() & 0x00FF;
        *this->PB = FixedReal(0).raw() & 0x00FF;
        *this->PC = FixedReal(0).raw() & 0x00FF;
        *this->PD = FixedReal(1).raw() & 0x00FF;
    }

    void applyRotation(double angle) {

    }

    void applyScaling(double x, double y) {
        FixedReal BFRPA = FixedReal::BasicFixedRealFromRaw(*this->PA);
        FixedReal BFRPB = FixedReal::BasicFixedRealFromRaw(*this->PB);
        FixedReal BFRPC = FixedReal::BasicFixedRealFromRaw(*this->PC);
        FixedReal BFRPD = FixedReal::BasicFixedRealFromRaw(*this->PD);

        *this->PA = (BFRPA * x + BFRPB * 0).raw() & 0x00FF;
        *this->PB = (BFRPA * 0 + BFRPB * y).raw() & 0x00FF;
        *this->PC = (BFRPC * x + BFRPD * 0).raw() & 0x00FF;
        *this->PD = (BFRPC * 0 + BFRPD * y).raw() & 0x00FF;
    }

};

}

#endif