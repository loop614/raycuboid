#include "triangle.hpp"
#include <raymath.h>
#include <math.h>
#include <iostream>

Triangle::Triangle()
{
}

void Triangle::Init(Vector3 a, Vector3 b, Vector3 c)
{
    this->a = {a.x, a.y, a.z};
    this->b = {b.x, b.y, b.z};
    this->c = {c.x, c.y, c.z};
    this->CalculateSides();
    this->CalculateAngles();
}

void Triangle::CalculateSides()
{
    this->sidea = Vector3Distance(this->b, this->c);
    this->sideb = Vector3Distance(this->a, this->c);
    this->sidec = Vector3Distance(this->a, this->b);
}

void Triangle::CalculateAngles()
{
    this->alpha.val = (180.0 / PI) * acos(
        (this->sideb * this->sideb + this->sidec * this->sidec - this->sidea * this->sidea) / (2 * this->sideb * this->sidec));
    this->gamma.val = (180.0 / PI) * acos(
        (this->sidea * this->sidea + this->sideb * this->sideb - this->sidec * this->sidec) / (2 * this->sidea * this->sideb));
    this->beta.val = 180.0 - this->alpha.val - this->gamma.val;
}
