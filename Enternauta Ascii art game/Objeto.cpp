#include "Objeto.h"

Objeto::Objeto(int x, int y, Tipo tipo) 
    : m_x(x), m_y(y), m_tipo(tipo), m_recogido(false) {}

void Objeto::draw() {
    if (m_recogido) return;
    
    switch (m_tipo) {
        case Tipo::PALO:
            mvaddch(m_y, m_x, '|');
            break;
        case Tipo::REVOLVER:
            mvaddch(m_y, m_x, 'R');
            break;
        case Tipo::ESCOPETA:
            mvaddch(m_y, m_x, 'E');
            break;
        case Tipo::CASCO:
            mvaddch(m_y, m_x, 'C');
            break;
    }
}