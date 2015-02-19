#ifndef FMAW_GEOMETRY_H
#define FMAW_GEOMETRY_H

#include "./fmaw_types.h"

#include <nds.h>

#include "./fmaw_debug.h"

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
        this->PB = OAM + this->id * 16 + 7;
        this->PC = OAM + this->id * 16 + 11;
        this->PD = OAM + this->id * 16 + 15;
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

    void clear() {
        *this->PA = 0;
        *this->PB = 0;
        *this->PC = 0;
        *this->PD = 0;
    }

    /**
     * Sets this transform to identify transform.
     */
    void setIdentity() {
        *this->PA = 1 << 8;
        *this->PB = 0;
        *this->PC = 0;
        *this->PD = 1 << 8;
    }

    void applyRotation(double angle) {

    }

    void applyScaling(FixedReal x, FixedReal y) {
        *this->PA = (FixedReal(*(this->PA), 8) * x).raw();
        *this->PB = (FixedReal(*(this->PB), 8) * y).raw();
        *this->PC = (FixedReal(*(this->PC), 8) * x).raw();
        *this->PD = (FixedReal(*(this->PD), 8) * y).raw();
    }

    void print() {
        printf("%s\r\n  Transform %u:%s\r\n%f %f\r\n%f %f\r\n%s",
               "\r\n|----------------|", this->id, "\r\n|----------------|",
               *this->PA,
               *this->PB,
               *this->PC,
               *this->PD,
               "|----------------|"
              );
    }

};

}

#endif