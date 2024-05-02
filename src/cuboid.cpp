#include "cuboid.hpp"
#include <raymath.h>
#include <iostream>

Cuboid::Cuboid(
    Vector3 a, Vector3 b, Vector3 c, Vector3 d,
    Vector3 e, Vector3 f, Vector3 g, Vector3 h)
{
    this->quadhorz1 = new Quad(a, b, c, d, true);
    this->quadhorz2 = new Quad(e, f, g, h, true);
    this->quadsouth = new Quad(this->quadhorz1->a, this->quadhorz2->a, this->quadhorz2->b, this->quadhorz1->b);
    this->quadwest = new Quad(this->quadhorz1->a, this->quadhorz2->a, this->quadhorz2->d, this->quadhorz1->d);
    this->quadnorth = new Quad(this->quadhorz1->c, this->quadhorz2->c, this->quadhorz2->d, this->quadhorz1->d);
    this->quadeast = new Quad(this->quadhorz1->b, this->quadhorz2->b, this->quadhorz2->c, this->quadhorz1->c);

    this->is_rectangular_prism = this->quadhorz1->is_rect && this->quadhorz2->is_rect;
    this->calculate_height();
    this->calculate_is_cube();
}

Cuboid::~Cuboid()
{
    delete this->quadhorz1;
    delete this->quadhorz2;
    delete this->quadsouth;
    delete this->quadwest;
    delete this->quadnorth;
    delete this->quadeast;
}

void Cuboid::Draw()
{
    this->quadhorz1->Draw();
    this->quadhorz2->Draw();
    this->quadeast->Draw();
    this->quadwest->Draw();
    this->quadsouth->Draw();
    this->quadnorth->Draw();
}

void Cuboid::calculate_height()
{
    this->heightae = Vector3Distance(this->quadhorz1->a, this->quadhorz2->a);
    this->heightbf = Vector3Distance(this->quadhorz1->b, this->quadhorz2->b);
    this->heightcg = Vector3Distance(this->quadhorz1->c, this->quadhorz2->c);
    this->heightdh = Vector3Distance(this->quadhorz1->d, this->quadhorz2->d);
}

void Cuboid::calculate_is_cube()
{
    this->is_cube = false;
    if (!this->is_rectangular_prism)
    {
        return;
    }
    float pivotDistance = this->quadhorz1->sideab;
    std::vector<float> distances = {
        this->quadhorz1->sidebc,
        this->quadhorz1->sidecd,
        this->quadhorz1->sideda,
        this->quadhorz2->sideab,
        this->quadhorz2->sidebc,
        this->quadhorz2->sidecd,
        this->quadhorz2->sideda,
        this->heightae,
        this->heightbf,
        this->heightcg,
        this->heightdh};

    for (float i : distances)
    {
        if (i != pivotDistance)
        {
            return;
        }
    }

    this->is_cube = true;
}

bool Cuboid::is_point_inside(Vector3 point)
{
    if (!this->is_rectangular_prism)
    {
        std::cout << "Not implemented";
        return false;
    }

    Vector3 p1 = this->quadhorz1->a;
    Vector3 p5 = this->quadhorz2->a;

    Vector3 p2 = this->quadhorz1->d;
    Vector3 p4 = this->quadhorz1->b;

    Vector3 i = Vector3Subtract(p1, p2);
    Vector3 j = Vector3Subtract(p1, p4);
    Vector3 k = Vector3Subtract(p1, p5);
    Vector3 v = Vector3Subtract(p1, point);

    float vi = Vector3DotProduct(v, i);
    float vj = Vector3DotProduct(v, j);
    float vk = Vector3DotProduct(v, k);

    return (
        0 < vi and vi < Vector3DotProduct(i, i) and
        0 < vj and vj < Vector3DotProduct(j, j) and
        0 < vk and vk < Vector3DotProduct(k, k));
}
