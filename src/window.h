#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL2/SDL.h>
#include <string>

class Window
{
public:
    Window(const char *name, int boardWidth, int boardHeight, int scalePixel);
    virtual ~Window();
    void clear();
    void update();
    int getBoardWidth() const
    {
        return boardWidth;
    }
    int getBoardHeight() const
    {
        return boardHeight;
    }
    int getScalePixel() const
    {
        return scalePixel;
    }
    SDL_Renderer* getRenderer() const
    {
        return renderer;
    }
private:
    SDL_Window *window;
    int boardWidth;
    int boardHeight;
    int scalePixel;

    SDL_Renderer *renderer;

    static int const START_POS_X = 100;
    static int const START_POS_Y = 100;
public:
    static int const INFO_SCREEN_HEIGHT = 100;
};

#endif
