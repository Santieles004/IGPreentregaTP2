#include "Nieve.h"
#include <cstdlib>

Nieve::Nieve(int x, int y) : m_x(x), m_y(y), m_velocidad(0.5f) {}

void Nieve::update() {
    m_y += m_velocidad;
    
    if (m_y >= 39) {
        m_x = rand() % 118 + 1;
        m_y = 1;
        m_velocidad = 0.3f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(0.7f)));
    }
}

void Nieve::draw() {
    mvaddch(static_cast<int>(m_y), m_x, '*');
}