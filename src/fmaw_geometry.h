#ifndef FMAW_GEOMETRY_H
#define FMAW_GEOMETRY_H

#include "./fmaw_types.h"

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
    void selectRegister();

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
    }

    /**
     * Returns transform with given identifier.
     */
    Transform(uint8 id) : id(id) {
        this->selectRegister();
    }

    /**
     * Returns an AND-friendly bitmask to set the index of this Transform.
     * @return AND-friendly bitmask to set the index of this Transform.
     */
    uint16 IDbitMask();

    /**
     * Resets this transform to 0.
     */
    void clear();

    /**
     * Sets this transform to identify transform.
     */
    void setIdentity();

    /**
     * Applies a rotation of given angle, CCW.
     * @param angle Angle to rotate.
     */
    void applyRotation(double angle);

    /**
     * Applies given scaling.
     * @param x Horizontal scaling.
     * @param y Vertical scaling.
     */
    void applyScaling(FixedReal x, FixedReal y);

    /**
     * Displays information about this transform.
     */
    void print();

};

}

#endif