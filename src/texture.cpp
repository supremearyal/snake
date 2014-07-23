#include "texture.h"

#include <cstdlib>
#include <cstdio>
#include <algorithm>

Texture::Texture(SDL_Renderer *renderer) :
    renderer(renderer),
    resource("../resources")
{
    addTexture(SNAKE_BODY_LEFT_RIGHT , "snakeLeftRightBody.bmp"); 
    addTexture(SNAKE_BODY_UP_DOWN    , "snakeUpDownBody.bmp");
    addTexture(SNAKE_BODY_LEFT_UP    , "snakeLeftUpBody.bmp");
    addTexture(SNAKE_BODY_LEFT_DOWN  , "snakeLeftDownBody.bmp");
    addTexture(SNAKE_BODY_RIGHT_UP   , "snakeRightUpBody.bmp");
    addTexture(SNAKE_BODY_RIGHT_DOWN , "snakeRightDownBody.bmp");

    addTexture(SNAKE_HEAD_LEFT       , "snakeHeadLeft.bmp");
    addTexture(SNAKE_HEAD_RIGHT      , "snakeHeadRight.bmp");
    addTexture(SNAKE_HEAD_UP         , "snakeHeadUp.bmp");
    addTexture(SNAKE_HEAD_DOWN       , "snakeHeadDown.bmp");

    addTexture(SNAKE_TAIL_LEFT       , "snakeTailLeft.bmp");
    addTexture(SNAKE_TAIL_RIGHT      , "snakeTailRight.bmp");
    addTexture(SNAKE_TAIL_UP         , "snakeTailUp.bmp");
    addTexture(SNAKE_TAIL_DOWN       , "snakeTailDown.bmp");

    addTexture(POWER                 , "power.bmp");
    addTexture(GAME_OVER             , "gameOver.bmp");
    addTexture(FONT                  , "font.bmp");
}

Texture::~Texture()
{
    for (auto i : textures)
        SDL_DestroyTexture(i.second);
}

SDL_Texture* Texture::getTexture(int textureID) const
{
    auto i = textures.find(textureID);
    if (i != std::end(textures))
        return i->second;

    return nullptr;
}

void Texture::addTexture(int textureID, const char *path)
{
    SDL_Surface *surface = resource.loadImage(path);
    textures[textureID] = SDL_CreateTextureFromSurface(renderer, surface);
    if (textures[textureID] == nullptr)
    {
        SDL_Quit();
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(surface);
}

SDL_Texture* Texture::getPieceTexture(Piece::Piece piece) const
{
    switch (piece)
    {
    case Piece::LEFT:
    case Piece::RIGHT:
        return getTexture(SNAKE_BODY_LEFT_RIGHT);
    case Piece::UP:
    case Piece::DOWN:
        return getTexture(SNAKE_BODY_UP_DOWN);
    case Piece::LEFT_UP:
    case Piece::DOWN_RIGHT:
        return getTexture(SNAKE_BODY_LEFT_UP);
    case Piece::LEFT_DOWN:
    case Piece::UP_RIGHT:
        return getTexture(SNAKE_BODY_LEFT_DOWN);
    case Piece::RIGHT_UP:
    case Piece::DOWN_LEFT:
        return getTexture(SNAKE_BODY_RIGHT_UP);
    case Piece::RIGHT_DOWN:
    case Piece::UP_LEFT:
        return getTexture(SNAKE_BODY_RIGHT_DOWN);
    default:
        return nullptr;
    }
}

SDL_Texture* Texture::getHeadTexture(Piece::Piece piece) const
{
    switch (piece)
    {
    case Piece::LEFT:
        return getTexture(SNAKE_HEAD_LEFT);
    case Piece::RIGHT:
        return getTexture(SNAKE_HEAD_RIGHT);
    case Piece::UP:
        return getTexture(SNAKE_HEAD_UP);
    case Piece::DOWN:
        return getTexture(SNAKE_HEAD_DOWN);
    default:
        return nullptr;
    }
}

SDL_Texture* Texture::getTailTexture(Piece::Piece piece) const
{
    switch (piece)
    {
    case Piece::LEFT:
        return getTexture(SNAKE_TAIL_LEFT);
    case Piece::RIGHT:
        return getTexture(SNAKE_TAIL_RIGHT);
    case Piece::UP:
        return getTexture(SNAKE_TAIL_UP);
    case Piece::DOWN:
        return getTexture(SNAKE_TAIL_DOWN);
    default:
        return nullptr;
    }
}

std::pair<int, int> getDimension(SDL_Texture *texture)
{
    Uint32 format;
    int access;
    int width;
    int height;
    SDL_QueryTexture(texture, &format, &access, &width, &height);

    return std::make_pair(width, height);
}


int Texture::getWidth(SDL_Texture *texture)
{
    return getDimension(texture).second;
}

int Texture::getHeight(SDL_Texture *texture)
{
    return getDimension(texture).first;
}
