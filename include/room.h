#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>

using g_input = std::tuple<std::string, std::vector<std::string>, std::unordered_map<std::string, std::string>>;

enum RoomName {
    _Room1,
    _Room2,
    _Room3,
    _Room4
};

enum Position
{

    North,
    South,
    West,
    East

};

class Room
{

    public:

        std::string description;
        int zone_numbers;
        Position statePosition = South;
        virtual RoomName handleInput(g_input& gameInput, RoomName r_name) = 0;
};

// Testing class

class RoomPositionMechanics
{
public:
    virtual std::string getInput() = 0;
    virtual void handleRoomPosition() = 0;
};

class RoomPositionInterface
{
    public:

        virtual Position handleRoomNorthPosition() = 0;
        virtual Position handleRoomSouthPosition() = 0;
        virtual Position handleRoomEastPosition() = 0;
        virtual Position handleRoomWestPosition() = 0;
};

class Room1 : public Room, public RoomPositionMechanics , public RoomPositionInterface
{

    public:

        Room1(){};
        virtual RoomName handleInput(g_input &gameInput, RoomName r_name);
        virtual std::string getInput();
        virtual void handleRoomPosition();

        // Position interface
        virtual Position handleRoomNorthPosition();
        virtual Position handleRoomSouthPosition();
        virtual Position handleRoomEastPosition();
        virtual Position handleRoomWestPosition();
};


//////////////////////////////

// New classes to manage room state
// class RoomPositionMechanics
// {
//     public:
//         virtual std::string getInput() =0;
//         virtual void handleRoomPosition() = 0;
// };

// class RoomPositionInterface
// {
//     public:

//         virtual Position handleRoomNorthPosition() = 0;
//         virtual Position handleRoomSouthPosition() = 0;
//         virtual Position handleRoomEastPosition() = 0;
//         virtual Position handleRoomWestPosition() = 0;
// };

// class Room1 : public Room, public RoomPositionMechanics, public RoomPositionInterface
// {
// public:

//     Position statePosition = South;
//     std::string input = "";

//     Room1(){};

//     Room1(const Room1 &room);
//     Room1 &operator=(const Room1 &room)
//     {
//         statePosition = room.statePosition;
//         return *this;
//     }

//     std::string getInput();
//     virtual RoomName handleInput(std::string command);
//     void handleRoomPosition();
//     virtual Position handleRoomNorthPosition();
//     virtual Position handleRoomSouthPosition();
//     virtual Position handleRoomWestPosition();
//     virtual Position handleRoomEastPosition();
 
// };

