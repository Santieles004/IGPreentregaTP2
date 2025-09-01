#include "Nieve.h"
#include <cstdlib>

Nieve::Nieve(int x, int y) : m_x(x), m_y(y), m_velocidad(0.5f) {}

void Nieve::update() {
    // Hacer que la nieve caiga con velocidad variable
    m_y += m_velocidad;
    
    // Si llega al fondo, reiniciar en una posición aleatoria arriba
    if (m_y >= 39) {
        m_x = rand() % 118 + 1; // Entre 1 y 118
        m_y = 1;
        m_velocidad = 0.3f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(0.7f)));
    }
}

void Nieve::draw() {
    mvaddch(static_cast<int>(m_y), static_cast<int>(m_x), '*');
}