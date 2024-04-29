#include "quad.hpp"
#include <raylib.h>

class Cuboid {
    public:
        Quad quadhorz1;
        Quad quadhorz2;
        float heightae;
        float heightbf;
        float heightcg;
        float heightdh;
        bool is_rectangular_prism;
        bool is_cube;
        Cuboid(
            Vector3 a, Vector3 b, Vector3 c, Vector3 d,
            Vector3 e, Vector3 f, Vector3 g, Vector3 h
        );
        void Draw();
        bool is_point_inside(Vector3 point);

    private:
        void calculate_height();
        void calculate_is_cube();
};
