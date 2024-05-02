#include <raylib.h>
#include <array>
#include <iostream>
#include <string>
#include "cuboid.hpp"
#include "button.hpp"
#include "util.hpp"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int screenDepth = 600;

    // TODO: make examples of more cuboids
    std::array<Cuboid, 3> cuboidExamples = {
        Cuboid {
            Vector3{1, 1, 1}, Vector3{3, 1, 1}, Vector3{3, 3, 1}, Vector3{1, 3, 1},
            Vector3{1, 1, 0}, Vector3{3, 1, 0}, Vector3{3, 3, 0}, Vector3{1, 3, 0}
        },
        Cuboid {
            Vector3{1, 1, 2}, Vector3{3, 1, 2}, Vector3{3, 3, 2}, Vector3{1, 3, 2},
            Vector3{1, 1, 0}, Vector3{3, 1, 0}, Vector3{3, 3, 0}, Vector3{1, 3, 0}
        },
        Cuboid {
            tiltVec3ByDeg(Vector3{1, 1, 2}, 20), tiltVec3ByDeg(Vector3{3, 1, 2}, 20), tiltVec3ByDeg(Vector3{3, 3, 2}, 20), tiltVec3ByDeg(Vector3{1, 3, 2}, 20),
            tiltVec3ByDeg(Vector3{1, 1, 0}, 20), tiltVec3ByDeg(Vector3{3, 1, 0}, 20), tiltVec3ByDeg(Vector3{3, 3, 0}, 20), tiltVec3ByDeg(Vector3{1, 3, 0}, 20)
        }
    };

    InitWindow(screenWidth, screenHeight, "RAYLIB!");
    SetTargetFPS(30);
    Camera3D camera3D = {{2, 2, 10}, {2, 2, 0}, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
    char bufferCamera[30];
    char bufferTarget[30];
    size_t index = 0;
    Vector3 point = Vector3 {2, 2, 0.5};
    bool isPointInside = false;
    Color pointColor = GREEN;
    Button nextButton = Button(20, 70, "NEXT");
    Vector2 mouseLeft = {-10.0f,-10.0f};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera3D);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mouseLeft = GetMousePosition();
            if (mouseLeft.x < nextButton.x1 && mouseLeft.x > nextButton.x && mouseLeft.y < nextButton.y1 && mouseLeft.y > nextButton.y) {
                index++;
                if (index == cuboidExamples.size()) {
                    index = 0;
                };
            }
        }

        if (IsKeyPressed(KEY_UP)) {
            camera3D.position = tiltVec3ByDeg(camera3D.position, 10, axisx);
        }

        if (IsKeyPressed(KEY_DOWN)) {
            camera3D.position = tiltVec3ByDeg(camera3D.position, -10, axisx);
        }

        if (IsKeyPressed(KEY_LEFT)) {
            camera3D.position = tiltVec3ByDeg(camera3D.position, 10, axisy);
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            camera3D.position = tiltVec3ByDeg(camera3D.position, -10, axisy);
        }

        if (IsKeyPressed(KEY_A) && camera3D.position.x > -screenWidth)
        {
            camera3D.position.x -= 2;
            camera3D.target.x -= 2;
        }
        if (IsKeyPressed(KEY_S) && camera3D.position.y > -screenHeight)
        {
            camera3D.position.y -= 2;
            camera3D.target.y -= 2;
        }
        if (IsKeyPressed(KEY_D) && camera3D.position.x < screenWidth)
        {
            camera3D.position.x += 2;
            camera3D.target.x += 2;
        }
        if (IsKeyPressed(KEY_W) && camera3D.position.y < screenHeight)
        {
            camera3D.position.y += 2;
            camera3D.target.y += 2;
        }
        if (IsKeyPressed(KEY_Q) && camera3D.position.z < screenDepth)
        {
            camera3D.position.z += 2;
            camera3D.target.z += 12;
        }
        if (IsKeyPressed(KEY_E) && camera3D.position.z > -screenDepth)
        {
            camera3D.position.z -= 2;
            camera3D.target.z -= 12;
        }

        if (IsKeyPressed(KEY_J) && point.x > 0)
        {
            point.x -= 0.5;
        }
        if (IsKeyPressed(KEY_K) && point.y > 0)
        {
            point.y -= 0.5;
        }
        if (IsKeyPressed(KEY_L) && point.x < screenWidth)
        {
            point.x += 0.5;
        }
        if (IsKeyPressed(KEY_I) && point.y < screenWidth)
        {
            point.y += 0.5;
        }
        if (IsKeyPressed(KEY_U) && point.z < screenDepth)
        {
            point.z += 0.5;
        }
        if (IsKeyPressed(KEY_O) && point.z > 0)
        {
            point.z -= 0.5;
        }

        cuboidExamples[index].Draw();
        DrawGrid(10, 1.0f);
        isPointInside = cuboidExamples[index].is_point_inside(point);
        pointColor = GREEN;
        if (isPointInside) {
            pointColor = BLACK;
        }
        DrawSphere(point, 0.1, pointColor);
        EndMode3D();

        std::sprintf(bufferCamera, "Camera at %.1f, %.1f, %.1f", camera3D.position.x, camera3D.position.y, camera3D.position.z);
        std::sprintf(bufferTarget, "Target at %.1f, %.1f, %.1f", camera3D.target.x, camera3D.target.y, camera3D.target.z);
        DrawText(bufferCamera, 10, 40, 10, DARKGRAY);
        DrawText(bufferTarget, 10, 55, 10, DARKGRAY);
        nextButton.Draw();
        DrawFPS(20, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
