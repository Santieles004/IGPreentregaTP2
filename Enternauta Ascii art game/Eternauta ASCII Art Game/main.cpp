#include <iostream>
#include <ncurses.h>
#include <vector>
#include <algorithm>  // Añadido para remove_if
#include <chrono>
#include <thread>
#include "Eternauta.h"
#include "Nieve.h"
#include "Cascarudo.h"
#include "HumanoControlado.h"
#include "Bala.h"
#include "Objeto.h"
#include "Pantalla.h"

using namespace std;

// Constantes del juego
const int ANCHO = 120;
const int ALTO = 40;
const int DELAY = 50;

// Estados del juego
enum GameState {
    INTRO,
    MENU_PRINCIPAL,
    JUGANDO,
    PAUSA,
    GAME_OVER,
    NIVEL_COMPLETADO,
    SALIR
};

// Variables globales - cambiadas a punteros para evitar problemas de inicialización
GameState estado_juego;
int nivel;
int puntaje;
Eternauta* juanSalvo = nullptr;  // Cambiado a puntero
vector<Nieve> coposNieve;
vector<Cascarudo> cascarudos;
vector<HumanoControlado> humanos;
vector<Bala> balasEnemigas;
vector<Objeto> objetos;
Pantalla pantallas;

// Prototipos de funciones
void setup();
void input();
void update();
void draw();
void mostrarIntro();
void mostrarMenu();
void mostrarGameOver();
void mostrarNivelCompletado();
void cambiarNivel(int nuevoNivel);

int main() {
    setlocale(LC_ALL, "");
    
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    
    if (LINES < ALTO || COLS < ANCHO) {
        endwin();
        cout << "La terminal debe tener al menos " << ANCHO << "x" << ALTO << " caracteres." << endl;
        return 1;
    }
    
    estado_juego = INTRO;
    nivel = 0;
    puntaje = 0;
    
    while (estado_juego != SALIR) {
        switch (estado_juego) {
            case INTRO:
                mostrarIntro();
                break;
            case MENU_PRINCIPAL:
                mostrarMenu();
                break;
            case JUGANDO:
                setup();
                while (estado_juego == JUGANDO) {
                    input();
                    update();
                    draw();
                    napms(DELAY);
                }
                break;
            case GAME_OVER:
                mostrarGameOver();
                break;
            case NIVEL_COMPLETADO:
                mostrarNivelCompletado();
                break;
            default:
                break;
        }
    }
    
    // Liberar memoria
    delete juanSalvo;
    
    endwin();
    return 0;
}

void setup() {
    // Liberar memoria anterior si existe
    delete juanSalvo;
    juanSalvo = new Eternauta(ANCHO/2, ALTO-5);  // Usar new para crear el objeto
    
    coposNieve.clear();
    cascarudos.clear();
    humanos.clear();
    balasEnemigas.clear();
    objetos.clear();
    
    if (nivel == 1) {
        for (int i = 0; i < 7; i++) {
            coposNieve.push_back(Nieve(rand() % (ANCHO-2) + 1, 1));
        }
        
        // Aparecerá el casco después de 10 segundos
        Objeto casco(ANCHO/2, 5, Objeto::Tipo::CASCO);
        objetos.push_back(casco);
    } 
    else if (nivel == 2) {
        for (int i = 0; i < 5; i++) {
            cascarudos.push_back(Cascarudo(rand() % (ANCHO-4) + 2, 1));
        }
        
        // Aparecen armas en el nivel 2
        Objeto revolver(ANCHO/3, 5, Objeto::Tipo::REVOLVER);
        Objeto escopeta(2*ANCHO/3, 5, Objeto::Tipo::ESCOPETA);
        objetos.push_back(revolver);
        objetos.push_back(escopeta);
    } 
    else if (nivel == 3) {
        for (int i = 0; i < 5; i++) {
            humanos.push_back(HumanoControlado(rand() % (ANCHO-6) + 3, 5));
        }
    }
}

