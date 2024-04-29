#pragma once

#include <raylib.h>
#include <vector>
#include <array>
#include "triangle.hpp"

class Quad
{
public:
    Quad() {};
    Quad(Vector3 a, Vector3 b, Vector3 c, Vector3 d, bool calculate = false);
    ~Quad();
    Vector3 a;
    Vector3 b;
    Vector3 c;
    Vector3 d;
    void Draw();
    bool IsReady;
    bool is_tilted;
    bool is_square;
    bool is_rect;
    float sideab;
    float sidebc;
    float sidecd;
    float sideda;
    float diaginal_len;
    std::vector<Vector3> GetPoints();

private:
    Vector3 center;
    Triangle* tri_abd;
    Triangle* tri_bcd;
    Color color;
    void CalculateCenter(Vector3 p1, Vector3 p2);
    void CalculateIsRectIsSquare();
    void CalculateSides();
    void CalculateIsTilted();
};
