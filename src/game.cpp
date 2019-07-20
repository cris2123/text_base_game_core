#include "game.h"
#include "user.h"
//#include "room.h"
#include "worldMap.h"
#include <iostream>
#include <string>

using g_input = std::tuple<std::string, std::vector<std::string>, std::unordered_map<std::string, std::string>>;

#define DEBUG

void Game::about()
{

    std::string synopsis = " Este es un juego sobre un joven que al despertar se encuentra en una habitación misteriosa, con su mochila y \
un puñado de recurdos difusos acerca e un viaje familiar. Lograremos resolver todos los acertijos y peligros que enfrentara \
este joven en esta misteriosa habitación ?";

    std::cout << synopsis << std::endl;
}

void Game::initGame()
{

    Game::about();
    User user;
    CommandParser parser;
    
    user.initUser(new WorldMap());
    
    std::cout << "Iprimiendo el estado del cuarto" << std::endl;
    std::cout << user.roomRef->statePosition << std::endl;

    RoomName room;

    g_input userInput;

        // maybe some state initialization check after some test
    for (;;)
    {
        userInput = user.getInput();
        user.printUserInput(userInput);
        room = user.handleInput(userInput);
        std::cout << "Made it here" << std::endl;
        user.parser.v = {};
    }
}

void Game::waitingForInput(CommandParser &parser)
{

    parser.command = parser.getCommand();

    #ifdef DEBUG
        std::cout << parser.command << std::endl;
    #endif
};

void Game::mainMenu()
{

    std::string input;

    while (true)
    {

        std::getline(std::cin, input);

        if (input.length() > 1)
        {
            std::cout << "Por favor introduce en tu respuesta un solo caracter" << std::endl;
            continue;
        }

        if (input[0] == 'q')
        {
            exit(0);
        }
        else if (input[0] == 'p')
        {
            break;
        }

        else
        {

            std::cout << "No elegiste ninguna opcion de las especificadas, por favor intenta de nuevo" << std::endl;
            continue;
        }
    };

    initGame();
};