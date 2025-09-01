#include "Cascarudo.h"
#include <cstdlib>

Cascarudo::Cascarudo(int x, int y) 
    : m_x(x), m_y(y), m_velocidad(0.3f), m_vida(3), m_muerto(false) {}

void Cascarudo::update() {
    m_y += m_velocidad;
    
    if (m_y >= 39) {
        m_x = rand() % 116 + 2;
        m_y = 1;
    }
}

void Cascarudo::draw() {
    // Dibujar cascarudo (3x2)
    mvaddch(m_y, m_x, ACS_ULCORNER);
    mvaddch(m_y, m_x + 1, ACS_HLINE);
    mvaddch(m_y, m_x + 2, ACS_URCORNER);
    mvaddch(m_y + 1, m_x, ACS_LLCORNER);
    mvaddch(m_y + 1, m_x + 1, ACS_HLINE);
    mvaddch(m_y + 1, m_x + 2, ACS_LRCORNER);
}

void Cascarudo::recibirDano(Eternauta::Arma arma) {
    if (arma == Eternauta::Arma::REVOLVER) {
        m_vida -= 1;
    } else if (arma == Eternauta::Arma::ESCOPETA) {
        m_vida -= 3;
    } else if (arma == Eternauta::Arma::PALO) {
        m_vida -= 1;
    }
    
    if (m_vida <= 0) {
        m_muerto = true;
    }
}

bool Cascarudo::colisionCon(int x, int y) const {
    // Hitbox solo en la cabeza (centro superior)
    return (x == m_x + 1 && y == m_y);
}

bool Cascarudo::estaMuerto() const {
    return m_muerto;
}