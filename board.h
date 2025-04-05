#ifndef PROJECT_BOARD_H
#define PROJECT_BOARD_H

#include <SFML/Graphics.hpp>
using namespace sf;

#define GRID_SIZE 5
#define CELL_SIZE 64
#define BOARD_TOP_OFFSET  128
#define BOARD_LEFT_OFFSET 220

enum LineType {DIAG=0, ROW=1, COL=2};

class Board{
private:
    int grid[GRID_SIZE][GRID_SIZE] = {0};
    static int get_points(int symbol_cnt);
    int total_score = 0;

public:
    static std::string get_symbol(int i);
    void draw_rect(RenderWindow* window, float width, float height, int x, int y, int line_width, Color fill, Color line,
                   Font* font, int txt_size=16, std::string string_text="");
    bool is_first_valid_pos(int x, int y);
    bool is_second_valid_pos(int x, int y, int last_x, int last_y);
    bool is_finished();
    void place(int symbol, int x, int y);
    int count_points(LineType line_type, int i);
    void draw(RenderWindow* window, Font* font);
    void draw_with_points(RenderWindow* window, Font* font);
    int get_total_score();

};

#endif //PROJECT_BOARD_H
