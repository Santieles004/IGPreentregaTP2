#include "Eternauta.h"
#include <cstdlib>

Eternauta::Eternauta(int x, int y) 
    : m_x(x), m_y(y), m_energia(3), m_vidas(3), 
      m_estado(Estado::NORMAL), m_arma(Arma::NINGUNA), 
      m_tieneCasco(false) {}

void Eternauta::update() {
    // Mantener dentro de los límites de la pantalla
    if (m_x < 1) m_x = 1;
    if (m_x > 118) m_x = 118;
    if (m_y < 1) m_y = 1;
    if (m_y > 38) m_y = 38;
    
    actualizarEstado();
}

void Eternauta::draw() {
    if (m_estado == Estado::MUERTO) {
        // Dibujar cuerpo caído
        mvaddch(m_y, m_x, '\\');
        mvaddch(m_y, m_x + 1, '_');
        mvaddch(m_y, m_x + 2, '/');
        mvaddch(m_y + 1, m_x + 1, 'o');
        return;
    }
    
    // Dibujar según el estado
    switch (m_estado) {
        case Estado::NORMAL:
            mvaddch(m_y, m_x + 1, 'O');
            mvaddch(m_y + 1, m_x, '/');
            mvaddch(m_y + 1, m_x + 1, '|');
            mvaddch(m_y + 1, m_x + 2, '\\');
            mvaddch(m_y + 2, m_x + 1, '^');
            break;
            
        case Estado::CON_PALO:
            mvaddch(m_y, m_x + 1, 'O');
            mvaddch(m_y + 1, m_x, '/');
            mvaddch(m_y + 1, m_x + 1, '|');
            mvaddch(m_y + 1, m_x + 2, '\\');
            mvaddch(m_y + 2, m_x, '|');
            break;
            
        case Estado::CON_CASCO:
            mvaddch(m_y, m_x + 1, ACS_PLUS);
            mvaddch(m_y + 1, m_x, '/');
            mvaddch(m_y + 1, m_x + 1, 'O');
            mvaddch(m_y + 1, m_x + 2, '\\');
            mvaddch(m_y + 2, m_x + 1, '^');
            break;
            
        case Estado::CON_CASCO_Y_REVOLVER:
            mvaddch(m_y, m_x + 1, ACS_PLUS);
            mvaddch(m_y + 1, m_x, '/');
            mvaddch(m_y + 1, m_x + 1, 'O');
            mvaddch(m_y + 1, m_x + 2, '\\');
            mvaddch(m_y + 2, m_x, '=');
            mvaddch(m_y + 2, m_x + 1, '=');
            mvaddch(m_y + 2, m_x + 2, '>');
            break;
            
        case Estado::CON_CASCO_Y_ESCOPETA:
            mvaddch(m_y, m_x + 1, ACS_PLUS);
            mvaddch(m_y + 1, m_x, '/');
            mvaddch(m_y + 1, m_x + 1, 'O');
            mvaddch(m_y + 1, m_x + 2, '\\');
            mvaddch(m_y + 2, m_x, '=');
            mvaddch(m_y + 2, m_x + 1, '=');
            mvaddch(m_y + 2, m_x + 2, 'E');
            break;
            
        default:
            break;
    }
}

void Eternauta::mover(int dx, int dy) {
    m_x += dx;
    m_y += dy;
}

void Eternauta::disparar(std::vector<Bala>& balas) {
    if (m_arma != Arma::NINGUNA && m_estado != Estado::MUERTO) {
        int velocidad = (m_arma == Arma::ESCOPETA) ? 2 : 1;
        balas.push_back(Bala(m_x + 1, m_y - 1, Bala::Tipo::PROTAGONISTA, -velocidad));
    }
}

void Eternauta::recibirDano() {
    if (m_tieneCasco && m_estado != Estado::NORMAL) {
        // El casco protege del daño
        return;
    }
    
    m_energia--;
    if (m_energia <= 0) {
        m_vidas--;
        m_energia = 3;
        
        if (m_vidas <= 0) {
            m_estado = Estado::MUERTO;
        }
    }
}

void Eternauta::recogerObjeto(Objeto::Tipo tipo) {
    switch (tipo) {
        case Objeto::Tipo::PALO:
            m_arma = Arma::PALO;
            break;
        case Objeto::Tipo::REVOLVER:
            m_arma = Arma::REVOLVER;
            break;
        case Objeto::Tipo::ESCOPETA:
            m_arma = Arma::ESCOPETA;
            break;
        case Objeto::Tipo::CASCO:
            m_tieneCasco = true;
            break;
    }
    
    actualizarEstado();
}

bool Eternauta::colisionCon(int x, int y) const {
    // Hitbox de 3x3 centrada en el personaje
    return (x >= m_x && x <= m_x + 2 && y >= m_y && y <= m_y + 2);
}

bool Eternauta::tieneCasco() const {
    return m_tieneCasco;
}

bool Eternauta::estaMuerto() const {
    return m_estado == Estado::MUERTO;
}

void Eternauta::actualizarEstado() {
    if (m_estado == Estado::MUERTO) return;
    
    if (m_tieneCasco) {
        if (m_arma == Arma::REVOLVER) {
            m_estado = Estado::CON_CASCO_Y_REVOLVER;
        } else if (m_arma == Arma::ESCOPETA) {
            m_estado = Estado::CON_CASCO_Y_ESCOPETA;
        } else {
            m_estado = Estado::CON_CASCO;
        }
    } else {
        if (m_arma == Arma::PALO) {
            m_estado = Estado::CON_PALO;
        } else {
            m_estado = Estado::NORMAL;
        }
    }
}