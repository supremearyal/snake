#ifndef PIECE_H_
#define PIECE_H_

#include "direction.h"

namespace Piece
{
    enum Piece
    {
        INVALID = -1,
        EMPTY,
        POWER,
        LEFT,
        RIGHT,
        UP,
        DOWN,
        LEFT_UP,
        LEFT_DOWN,
        RIGHT_UP,
        RIGHT_DOWN,
        UP_LEFT,
        DOWN_LEFT,
        UP_RIGHT,
        DOWN_RIGHT,
    };

    bool isSnakePiece(Piece piece);
    Piece getPiece(Direction::Direction direction);
    Piece getPiece(Direction::Direction direction,
                   Direction::Direction nextDirection);
}

#endif
