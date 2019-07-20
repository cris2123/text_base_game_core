#include <iostream>
#include "commandParser.h"
#include "game.h"

#define DEBUG

int main() {

    std::cout << "First game ever, text based for now!" << std::endl;

    std::cout << "Este es un juego prototipo realizado para experimentar que se necesita para realizar un videojuego. \
    Para comenzar el juego presiona p, de lo contario presiona q" << std::endl;

    Game main_loop;

    main_loop.mainMenu();
    
}