void input() {
    int tecla = getch();
    
    switch (tecla) {
        case KEY_LEFT:
            juanSalvo->mover(-1, 0);
            break;
        case KEY_RIGHT:
            juanSalvo->mover(1, 0);
            break;
        case KEY_UP:
            juanSalvo->mover(0, -1);
            break;
        case KEY_DOWN:
            juanSalvo->mover(0, 1);
            break;
        case 'z':
            juanSalvo->disparar(balasEnemigas);
            break;
        case 'p':
        case 'P':
            estado_juego = PAUSA;
            break;
        case 27: // ESC
            estado_juego = MENU_PRINCIPAL;
            break;
        default:
            break;
    }
}

void update() 
{
    // Actualizar Juan Salvo
    juanSalvo->update();
    
    // Verificar si Juan Salvo tiene casco y llega al borde derecho para pasar de nivel
    if (nivel == 1 && juanSalvo->tieneCasco() && juanSalvo->getX() >= ANCHO - 3) {
        // Mostrar mensaje de transición al nivel 2
        erase();
        mvprintw(ALTO/2 - 3, ANCHO/2 - 20, "¡CONSEGUISTE EL CASCO!");
        mvprintw(ALTO/2 - 1, ANCHO/2 - 25, "Ahora estas protegido de la nieve toxica");
        mvprintw(ALTO/2 + 1, ANCHO/2 - 30, "Llegaron los cascarudos a la Tierra...");
        mvprintw(ALTO/2 + 3, ANCHO/2 - 15, "[Aqui estara el ASCII art de cascarudos]");
        mvprintw(ALTO/2 + 6, ANCHO/2 - 15, "Presiona ENTER para continuar");
        refresh();
        
        // Esperar a que presione ENTER
        while (getch() != '\n') {}
        
        cambiarNivel(2);
        return;
    }
    
    // Actualizar nieve
    if (nivel == 1) 
    {
        for (auto& copo : coposNieve) 
        {
            copo.update();
            
            // Colisión con Juan Salvo (solo si no tiene casco)
            if (juanSalvo->colisionCon(copo.getX(), copo.getY()) && !juanSalvo->tieneCasco()) 
            {
                juanSalvo->recibirDano();
            }
        }
    }
    // Comprobar si se completó el nivel 2
if (cascarudos.empty() && nivel == 2) {
    // Mostrar mensaje de transición al nivel 3
    erase();
    mvprintw(ALTO/2 - 3, ANCHO/2 - 20, "¡DERROTASTE A LOS CASCARUDOS!");
    mvprintw(ALTO/2 - 1, ANCHO/2 - 25, "Pero ahora El Mano controla a los humanos...");
    mvprintw(ALTO/2 + 1, ANCHO/2 - 30, "Debes liberarlos de su control mental");
    mvprintw(ALTO/2 + 3, ANCHO/2 - 15, "[Aqui estara el ASCII art de humanos controlados]");
    mvprintw(ALTO/2 + 6, ANCHO/2 - 15, "Presiona ENTER para continuar");
    refresh();
    
    while (getch() != '\n') {}
    
    cambiarNivel(3);
}
    
    // Actualizar humanos controlados
    if (nivel == 3) {
        for (auto& humano : humanos) {
            humano.update();
            
            // Disparar aleatoriamente
            if (rand() % 100 < 2) { // 2% de probabilidad de disparar en cada frame
                humano.disparar(balasEnemigas);
            }
            
            // Colisión con balas de Juan Salvo
            for (auto& bala : balasEnemigas) {
                if (bala.getTipo() == Bala::Tipo::PROTAGONISTA && 
                    humano.colisionCon(bala.getX(), bala.getY())) {
                    humano.recibirDano();
                    bala.setActiva(false);
                    
                    if (humano.estaMuerto()) {
                        puntaje += 150;
                    }
                }
            }
        }
        
        // Eliminar humanos muertos
        humanos.erase(
            remove_if(humanos.begin(), humanos.end(), 
                     [](HumanoControlado& h) { return h.estaMuerto(); }),
            humanos.end()
        );
        
        // Comprobar si se completó el nivel 3
        if (humanos.empty()) {
            estado_juego = NIVEL_COMPLETADO;
        }
    }
    
    // Actualizar balas
    for (auto& bala : balasEnemigas) {
        bala.update();
    }
    
    // Eliminar balas inactivas
    balasEnemigas.erase(
        remove_if(balasEnemigas.begin(), balasEnemigas.end(), 
                 [](Bala& b) { return !b.estaActiva(); }),
        balasEnemigas.end()
    );
    
    // Actualizar objetos
    for (auto& objeto : objetos) {
        // Colisión con Juan Salvo
        if (juanSalvo->colisionCon(objeto.getX(), objeto.getY())) {
            juanSalvo->recogerObjeto(objeto.getTipo());
            objeto.setRecogido(true);
            puntaje += 50;
        }
    }
    
    // Eliminar objetos recogidos
    objetos.erase(
        remove_if(objetos.begin(), objetos.end(), 
                 [](Objeto& o) { return o.estaRecogido(); }),
        objetos.end()
    );
    
    // Comprobar si Juan Salvo murió
    if (juanSalvo->estaMuerto()) {
        estado_juego = GAME_OVER;
    }
}

