#pragma once
#include <ncurses.h>
#include <vector>
#include "Bala.h"

class HumanoControlado {
public:
    HumanoControlado(int x, int y);
    void update();
    void draw();
    void disparar(std::vector<Bala>& balas);
    void recibirDano();
    
    bool colisionCon(int x, int y) const;
    bool estaMuerto() const;
    
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    
private:
    int m_x, m_y;
    int m_direccion;
    int m_vida;
    bool m_muerto;
    int m_contadorMovimiento;
};