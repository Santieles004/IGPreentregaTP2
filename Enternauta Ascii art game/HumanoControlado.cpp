#include "HumanoControlado.h"
#include <cstdlib>

HumanoControlado::HumanoControlado(int x, int y) 
    : m_x(x), m_y(y), m_direccion(1), m_vida(1), 
      m_muerto(false), m_contadorMovimiento(0) {}

void HumanoControlado::update() {
    m_contadorMovimiento++;
    
    // Cambiar dirección aleatoriamente
    if (m_contadorMovimiento >= 20) {
        m_direccion = (rand() % 3) - 1; // -1, 0, o 1
        m_contadorMovimiento = 0;
    }
    
    // Moverse horizontalmente
    m_x += m_direccion;
    
    // Mantener dentro de los límites
    if (m_x < 3) m_x = 3;
    if (m_x > 116) m_x = 116;
}

void HumanoControlado::draw() {
    // Dibujar humano controlado (con antena)
    mvaddch(m_y, m_x + 1, 'O');
    mvaddch(m_y, m_x, '^'); // Antena
    mvaddch(m_y + 1, m_x, '/');
    mvaddch(m_y + 1, m_x + 1, '|');
    mvaddch(m_y + 1, m_x + 2, '\\');
    mvaddch(m_y + 2, m_x + 1, 'A'); // Arma
}

void HumanoControlado::disparar(std::vector<Bala>& balas) {
    balas.push_back(Bala(m_x + 1, m_y + 3, Bala::Tipo::ENEMIGA, 1));
}

void HumanoControlado::recibirDano() {
    m_vida--;
    if (m_vida <= 0) {
        m_muerto = true;
    }
}

bool HumanoControlado::colisionCon(int x, int y) const {
    // Hitbox de 3x3
    return (x >= m_x && x <= m_x + 2 && y >= m_y && y <= m_y + 2);
}

bool HumanoControlado::estaMuerto() const {
    return m_muerto;
}