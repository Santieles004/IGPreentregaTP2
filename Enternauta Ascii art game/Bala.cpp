#include "Bala.h"

Bala::Bala(int x, int y, Tipo tipo, int velocidad) 
    : m_x(x), m_y(y), m_tipo(tipo), m_velocidad(velocidad), m_activa(true) {}

void Bala::update() {
    m_y += m_velocidad;
    
    // Desactivar si sale de la pantalla
    if (m_y < 1 || m_y > 39) {
        m_activa = false;
    }
}

void Bala::draw() {
    if (m_tipo == Tipo::PROTAGONISTA) {
        mvaddch(m_y, m_x, '|');
    } else {
        mvaddch(m_y, m_x, '\'');
    }
}