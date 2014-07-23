#ifndef POSITION_H_
#define POSITION_H_

#include "direction.h"

struct Position
{
    int row;
    int col;

    Position operator+(const Position &p)
    {
        return {row + p.row, col + p.col};
    }

    bool operator==(const Position &position)
    {
        return row == position.row &&
               col == position.col;
    }

    bool operator!=(const Position &position)
    {
        return !operator==(position);
    }        
};

#endif
