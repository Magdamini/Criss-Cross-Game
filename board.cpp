#include "board.h"
bool Board::is_first_valid_pos(int x, int y) {
    if(grid[x][y] != 0) return false;
    // check free neighbour spots
    if(x - 1 >= 0 && grid[x - 1][y] == 0) return true;
    if(x + 1 < GRID_SIZE && grid[x + 1][y] == 0) return true;
    if(y - 1 >= 0 && grid[x][y - 1] == 0) return true;
    if(y + 1 < GRID_SIZE && grid[x][y + 1] == 0) return true;
    return false;
}

bool Board::is_second_valid_pos(int x, int y, int last_x, int last_y) {
    if(grid[x][y] != 0) return false;
    if(x - 1 == last_x && y == last_y) return true;
    if(x + 1 == last_x && y == last_y) return true;
    if(x == last_x && y - 1 == last_y) return true;
    if(x == last_x && y + 1 == last_y) return true;
    return false;
}

void Board::place(int symbol, int x, int y) {
    grid[x][y] = symbol;
}

int Board::count_points(LineType line_type, int i) {
    int points = 0;
    int last = -1, curr_cnt = 0, elem;

    for(int j = 0; j < GRID_SIZE; j++){
        if(line_type == DIAG) elem = grid[GRID_SIZE - 1 - j][j];
        else if(line_type == ROW) elem = grid[i][j];
        else elem = grid[j][i];

        if(elem == last){
            curr_cnt += 1;
        } else{
            points += get_points(curr_cnt);
            if(elem == 0) {
                last = -1;
                curr_cnt = 0;
            }
            else {
                last = elem;
                curr_cnt = 1;
            }
        }
    }
    return points + get_points((curr_cnt));
}

int Board::get_points(int symbol_cnt) {
    if(symbol_cnt == 5) return 10;
    if(symbol_cnt == 4) return 8;
    if(symbol_cnt == 3) return 3;
    if(symbol_cnt == 2) return 2;
    return 0;
}

bool Board::is_finished() {
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(is_first_valid_pos(i, j)) return false;
        }
    }
    return true;
}

void Board::draw_rect(RenderWindow *window, float width, float height, int x, int y, int line_width, Color fill,
                      Color line, Font* font, int txt_size, std::string string_text) {
    RectangleShape rect;
    rect.setSize(Vector2f(width, height));
    rect.setPosition(Vector2f(float(x), float(y)));
    rect.setFillColor(fill);
    rect.setOutlineThickness(line_width);
    rect.setOutlineColor(line);

    window->draw(rect);

    if(string_text != "") {
        Text text(string_text, *font, txt_size);
        text.setFillColor(Color::Black);

        FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(rect.getPosition().x + rect.getSize().x / 2.0, rect.getPosition().y + rect.getSize().y / 2.0);

        window->draw(text);
    }
}


void Board::draw(RenderWindow* window, Font* font) {
    int line_width = 2;
    Color color;
    // draw grid background
    draw_rect(window, CELL_SIZE * GRID_SIZE, CELL_SIZE * GRID_SIZE, BOARD_LEFT_OFFSET, BOARD_TOP_OFFSET, 5, Color::White, Color::Black,
              nullptr);

    // draw cells inside
    for(int row = 0; row < GRID_SIZE; row++){
        for(int col = 0; col < GRID_SIZE; col++){

            if(col == GRID_SIZE - 1 - row) color = Color(219, 222, 158);
            else if (col == 0 && row == 0) color = Color(158, 181, 222);
            else color = Color::White;

            draw_rect(window, CELL_SIZE, CELL_SIZE, BOARD_LEFT_OFFSET + col * CELL_SIZE, BOARD_TOP_OFFSET + row * CELL_SIZE, line_width,
            color, Color::Black, font, 3 * CELL_SIZE / 4, get_symbol(grid[row][col]));
        }
    }
}

void Board::draw_with_points(RenderWindow *window, Font *font) {
    int line_width = 2, sum_points = 0, curr_points;
    LineType line_type;
    Color grey = Color(115, 115, 115);

    // sum cols
    for(int i = -1; i < GRID_SIZE; i++){
        if(i == -1) line_type = DIAG;
        else line_type = COL;

        curr_points = count_points(line_type, i);
        sum_points += curr_points;
        draw_rect(window, CELL_SIZE, CELL_SIZE, BOARD_LEFT_OFFSET + i * CELL_SIZE, BOARD_TOP_OFFSET + line_width + GRID_SIZE * CELL_SIZE, line_width,
                  Color::White, grey, font, 3 * CELL_SIZE / 4, std::to_string(curr_points));
    }

    // sum rows
    for(int i = -1; i < GRID_SIZE; i++){
        if(i == -1) line_type = DIAG;
        else line_type = ROW;
        curr_points = count_points(line_type, i);
        sum_points += curr_points;
        draw_rect(window, CELL_SIZE, CELL_SIZE, BOARD_LEFT_OFFSET + line_width + GRID_SIZE * CELL_SIZE, BOARD_TOP_OFFSET + i * CELL_SIZE, line_width,
                  Color::White, grey, font, 3 * CELL_SIZE / 4, std::to_string(curr_points));

    }

    // sum points
    total_score = sum_points;
    draw_rect(window, CELL_SIZE, CELL_SIZE, BOARD_LEFT_OFFSET + GRID_SIZE * CELL_SIZE + line_width,
              BOARD_TOP_OFFSET + GRID_SIZE * CELL_SIZE + line_width, line_width, Color(141, 209, 140), grey, font,
              3 * CELL_SIZE / 4, std::to_string(sum_points));

    // draw grid
    draw(window, font);

}

std::string Board::get_symbol(int i) {
    if(i == 1) return "*";
    if(i == 2) return "/";
    if(i == 3) return "o";
    if(i == 4) return "X";
    if(i == 5) return "#";
    if(i == 6) return "@";
    return "";
}

int Board::get_total_score() {
    return total_score;
}
