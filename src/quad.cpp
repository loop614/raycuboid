#include "quad.hpp"
#include <raymath.h>
#include <iostream>

Quad::Quad(Vector3 a, Vector3 b, Vector3 c, Vector3 d, bool calculate)
{
    this->a = {a.x, a.y, a.z};
    this->b = {b.x, b.y, b.z};
    this->c = {c.x, c.y, c.z};
    this->d = {d.x, d.y, d.z};
    this->tri_abd = new Triangle();
    this->tri_bcd = new Triangle();

    if (calculate)
    {
        this->tri_abd->Init(this->a, this->b, this->d);
        this->tri_bcd->Init(this->b, this->c, this->d);
        this->CalculateIsRectIsSquare();
        this->CalculateSides();
        this->CalculateIsTilted();
    }
}

Quad::~Quad()
{
    delete this->tri_abd;
    delete this->tri_bcd;
}

void Quad::CalculateIsRectIsSquare()
{
    this->is_rect = false;
    if (this->tri_abd->alpha.is90())
    {
        this->diaginal_len = this->tri_abd->sidea;
        this->is_rect = true;
        this->is_square = this->tri_abd->beta.is45() and this->tri_abd->gamma.is45();
    }
    else if (this->tri_abd->beta.is90())
    {
        this->diaginal_len = this->tri_abd->sideb;
        this->is_rect = true;
        this->is_square = this->tri_abd->alpha.is45() and this->tri_abd->gamma.is45();
    }
    else if (this->tri_abd->gamma.is90())
    {
        this->diaginal_len = this->tri_abd->sidec;
        this->is_rect = true;
        this->is_square = this->tri_abd->alpha.is45() and this->tri_abd->beta.is45();
    }
}

void Quad::CalculateSides()
{
    this->sideab = Vector3Distance(this->a, this->b);
    this->sidebc = Vector3Distance(this->b, this->c);
    this->sidecd = Vector3Distance(this->c, this->d);
    this->sideda = Vector3Distance(this->d, this->a);
}

void Quad::CalculateIsTilted()
{
    this->is_tilted = !(
        Vector3Angle({0, 1, 0}, Vector3Subtract(this->b, this->a)) == 0 ||
        Vector3Angle({0, 1, 0}, Vector3Subtract(this->c, this->b)) == 0 ||
        Vector3Angle({0, 1, 0}, Vector3Subtract(this->d, this->c)) == 0 ||
        Vector3Angle({0, 1, 0}, Vector3Subtract(this->d, this->a)) == 0);
}

void Quad::Draw()
{
    DrawLine3D(this->a, this->b, BLACK);
    DrawLine3D(this->b, this->c, BLACK);
    DrawLine3D(this->c, this->d, BLACK);
    DrawLine3D(this->d, this->a, BLACK);
}

std::vector<Vector3> Quad::GetPoints()
{
    return std::vector<Vector3>{this->a, this->b, this->c, this->d};
}

void Quad::CalculateCenter(Vector3 p1, Vector3 p2)
{
    this->center = Vector3{
        (p1.x + p2.x) / 2,
        (p1.y + p2.y) / 2,
        (p1.z + p2.z) / 2};
}
