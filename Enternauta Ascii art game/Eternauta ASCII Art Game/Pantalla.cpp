#include <cstring>
#include "Pantalla.h"
#include <iostream>
#include <chrono>
#include <thread>

void Pantalla::mostrarIntro() {
    erase();
    
    // Pantalla 1: Título
    const char* titulo[] = {
        "  _______  _        _                                 _        _        ",
        " |__   __|| |      | |                               | |      | |       ",
        "    | |   | |_ ___ | | _ __   __ _  _ __    __ _   __| |  ___ | |_ __ _ ",
        "    | |   | __/ _ \\| || '__| / _` || '_ \\  / _` | / _` | / _ \\| __/ _` |",
        "    | |   | ||  __/| || |   | (_| || | | || (_| || (_| ||  __/| || (_| |",
        "    |_|    \\__\\___||_||_|    \\__,_||_| |_| \\__,_| \\__,_| \\___| \\__\\__,_|",
        "",
        "                           Presiona ENTER para continuar"
    };
    
    mostrarASCII(titulo, 7, 5);
    esperarEnter();
    
    // Pantalla 2: Introducción
    const char* intro1[] = {
        "Buenos Aires, 1963. Una noche como cualquier otra,",
        "Juan Salvo y sus amigos juegan al truco cuando...",
        "",
        "De repente, una extraña nevada tóxica cubre la ciudad.",
        "Quienes se exponen a ella mueren instantáneamente.",
        "",
        "Solo unos pocos logran refugiarse a tiempo.",
        "Pero esto es solo el comienzo de una pesadilla...",
        "",
        "Presiona ENTER para continuar"
    };
    
    erase();
    for (int i = 0; i < 9; i++) {
        mvprintw(5 + i, 10, "%s", intro1[i]);
    }
    esperarEnter();
    
    // Pantalla 3: Continuación
    const char* intro2[] = {
        "Pronto descubrirán que esta no es una invasión común.",
        "Seres extraterrestres llamados 'cascarudos' y humanos",
        "controlados mentalmente por 'El Mano' amenazan con",
        "exterminar a toda la humanidad.",
        "",
        "Juan Salvo, ahora conocido como El Eternauta,",
        "deberá luchar por su supervivencia y la de sus amigos.",
        "",
        "Presiona ENTER para comenzar"
    };
    
    erase();
    for (int i = 0; i < 8; i++) {
        mvprintw(5 + i, 10, "%s", intro2[i]);
    }
    esperarEnter();
}

int Pantalla::mostrarMenu() {
    erase();
    box(stdscr, 0, 0);
    
    const char* titulo[] = {
        "  _______  _        _                                 _        _        ",
        " |__   __|| |      | |                               | |      | |       ",
        "    | |   | |_ ___ | | _ __   __ _  _ __    __ _   __| |  ___ | |_ __ _ ",
        "    | |   | __/ _ \\| || '__| / _` || '_ \\  / _` | / _` | / _ \\| __/ _` |",
        "    | |   | ||  __/| || |   | (_| || | | || (_| || (_| ||  __/| || (_| |",
        "    |_|    \\__\\___||_||_|    \\__,_||_| |_| \\__,_| \\__,_| \\___| \\__\\__,_|",
        ""
    };
    
    mostrarASCII(titulo, 6, 2);
    
    mvprintw(15, 50, "1. Jugar");
    mvprintw(17, 50, "2. Salir");
    mvprintw(20, 45, "Selecciona una opción: ");
    
    refresh();
    
    int opcion = getch();
    while (opcion != '1' && opcion != '2') {
        opcion = getch();
    }
    
    return (opcion == '1') ? 1 : 2;
}

void Pantalla::mostrarGameOver(int puntaje) {
    erase();
    box(stdscr, 0, 0);
    
    const char* gameOver[] = {
        "   _____                         ____                 ",
        "  / ____|                       / __ \\                ",
        " | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ ",
        " | | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|",
        " | |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   ",
        "  \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   ",
        ""
    };
    
    mostrarASCII(gameOver, 6, 5);
    
    mvprintw(15, 50, "Puntuación final: %d", puntaje);
    mvprintw(18, 45, "¿Volver a jugar? (S/N)");
    
    refresh();
}

void Pantalla::mostrarNivelCompletado(int nivel, int puntaje) {
    erase();
    box(stdscr, 0, 0);
    
    mvprintw(10, 50, "¡NIVEL %d COMPLETADO!", nivel);
    mvprintw(12, 50, "Puntuación: %d", puntaje);
    
    if (nivel < 3) {
        mvprintw(15, 45, "Preparándose para el siguiente nivel...");
    } else {
        mvprintw(15, 45, "¡Felicidades! Has completado el juego.");
    }
    
    mvprintw(20, 45, "Presiona ENTER para continuar");
    
    refresh();
    esperarEnter();
}

void Pantalla::mostrarFinal() {
    erase();
    box(stdscr, 0, 0);
    
    const char* final[] = {
        "¡FELICITACIONES!",
        "",
        "Has logrado sobrevivir a la invasión y derrotar a El Mano.",
        "Pero la lucha apenas comienza...",
        "",
        "Juan Salvo se convertirá en El Eternauta,",
        "viajero de la eternidad, luchando por la libertad",
        "a través de infinitos mundos y dimensiones.",
        "",
        "Esta es solo una de sus muchas historias.",
        "",
        "Presiona ENTER para volver al menú principal"
    };
    
    for (int i = 0; i < 11; i++) {
        mvprintw(5 + i, 10, "%s", final[i]);
    }
    
    refresh();
    esperarEnter();
}

void Pantalla::mostrarASCII(const char* asciiArt[], int lineas, int y) {
    for (int i = 0; i < lineas; i++) {
        mvprintw(y + i, (COLS - strlen(asciiArt[i])) / 2, "%s", asciiArt[i]);
    }
    refresh();
}

void Pantalla::esperarEnter() {
    while (getch() != '\n') {
        // Esperar hasta que se presione ENTER
    }
}