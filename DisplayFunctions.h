#ifndef PROJECT_DISPLAYFUNCTIONS_H
#define PROJECT_DISPLAYFUNCTIONS_H

#include <SFML/Graphics.hpp>
#include "board.h"
#include <random>

#define TEXT_LEFT_OFFSET 64
#define TEXT_TOP_OFFSET 550

using namespace sf;

void choose_starting_symbol(Board* board, RenderWindow* window, Font* font, bool mouse_click);
void show_text_score(int score, RenderWindow* window, Font* font);
int show_and_place_round_symbols(int symbol_no, int round_symbols[], RenderWindow* window, Font* font, bool mouse_click,
                                 Board* board, int* last_x, int* last_y);
void show_rules(RenderWindow* window, Font* font);

#endif //PROJECT_DISPLAYFUNCTIONS_H
