#include "ClickDetector.h"
using namespace sf;

bool ClickDetector::is_clicked() {
    if(Mouse::isButtonPressed(sf::Mouse::Left) && !last_click){
        last_click = true;
        return true;
    } else if(!Mouse::isButtonPressed(sf::Mouse::Left)) last_click = false;
    return false;
}

