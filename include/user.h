#pragma once
#include <string>
#include "commandParser.h"
#include "worldMap.h"
#include <unordered_map>

// We would create a class World Map where we could would have list
// of all rooms on the game, instantiated. Also we will create a method to add n rooms to taht list.
//Then user class , would take
// te corresponding instance base on handleInput result

using g_input = std::tuple<std::string, std::vector<std::string>, std::unordered_map<std::string, std::string>>;

class UserState
{

public:

    virtual ~UserState(){};
    //UserState *handleInput(std::string input){};
    virtual RoomName handleInput(g_input& gameInput) = 0;
    virtual void updateState(){};
};

class User : public UserState
{
    public:

        //Variable of our user, maybe put private later
        CommandParser parser;
        WorldMap *worldmap;
        Room *roomRef;
        RoomName userRoomState;

        User(){};

        // Initializing user states
        void initUser(WorldMap *map);
        void setInitialState();

        void setRoom(RoomName newRef);
        void setState();

        // hadling user input
        RoomName handleInput(g_input& gameInput); // Reference of a room, better return a enum and take
        g_input getInput();

        // utils function to print user input
        void User::printUserInput(g_input& userInput);
                
};