void draw() {
    erase();
    box(stdscr, 0, 0);
    
    // Dibujar HUD
    mvprintw(0, 2, "NIVEL: %d", nivel);
    mvprintw(0, 15, "PUNTOS: %d", puntaje);
    mvprintw(0, 35, "ENERGIA: ");
    for (int i = 0; i < juanSalvo->getEnergia(); i++) {
        mvaddch(0, 44 + i, ACS_CKBOARD);
    }
    mvprintw(0, 50, "VIDAS: ");
    for (int i = 0; i < juanSalvo->getVidas(); i++) {
        mvaddch(0, 57 + i, ACS_DIAMOND);
    }
    mvprintw(0, 65, "ARMA: ");
    switch (juanSalvo->getArmaActual()) {
        case Eternauta::Arma::NINGUNA:
            mvprintw(0, 71, "NINGUNA");
            break;
        case Eternauta::Arma::PALO:
            mvprintw(0, 71, "PALO");
            break;
        case Eternauta::Arma::REVOLVER:
            mvprintw(0, 71, "REVOLVER");
            break;
        case Eternauta::Arma::ESCOPETA:
            mvprintw(0, 71, "ESCOPETA");
            break;
    }
    if (juanSalvo->tieneCasco()) {
        mvprintw(0, 85, "CASCO: SI");
    } else {
        mvprintw(0, 85, "CASCO: NO");
    }
    
    // Dibujar elementos del juego según el nivel
    if (nivel == 1) {
        for (auto& copo : coposNieve) {
            copo.draw();
        }
    } 
    else if (nivel == 2) {
        for (auto& cascarudo : cascarudos) {
            cascarudo.draw();
        }
    } 
    else if (nivel == 3) {
        for (auto& humano : humanos) {
            humano.draw();
        }
    }
    
    // Dibujar balas
    for (auto& bala : balasEnemigas) {
        bala.draw();
    }
    
    // Dibujar objetos
    for (auto& objeto : objetos) {
        objeto.draw();
    }
    
    // Dibujar a Juan Salvo
    juanSalvo->draw();
    
    refresh();
}

void mostrarIntro() {
    pantallas.mostrarIntro();
    estado_juego = MENU_PRINCIPAL;
}

void mostrarMenu() {
    int opcion = pantallas.mostrarMenu();
    
    switch (opcion) {
        case 1: // Jugar
            nivel = 1;
            estado_juego = JUGANDO;
            break;
        case 2: // Salir
            estado_juego = SALIR;
            break;
        default:
            break;
    }
}

void mostrarGameOver() {
    pantallas.mostrarGameOver(puntaje);
    
    int tecla = getch();
    if (tecla == 's' || tecla == 'S') {
        estado_juego = MENU_PRINCIPAL;
    } else {
        estado_juego = SALIR;
    }
}

void mostrarNivelCompletado() {
    pantallas.mostrarNivelCompletado(nivel, puntaje);
    
    if (nivel < 3) {
        cambiarNivel(nivel + 1);
        estado_juego = JUGANDO;
    } else {
        // Juego completado
        pantallas.mostrarFinal();
        estado_juego = MENU_PRINCIPAL;
    }
}

void cambiarNivel(int nuevoNivel) {
    nivel = nuevoNivel;
    setup();
}