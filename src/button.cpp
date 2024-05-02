#include "button.hpp"
#include "css.hpp"
#include <cstring>

Button::Button(float x, float y, const char *text) : x{x}, y{y}, text{text}
{
    this->h = BUTTON_HEIGHT;
    this->w = strlen(text) * BUTTON_WIDTH_PER_LETTER;
    this->y1 = y + BUTTON_HEIGHT;
    this->x1 = x + this->w;
    this->font = LoadFontEx("font/monogram.ttf", 32, 0, 250);
}

Button::~Button()
{
}

void Button::Draw()
{
    DrawRectangle(this->x, this->y, this->w, this->h, BLACK);
    DrawTextEx(this->font, this->text, {this->x, this->y}, FONT_SIZE, FONT_SPACING, GREEN);
}
