#pragma once
#include <raylib.h>
#include "angle.hpp"

class Triangle {
    public:
        Triangle();
        void Init(Vector3 a, Vector3 b, Vector3 c);
        Vector3 a;
        Vector3 b;
        Vector3 c;
        Angle alpha;
        Angle beta;
        Angle gamma;
        float sidea;
        float sideb;
        float sidec;
        bool IsVecIn(Vector3 p);

    private:
        void CalculateSides();
        void CalculateAngles();
};
