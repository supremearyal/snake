#include "window.h"

#include <cstdlib>

Window::Window(const char *name, int boardWidth, int boardHeight,
               int scalePixel) :
    boardWidth(boardWidth),
    boardHeight(boardHeight),
    scalePixel(scalePixel)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Can't initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    
    window = SDL_CreateWindow(name, START_POS_X, START_POS_Y,
                              boardWidth * scalePixel,
                              boardHeight * scalePixel + INFO_SCREEN_HEIGHT, 0);
    if (window == nullptr)
    {
        fprintf(stderr, "Can't create SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        fprintf(stderr, "Can't create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

void Window::clear()
{
    SDL_SetRenderDrawColor(renderer, 0xff, 0x5A, 0x23, 0xff);
    SDL_RenderClear(renderer);
}

void Window::update()
{
    SDL_RenderPresent(renderer);
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
