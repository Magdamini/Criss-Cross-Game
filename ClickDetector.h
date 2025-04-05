#ifndef PROJECT_CLICKDETECTOR_H
#define PROJECT_CLICKDETECTOR_H

#include <SFML/Graphics.hpp>

class ClickDetector{
private:
    bool last_click = true;
public:
    bool is_clicked();


};

#endif //PROJECT_CLICKDETECTOR_H
