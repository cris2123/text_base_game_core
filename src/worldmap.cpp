#include "worldMap.h"
#include <iostream>

void WorldMap::createWorldMap(int max_rooms)
{
    
    // For now just like this
    roomInstances[_Room1] = new Room1();
    std::cout << "Creado el mapa del juego" << std::endl;
    
    // Create a function to manage instances of my classes with new states and new changes
    // this instances will be stored on a dict page
};

void WorldMap::updateRoom(Room* roomUpdate, RoomName r_name)
{
    std::cout << "Room to update" << std::endl;
}

Room* WorldMap::getRoom( RoomName roomKey)
{
    return roomInstances.at(roomKey);

    // need to save old instance value inside map, and then need to get new one,
    // i want to save it because i dont know if it will be destroyed 
    // Test: test if a modify an old class with the reference, if i change with another reference, and the
    // go back with the first one, if last changes are ok or where deleted

};