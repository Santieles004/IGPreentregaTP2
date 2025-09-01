#pragma once
#include <ncurses.h>
#include "Eternauta.h"

class Cascarudo {
public:
    Cascarudo(int x, int y);
    void update();
    void draw();
    void recibirDano(Eternauta::Arma arma);
    
    bool colisionCon(int x, int y) const;
    bool estaMuerto() const;
    
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    
private:
    int m_x, m_y;
    float m_velocidad;
    int m_vida;
    bool m_muerto;
};