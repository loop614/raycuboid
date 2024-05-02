#pragma once

#include "angle.hpp"
#include <raymath.h>

enum axis
{
    axisx,
    axisy,
    axisz,
};

Vector3 tiltVec3ByDeg(Vector3 vec, Angle angle, axis ax = axisz);
