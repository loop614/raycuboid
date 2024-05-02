#include "util.hpp"
#include <math.h>
#include <map>
#include <array>

Vector3 tiltVec3ByDeg(Vector3 vec, Angle angle, axis ax)
{
    float pi180 = PI / 180;

    std::map<axis, std::array<Vector3, 3>> mapAxis;
    mapAxis[axisx] = {{{1, 0, 0},
                   {0, cos(angle.val * pi180), -sin(angle.val * pi180)},
                   {0, sin(angle.val * pi180), cos(angle.val * pi180)}}};

    mapAxis[axisy] = {{{cos(angle.val * pi180), 0, sin(angle.val * pi180)},
                   {0, 1, 0},
                   {-sin(angle.val * pi180), 0, cos(angle.val * pi180)}}};

    mapAxis[axisz] = {{{cos(angle.val * pi180), -sin(angle.val * pi180), 0},
                   {sin(angle.val * pi180), cos(angle.val * pi180), 0},
                   {0, 0, 1}}};

    Vector3 mat1 = mapAxis[ax][0];
    Vector3 mat2 = mapAxis[ax][1];
    Vector3 mat3 = mapAxis[ax][2];

    return Vector3{
        mat1.x * vec.x + mat1.y * vec.y + mat1.z * vec.z,
        mat2.x * vec.x + mat2.y * vec.y + mat2.z * vec.z,
        mat3.x * vec.x + mat3.y * vec.y + mat3.z * vec.z,
    };
}
