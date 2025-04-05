#include <SFML/Graphics.hpp>
#include "Button.h"
#include <iostream>
using namespace sf;


Button::Button(const Color &color, const Color &mouseColor, int x_center, int y_top, Font* font, std::string text, int size) : color(color), mouse_color(mouseColor){
    button_text = Text(text, *font, size);
    button_text.setFillColor(Color::Black);

    auto text_bounds = button_text.getGlobalBounds();
    float x = x_center - text_bounds.width / 2;
    button_text.setPosition(x, y_top);
    text_bounds = button_text.getGlobalBounds();

//    if (size == 128) y_top += 15;
    y_top += 4 * size / 32;



    rect.setSize(Vector2f(text_bounds.width + 2 * BUTTON_OFFSET, text_bounds.height + 2 * BUTTON_OFFSET));
    rect.setPosition(x - BUTTON_OFFSET, y_top - BUTTON_OFFSET);
    rect.setOutlineThickness(4);
    rect.setOutlineColor(Color::Black);
}



void Button::draw(RenderWindow *window, Vector2f mouse_pos) {
    Color curr_color = color;
    if(rect.getGlobalBounds().contains(Vector2f(mouse_pos))) curr_color = mouse_color;

    rect.setFillColor(curr_color);

    window->draw(rect);
    window->draw(button_text);
}

bool Button::is_clicked(Vector2f mouse_pos, bool mouse_click) {
    return mouse_click && rect.getGlobalBounds().contains(Vector2f(mouse_pos));
}
