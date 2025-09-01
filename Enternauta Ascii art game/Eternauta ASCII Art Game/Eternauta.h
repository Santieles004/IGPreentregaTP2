#pragma once
#include <ncurses.h>
#include <vector>
#include "Bala.h"
#include "Objeto.h"

class Eternauta {
public:
    enum class Estado {
        NORMAL,
        CON_PALO,
        CON_CASCO,
        CON_CASCO_Y_REVOLVER,
        CON_CASCO_Y_ESCOPETA,
        MUERTO
    };
    
    enum class Arma {
        NINGUNA,
        PALO,
        REVOLVER,
        ESCOPETA
    };
    
    Eternauta() : Eternauta(0, 0) {}  // Constructor por defecto añadido
    Eternauta(int x, int y);
    void update();
    void draw();
    void mover(int dx, int dy);
    void disparar(std::vector<Bala>& balas);
    void recibirDano();
    void recogerObjeto(Objeto::Tipo tipo);
    
    bool colisionCon(int x, int y) const;
    bool tieneCasco() const;
    bool estaMuerto() const;
    
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getEnergia() const { return m_energia; }
    int getVidas() const { return m_vidas; }
    Arma getArmaActual() const { return m_arma; }
    
private:
    int m_x, m_y;
    int m_energia;
    int m_vidas;
    Estado m_estado;
    Arma m_arma;
    bool m_tieneCasco;
    
    void actualizarEstado();
};