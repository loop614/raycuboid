#include "util.hpp"
#include <math.h>
#include <map>
#include <array>
#include <cassert>

Vector3 tiltVec3ByDeg(Vector3 vec, Angle angle, axis ax)
{
    float pi180 = PI / 180;
    std::array<Vector3, 3> rotMat = {};

    switch (ax)
    {
    case axisx:
        rotMat = {{{1, 0, 0},
                   {0, cos(angle.val * pi180), -sin(angle.val * pi180)},
                   {0, sin(angle.val * pi180), cos(angle.val * pi180)}}};
        break;
    case axisy:
        rotMat = {{{cos(angle.val * pi180), 0, sin(angle.val * pi180)},
                   {0, 1, 0},
                   {-sin(angle.val * pi180), 0, cos(angle.val * pi180)}}};
        break;
    case axisz:
        rotMat = {{{cos(angle.val * pi180), -sin(angle.val * pi180), 0},
                   {sin(angle.val * pi180), cos(angle.val * pi180), 0},
                   {0, 0, 1}}};
        break;
    default:
        assert(false && "unreachable");
        break;
    }

    return Vector3{
        rotMat[0].x * vec.x + rotMat[0].y * vec.y + rotMat[0].z * vec.z,
        rotMat[1].x * vec.x + rotMat[1].y * vec.y + rotMat[1].z * vec.z,
        rotMat[2].x * vec.x + rotMat[2].y * vec.y + rotMat[2].z * vec.z,
    };
}
