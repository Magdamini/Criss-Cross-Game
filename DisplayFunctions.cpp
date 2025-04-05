#include "DisplayFunctions.h"

void choose_starting_symbol(Board* board, RenderWindow* window, Font* font, bool mouse_click){
    Text text("Choose starting symbol: ", *font, CELL_SIZE / 2);
    text.setFillColor(Color::Black);
    text.setPosition(TEXT_LEFT_OFFSET, TEXT_TOP_OFFSET);
    window->draw(text);
    int left_offset = TEXT_LEFT_OFFSET + text.getGlobalBounds().width;

    Vector2i pos = Mouse::getPosition(*window);

    for(int i = 1; i <= 6; i++){
        RectangleShape rect;
        Color fill_color = Color::Black;
        float left = left_offset + (i - 1) * CELL_SIZE * 0.75;
        rect.setSize(Vector2f(CELL_SIZE * 0.75, CELL_SIZE));
        rect.setPosition(Vector2f(left, TEXT_TOP_OFFSET));

        if(rect.getGlobalBounds().contains(Vector2f(pos))) fill_color = Color(95, 140, 94);

        Text text(Board::get_symbol(i), *font, CELL_SIZE / 2);
        text.setFillColor(fill_color);

        text.setPosition(left + CELL_SIZE * 0.75 / 2.0 - text.getGlobalBounds().width / 2.0, TEXT_TOP_OFFSET);
        window->draw(text);

        if(mouse_click && rect.getGlobalBounds().contains(Vector2f(pos))){
            board->place(i, 0, 0);
        }
    }
}


void show_text_score(int score, RenderWindow* window, Font* font){
    Text text("You've scored " + std::to_string(score) + " points!", *font, CELL_SIZE / 2);
    text.setFillColor(Color::Black);
    text.setPosition(3 * TEXT_LEFT_OFFSET, TEXT_TOP_OFFSET);
    window->draw(text);
}



int show_and_place_round_symbols(int symbol_no, int round_symbols[], RenderWindow* window, Font* font, bool mouse_click,
                                 Board* board, int* last_x, int* last_y){
    std::string str_txt;
    if(symbol_no == 0) str_txt = "Place  1st symbol: ";
    else str_txt = "Place 2nd symbol: ";

    Text text(str_txt, *font, CELL_SIZE / 2);
    text.setFillColor(Color::Black);
    text.setPosition(3 * TEXT_LEFT_OFFSET, TEXT_TOP_OFFSET);
    window->draw(text);
    int left_offset = 3 * TEXT_LEFT_OFFSET + text.getGlobalBounds().width;

    for(int i = 0; i < 2; i++) {
        RectangleShape rect;
        float left = left_offset + i * CELL_SIZE * 0.75;
        rect.setSize(Vector2f(CELL_SIZE * 0.75, CELL_SIZE));
        rect.setPosition(Vector2f(left, TEXT_TOP_OFFSET));

        Color fill_color = Color::Black;

        if(i == symbol_no) fill_color = Color(95, 140, 94);

        Text text(Board::get_symbol(round_symbols[i]), *font, CELL_SIZE / 2);
        text.setFillColor(fill_color);

        text.setPosition(left + CELL_SIZE * 0.75 / 2.0 - text.getGlobalBounds().width / 2.0, TEXT_TOP_OFFSET);
        window->draw(text);
    }

    Vector2i pos = Mouse::getPosition(*window);

    for(int row = 0; row < GRID_SIZE; row++){
        for(int col = 0; col < GRID_SIZE; col++){

            RectangleShape rect;
            rect.setSize(Vector2f(CELL_SIZE, CELL_SIZE));
            rect.setPosition(BOARD_LEFT_OFFSET + col * CELL_SIZE, BOARD_TOP_OFFSET + row * CELL_SIZE);

            if(mouse_click && rect.getGlobalBounds().contains(Vector2f(pos))){
                if(symbol_no == 0 && board->is_first_valid_pos(row, col)) {
                    board->place(round_symbols[symbol_no], row, col);
                    *last_x = row;
                    *last_y = col;
                    return (symbol_no + 1) % 2;
                } else if(symbol_no == 1 && board->is_second_valid_pos(row, col, *last_x, *last_y)){
                    board->place(round_symbols[symbol_no], row, col);
                    return (symbol_no + 1) % 2;
                }

            }
        }
    }
    return symbol_no;
}

void show_rules(RenderWindow* window, Font* font){
    int left_offset = 40, top_offset = 10, header_size = 48, text_size = 24;
    std::string rules = "At the start of the game choose one of the six shapes. It\n"
                        "will be placed in the top leftcorner of the 5x5 board. Every\n"
                        "round you will get two random symbols. The symbols must be \n"
                        "entered into two empty spaces that are horizontally or \n"
                        "vertically next to each other. The game ends when the board \n"
                        "is filled or there are no legal adjacent spaces left\n";

    std::string points = "You score points for the same adjacent symbols in each \n"
                         "column, row and on the marked diagonal.\n"
                         "Points are awarded according to the following rule:\n"
                         " Two adjacent symbols - 2 points\n"
                         " Three adjacent symbols - 3 points\n"
                         " Four adjacent symbols - 8 points\n"
                         " Five adjacent symbols - 10 points\n"
                         "Remember, the diagonal counts twice!\n";

    std::string header = "Rules";
    std::string points_header = "Points";

    // header
    Text text(header, *font, header_size);
    text.setFillColor(Color::Black);
    text.setPosition(left_offset, top_offset);
    window->draw(text);
    top_offset += text.getGlobalBounds().height + 20;

    text = Text(rules, *font, text_size);
    text.setFillColor(Color::Black);
    text.setPosition(left_offset, top_offset);
    window->draw(text);
    top_offset += text.getGlobalBounds().height;


    text = Text(points_header, *font, header_size);
    text.setFillColor(Color::Black);
    text.setPosition(left_offset, top_offset);
    window->draw(text);
    top_offset += text.getGlobalBounds().height + 20;

    text = Text(points, *font, text_size);
    text.setFillColor(Color::Black);
    text.setPosition(left_offset, top_offset);
    window->draw(text);
}

