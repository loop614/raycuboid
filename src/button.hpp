#pragma once

#include <string>
#include <raylib.h>

class Button
{
public:
    Button(float x, float y, const char* text);
    ~Button();
    Font font;
    float x;
    float y;
    float w;
    float h;
    float x1;
    float y1;
    const char* text;
    void Draw();
};
