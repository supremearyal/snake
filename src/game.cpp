#include "game.h"

#include "window.h"
#include "board.h"

#include <algorithm>

Game::Game() :
    running(true),
    paused(false),
    window("Snake", 300, 300, 2),
    board(window.getRenderer(), 30, 30)
{
}

Game::~Game()
{
}

void Game::run()
{
    int frameCount = 0;
    while (running)
    {
        Uint32 beginTime = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event))
            handleEvent(event);

        Uint32 endTime = SDL_GetTicks();
        Uint32 elapsedTime = endTime - beginTime;
        if (MSPF > elapsedTime)
            SDL_Delay(MSPF - elapsedTime);

        if (!paused && !board.isGameOver())
        {
            ++frameCount;
            if (frameCount == 100 / MSPF)
            {
                board.move();
                frameCount = 0;
            }
            
            window.clear();
            board.draw(window);
            window.update();
        }
        else
        {
            frameCount = 0;
        }
    }
}

void Game::handleEvent(const SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_QUIT:
        running = false;
        break;
    case SDL_KEYDOWN:
        SDL_Keycode keycode = event.key.keysym.sym;
        if (paused && !(keycode == SDLK_SPACE ||
                        keycode == SDLK_ESCAPE))
            break;
        
        switch (keycode)
        {
        case SDLK_ESCAPE:
            running = false;
            break;
        case SDLK_SPACE:
            if (board.isGameOver())
            {
                board.reset();
                paused = false;
            }
            else
            {
                paused = !paused;
            }
            break;
        case SDLK_LEFT:
        case SDLK_a:
            board.setDirection(Direction::LEFT);
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            board.setDirection(Direction::RIGHT);
            break;
        case SDLK_UP:
        case SDLK_w:
            board.setDirection(Direction::UP);
            break;
        case SDLK_DOWN:
        case SDLK_s:
            board.setDirection(Direction::DOWN);
            break;
        }
        break;
    }
}
