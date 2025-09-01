#pragma once
#include <ncurses.h>
#include <cstdlib> // Para rand()

class Nieve {
public:
    Nieve(int x, int y);
    void update();  // Añadir este método
    void draw();
    
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    
private:
    float m_x, m_y;  // Cambiar a float para movimiento suave
    float m_velocidad;
};