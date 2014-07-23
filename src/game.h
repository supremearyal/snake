#ifndef GAME_H_
#define GAME_H_

#include "window.h"
#include "board.h"

#include <SDL2/SDL.h>

class Game
{
public:
    Game();
    virtual ~Game();
    void run();
private:
    void handleEvent(const SDL_Event &event);

    bool running;
    bool paused;

    Window window;
    Board board;

    static const Uint32 FPS = 30;
    static const Uint32 MSPF = 1000 / FPS;
};

#endif
