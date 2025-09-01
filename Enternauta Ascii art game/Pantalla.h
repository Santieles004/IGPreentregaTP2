#pragma once
#include <ncurses.h>

class Pantalla {
public:
    void mostrarIntro();
    int mostrarMenu();
    void mostrarGameOver(int puntaje);
    void mostrarNivelCompletado(int nivel, int puntaje);
    void mostrarFinal();
    
private:
    void mostrarASCII(const char* asciiArt[], int lineas, int y);
    void esperarEnter();
};