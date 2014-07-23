#include "resource.h"

Resource::Resource(const char *relativeDirectory) :
            relativeDirectory(relativeDirectory)
{
    char *absolutePath = SDL_GetBasePath();
    absoluteDirectory.append(absolutePath);
    SDL_free(absolutePath);
}

Resource::~Resource()
{
}

std::string Resource::getPath(const char *file)
{
    std::string path = absoluteDirectory;
    return path + relativeDirectory + '/' + file;
}

SDL_Surface* Resource::loadImage(const char *file)
{
    std::string snakeLeftRightPath = getPath(file);
    SDL_Surface *surface = SDL_LoadBMP(snakeLeftRightPath.c_str());
    if (surface == nullptr)
    {
        fprintf(stderr, "Couldn't find texture %s: %s\n",
                file, SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return surface;
}
