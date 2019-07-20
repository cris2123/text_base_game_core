#include "commandParser.h"

class Game
{

private:
    void about();

public:
    Game(){};

    void mainMenu();
    void initGame();
    void waitingForInput(CommandParser &parser);
    void quit();
};