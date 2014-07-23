#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "resource.h"
#include "piece.h"

#include <SDL2/SDL.h>
#include <map>

class Texture
{
public:
    Texture(SDL_Renderer *renderer);
    virtual ~Texture();

    SDL_Texture* getTexture(int textureID) const;

    SDL_Texture* getPieceTexture(Piece::Piece piece) const;
    SDL_Texture* getHeadTexture(Piece::Piece piece) const;
    SDL_Texture* getTailTexture(Piece::Piece piece) const;

    static int getWidth(SDL_Texture *texture);
    static int getHeight(SDL_Texture *texture);

    static int const SNAKE_BODY_LEFT_RIGHT = 0;
    static int const SNAKE_BODY_UP_DOWN    = 1;
    static int const SNAKE_BODY_LEFT_UP    = 2;
    static int const SNAKE_BODY_LEFT_DOWN  = 3;
    static int const SNAKE_BODY_RIGHT_UP   = 4;
    static int const SNAKE_BODY_RIGHT_DOWN = 5;

    static int const SNAKE_HEAD_LEFT       = 6;
    static int const SNAKE_HEAD_RIGHT      = 7;
    static int const SNAKE_HEAD_UP         = 8;
    static int const SNAKE_HEAD_DOWN       = 9;

    static int const SNAKE_TAIL_LEFT       = 10;
    static int const SNAKE_TAIL_RIGHT      = 11;
    static int const SNAKE_TAIL_UP         = 12;
    static int const SNAKE_TAIL_DOWN       = 13;

    static int const POWER                 = 14;
    static int const GAME_OVER             = 15;
    static int const FONT                  = 16;
private:
    void addTexture(int textureID, const char *path);

    SDL_Renderer *renderer;
    Resource resource;
    std::map<int, SDL_Texture*> textures;
};

#endif
