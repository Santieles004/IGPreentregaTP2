#pragma once
#include <ncurses.h>

class Nieve {
public:
    Nieve(int x, int y);
    void update();
    void draw();
    
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    
private:
    int m_x, m_y;
    float m_velocidad;
};