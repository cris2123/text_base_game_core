#include <iostream>
#include "user.h"
#include "room.h"

using g_input = std::tuple<std::string, std::vector<std::string>, std::unordered_map<std::string, std::string>>;

void User::setInitialState()
{
    std::cout << "Setting initial State" << std::endl;

    roomRef = worldmap->getRoom(_Room1);

    std::cout << "Set user on room1 " << std::endl;

};

void User::initUser(WorldMap *map)
{
    parser.initSemantics();
    parser.command = "";

    worldmap = map;
    worldmap->createWorldMap(1);

    setInitialState();

};

g_input User::getInput()
{

    g_input gameInput;
    parser.command = parser.getCommand();
    parser.lexCommand(parser.command);
    gameInput = parser.parseCommand(parser.command);

    return gameInput;
};

void User::printUserInput(g_input& userInput)
{

    std::cout << "########## UserInput ######################" << std::endl;
    std::cout << "Grammar: " << std::get<0>(userInput) << std::endl;
    for (auto key : std::get<1>(userInput))
    {
        std::cout << "key: " << key << " ";
    }
    std::cout << std::endl;
    for (auto expression : std::get<2>(userInput))
    {

        std::cout << expression.first << "::";
        std::cout << expression.second << std::endl;
    }
    std::cout << "############################################" << std::endl;
};

RoomName User::handleInput(g_input& gameInput)
{

    // here i will pass a reference to gameInput  and from here, all state machines will process
    // this work, after this just need to handle everything related to the game
    // testing that i made it here

    std:: cout << "Dentro de la funcion de handle input del cuarto" << std::endl;
    printUserInput(gameInput);

    roomRef->handleInput(gameInput, userRoomState);

    return _Room1;
    
};

void User::setRoom(RoomName newRoomRef)
{

    // roomref and userRoomState are class variables
    Room* r;

    if(userRoomState != newRoomRef)
    {
       
       r = worldmap->getRoom(newRoomRef);
       worldmap->updateRoom(roomRef,userRoomState);
       roomRef = r;
       userRoomState = newRoomRef;
    }
    
}
