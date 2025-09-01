#pragma once
#include <ncurses.h>

class Bala {
public:
    enum class Tipo {
        PROTAGONISTA,
        ENEMIGA
    };
    
    Bala(int x, int y, Tipo tipo, int velocidad);
    void update();
    void draw();
    
    void setActiva(bool activa) { m_activa = activa; }
    
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    Tipo getTipo() const { return m_tipo; }
    bool estaActiva() const { return m_activa; }
    
private:
    int m_x, m_y;
    Tipo m_tipo;
    int m_velocidad;
    bool m_activa;
};