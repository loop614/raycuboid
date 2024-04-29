#include "angle.hpp"
#include <stdlib.h>

Angle::Angle(float val) : val{val}
{
}

bool Angle::is45()
{
    return abs(45 - this->val) < ERROR_TOLERANCE;
}

bool Angle::is90()
{
    return abs(90 - this->val) < ERROR_TOLERANCE;
}
