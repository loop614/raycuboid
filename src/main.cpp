#include <raylib.h>
#include <array>
#include <iostream>
#include <string>
#include "cuboid.hpp"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int screenDepth = 600;

    // TODO: make examples of more cuboids
    // TODO: double free detected in tcache
    std::array<std::array<Vector3, 8>, 1> cuboidExamples = {{
        {
            Vector3{1, 1, 1}, Vector3{3, 1, 1}, Vector3{3, 3, 1}, Vector3{1, 3, 1},
            Vector3{1, 1, 0}, Vector3{3, 1, 0}, Vector3{3, 3, 0}, Vector3{1, 3, 0}
        },
    }};

    InitWindow(screenWidth, screenHeight, "RAYLIB!");
    SetTargetFPS(60);
    Camera3D camera3D = {{0, 10, 10}, {0, 0, 0}, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
    char buffer[30];
    Cuboid cb = Cuboid(
        cuboidExamples[0][0],
        cuboidExamples[0][1],
        cuboidExamples[0][2],
        cuboidExamples[0][3],
        cuboidExamples[0][4],
        cuboidExamples[0][5],
        cuboidExamples[0][6],
        cuboidExamples[0][7]
    );
    Vector3 point = Vector3 {2, 2, 0.5};
    bool isPointInside = false;
    Color pointColor = GREEN;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera3D);

        if (IsKeyPressed(KEY_A) && camera3D.position.x > 0)
        {
            camera3D.position.x -= 2;
        }
        if (IsKeyPressed(KEY_S) && camera3D.position.y > 0)
        {
            camera3D.position.y -= 2;
        }
        if (IsKeyPressed(KEY_D) && camera3D.position.x < screenWidth)
        {
            camera3D.position.x += 2;
        }
        if (IsKeyPressed(KEY_W) && camera3D.position.y < screenWidth)
        {
            camera3D.position.y += 2;
        }
        if (IsKeyPressed(KEY_Q) && camera3D.position.z < screenDepth)
        {
            camera3D.position.z += 2;
        }
        if (IsKeyPressed(KEY_E) && camera3D.position.z > 0)
        {
            camera3D.position.z -= 2;
        }

        cb.Draw();
        DrawGrid(10, 1.0f);
        isPointInside = cb.is_point_inside(point);
        pointColor = GREEN;
        if (isPointInside) {
            pointColor = BLACK;
        }
        DrawSphere(point, 0.1, pointColor);
        EndMode3D();

        std::sprintf(buffer, "Camera at %.1f, %.1f, %.1f", camera3D.position.x, camera3D.position.y, camera3D.position.z);
        DrawText(buffer, 10, 40, 10, DARKGRAY);
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
