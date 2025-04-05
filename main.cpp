#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "board.h"
#include <iostream>
#include "ClickDetector.h"
#include <ctime>
#include <random>
#include "Button.h"
#include "DisplayFunctions.h"

#define TEXT_LEFT_OFFSET 64
#define TEXT_TOP_OFFSET 550


using namespace sf;

enum GameStates {MENU, HELP, START, PLAY, SHOW_POINTS};

int main() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    srand(time(NULL));


    RenderWindow window(VideoMode(800, 640), "CrissCross", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int pos_x = (desktop.width - window.getSize().x) / 2;
    int pos_y = (desktop.height - window.getSize().y) / 2;
    window.setPosition(sf::Vector2i(pos_x, pos_y));

    Font my_font;
    my_font.loadFromFile(std::string(cwd) + "/my_font.ttf");

    Board game_board;
    GameStates game_state = MENU;
    ClickDetector click_detector = ClickDetector();
    bool mouse_click;
    Vector2i mouse_pos;
    int new_symbol_no, symbol_no = 0;
    int round_symbols[2], last_x, last_y;

    //buttons

    Button start_button(Color(101, 161, 224), Color(56, 83, 112), 400, 180, &my_font, "New game", 128);
    Button how_to_play_button(Color(101, 161, 224), Color(56, 83, 112), 400, 400, &my_font, "How to play", 64);
    Button back_button(Color(242, 87, 87), Color(138, 58, 58), 400, 530, &my_font, "Back", 48);
    Button finish_button(Color(141, 209, 140), Color(95, 140, 94), 710, 545, &my_font, "Finish", 48);


    while(window.isOpen())
    {
        Event e;
        while (window.pollEvent(e)){
            if(e.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);
        mouse_click = click_detector.is_clicked();
        mouse_pos = Mouse::getPosition(window);

        switch (game_state) {
            case MENU:{
                start_button.draw(&window, Vector2f(mouse_pos));
                how_to_play_button.draw(&window, Vector2f(mouse_pos));
                if(start_button.is_clicked(Vector2f(mouse_pos), mouse_click)){
                    game_state = START;
                    game_board = Board();
                }
                if(how_to_play_button.is_clicked(Vector2f(mouse_pos), mouse_click)){
                    game_state = HELP;
                }
                break;
            }
            case HELP:{
                show_rules(&window, &my_font);
                back_button.draw(&window, Vector2f(mouse_pos));
                if(back_button.is_clicked(Vector2f(mouse_pos), mouse_click)){
                    game_state = MENU;
                }
                break;
            }

            case START: {
                choose_starting_symbol(&game_board, &window, &my_font, mouse_click);
                game_board.draw(&window, &my_font);
                if(!game_board.is_first_valid_pos(0, 0)) {
                    game_state = PLAY;
                    round_symbols[0] = rand() % 6 + 1;
                    round_symbols[1] = rand() % 6 + 1;
                    symbol_no = 0;
                }
            }
                break;
            case PLAY:{
                game_board.draw(&window, &my_font);

                new_symbol_no = show_and_place_round_symbols(symbol_no, round_symbols, &window, &my_font, mouse_click,
                                                             &game_board, &last_x, &last_y);
                if(symbol_no == 1 && new_symbol_no == 0){
                    // case when 2nd symbol is placed
                    round_symbols[0] = rand() % 6 + 1;
                    round_symbols[1] = rand() % 6 + 1;
                }
                symbol_no = new_symbol_no;


                if(symbol_no == 0 && game_board.is_finished()) game_state = SHOW_POINTS;
                break;
            }
            case SHOW_POINTS:{
                game_board.draw_with_points(&window, &my_font);
                show_text_score(game_board.get_total_score(), &window, &my_font);

                finish_button.draw(&window, Vector2f(mouse_pos));
                if(finish_button.is_clicked(Vector2f(mouse_pos), mouse_click)){
                    game_state = MENU;
                }
                break;
            }

        }

        window.display();
    }


    return 0;
}

