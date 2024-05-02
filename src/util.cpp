#include "util.hpp"
#include <math.h>

Vector3 tiltVec3ByDeg(Vector3 vec, Angle angle) {
    float pi180 = PI / 180;

    Vector3 mat1 = {
        cos(angle.val * pi180),
        -sin(angle.val * pi180),
        0
    };

    Vector3 mat2 = {
        sin(angle.val * pi180),
        cos(angle.val * pi180),
        0
    };

    Vector3 mat3 = {
        0,
        0,
        1
    };

    return Vector3 {
        mat1.x * vec.x + mat1.y * vec.y + mat1.z * vec.z,
        mat2.x * vec.x + mat2.y * vec.y + mat2.z * vec.z,
        mat3.x * vec.x + mat3.y * vec.y + mat3.z * vec.z,
    };
}
