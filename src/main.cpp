#include <raylib.h>
#include <array>
#include <iostream>
#include <string>
#include "cuboid.hpp"
#include "button.hpp"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int screenDepth = 600;

    // TODO: make examples of more cuboids
    // TODO: [1]    9534 segmentation fault  ./raycuboid
    std::array<std::array<Vector3, 8>, 2> cuboidExamples = {{
        {
            Vector3{1, 1, 1}, Vector3{3, 1, 1}, Vector3{3, 3, 1}, Vector3{1, 3, 1},
            Vector3{1, 1, 0}, Vector3{3, 1, 0}, Vector3{3, 3, 0}, Vector3{1, 3, 0}
        },
        {
            Vector3{1, 1, 2}, Vector3{3, 1, 2}, Vector3{3, 3, 2}, Vector3{1, 3, 2},
            Vector3{1, 1, 0}, Vector3{3, 1, 0}, Vector3{3, 3, 0}, Vector3{1, 3, 0}
        },
    }};

    InitWindow(screenWidth, screenHeight, "RAYLIB!");
    SetTargetFPS(60);
    Camera3D camera3D = {{0, 10, 10}, {0, 0, 0}, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
    char buffer[30];
    size_t index = 0;
    Cuboid* cb = new Cuboid(
        cuboidExamples[index][0],
        cuboidExamples[index][1],
        cuboidExamples[index][2],
        cuboidExamples[index][3],
        cuboidExamples[index][4],
        cuboidExamples[index][5],
        cuboidExamples[index][6],
        cuboidExamples[index][7]
    );
    Vector3 point = Vector3 {2, 2, 0.5};
    bool isPointInside = false;
    Color pointColor = GREEN;
    Button nextButton = Button(20, 60, "NEXT");
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
                }
                cb = new Cuboid(
                    cuboidExamples[index][0],
                    cuboidExamples[index][1],
                    cuboidExamples[index][2],
                    cuboidExamples[index][3],
                    cuboidExamples[index][4],
                    cuboidExamples[index][5],
                    cuboidExamples[index][6],
                    cuboidExamples[index][7]
                );
            }
        }

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
        if (IsKeyPressed(KEY_ESCAPE))
        {
            EndDrawing();
            EndMode3D();
            break;
        }

        cb->Draw();
        DrawGrid(10, 1.0f);
        isPointInside = cb->is_point_inside(point);
        pointColor = GREEN;
        if (isPointInside) {
            pointColor = BLACK;
        }
        DrawSphere(point, 0.1, pointColor);
        EndMode3D();

        std::sprintf(buffer, "Camera at %.1f, %.1f, %.1f", camera3D.position.x, camera3D.position.y, camera3D.position.z);
        DrawText(buffer, 10, 40, 10, DARKGRAY);
        nextButton.Draw();
        DrawFPS(10, 10);
        EndDrawing();
    }

    delete cb;
    CloseWindow();
    return 0;
}
