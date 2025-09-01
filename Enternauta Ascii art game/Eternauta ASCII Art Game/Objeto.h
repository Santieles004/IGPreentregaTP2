#pragma once
#include <ncurses.h>

class Objeto {
public:
    enum class Tipo {
        PALO,
        REVOLVER,
        ESCOPETA,
        CASCO
    };
    
    Objeto(int x, int y, Tipo tipo);
    void draw();
    
    void setRecogido(bool recogido) { m_recogido = recogido; }
    
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    Tipo getTipo() const { return m_tipo; }
    bool estaRecogido() const { return m_recogido; }
    
private:
    int m_x, m_y;
    Tipo m_tipo;
    bool m_recogido;
};