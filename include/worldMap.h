#pragma once
#include <unordered_map>
#include <string>

#include "room.h"


class WorldMap
{
    public:
        void createWorldMap( int max_rooms);
        Room* getRoom(RoomName roomKey);
        void WorldMap::updateRoom(Room *roomUpdate, RoomName r_name);
        std::unordered_map<RoomName, Room *> roomInstances;
};

// to do this better i need to update old state with new data, save the state  data
// and then i need to get new state to work with it