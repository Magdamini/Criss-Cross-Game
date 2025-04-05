#ifndef PROJECT_BUTTON_H
#define PROJECT_BUTTON_H

#include <SFML/Graphics.hpp>
using namespace sf;

#define BUTTON_OFFSET 10

class Button{
private:
    Color color;
    Color mouse_color;
    RectangleShape rect;
    Text button_text;

public:
    Button(const Color &color, const Color &mouseColor, int x_center, int y_top, Font* font, std::string text, int size);
    void draw(RenderWindow* window, Vector2f mouse_pos);
    bool is_clicked(Vector2f mouse_pos, bool mouse_click);

};

#endif //PROJECT_BUTTON_H
