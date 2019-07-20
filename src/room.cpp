#include "room.h"
#include <iostream>


RoomName Room1::handleInput(g_input& gameInput, RoomName r_name) 
{
    // here we call getInput data
    std::cout << "Entre en la maquina de estado del cuarto Room1" << std::endl;
    // call state machine, is a wraper for all interaction

    // This is not a estate machine this part of the code parse my input and tell me 
    // Here i need to check my input and veryfy if i have a change of room position
    // if i have i will set statePosition to new position to evaluate machine state. If not
    // i will pass same room state postiion, this could be a private parameter
    

   

    // switch(userRoomState)
    // return room Position
    return _Room1;
};

// std::string Room1::getInput()
// {
//     return "Hola";
// };

Position Room1::handleRoomNorthPosition()
{

    return North;

};

Position Room1::handleRoomSouthPosition()
{

    return South;
};

Position Room1::handleRoomWestPosition()
{

    return West;
};

Position Room1::handleRoomEastPosition()
{

    return East;
};

std::string Room1::getInput(){

    return "N"; // This function will dissapear probably

};

void Room1::handleRoomPosition()
{

    std::string input = "";
    // State machine to manage  room positions (Norht, South, West, East)
    // in essence is a state machine which controls which state machine a i would call inside room layout
    switch (statePosition)
    {

    case North:

        if (getInput() == "N")
        {
            // here handle room position will return room State
            statePosition = handleRoomNorthPosition();
            //statePosition = North;
        }
        else if (getInput() == "S")
        {

            statePosition = handleRoomSouthPosition();
            // statePosition = South;
        }

        break;

    case South:

        if (getInput() == "N")
        {
            // here handle room position will return room State
            statePosition= handleRoomWestPosition();
            //statePosition = North;
        }
    }
};