#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>
#include <SDL2/SDL.h>

class Resource
{
public:
    Resource(const char *relativeDirectory);
    virtual ~Resource();

    std::string getPath(const char *file);
    SDL_Surface* loadImage(const char *file);
private:
    std::string relativeDirectory;
    std::string absoluteDirectory;
};

#endif
