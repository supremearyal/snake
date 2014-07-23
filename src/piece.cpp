#include "piece.h"

namespace Piece
{
    bool isSnakePiece(Piece piece)
    {
        return piece == Piece::LEFT       ||
               piece == Piece::RIGHT      ||
               piece == Piece::UP         ||
               piece == Piece::DOWN       ||
               piece == Piece::LEFT_UP    ||
               piece == Piece::LEFT_DOWN  ||
               piece == Piece::RIGHT_UP   ||
               piece == Piece::RIGHT_DOWN ||
               piece == Piece::UP_LEFT    ||
               piece == Piece::DOWN_LEFT  ||
               piece == Piece::UP_RIGHT   ||
               piece == Piece::DOWN_RIGHT;
    }

    Piece getPiece(Direction::Direction direction)
    {
        switch (direction)
        {
        case Direction::LEFT:
            return Piece::LEFT;
        case Direction::RIGHT:
            return Piece::RIGHT;
        case Direction::UP:
            return Piece::UP;
        case Direction::DOWN:
            return Piece::DOWN;
        case Direction::INVALID:
        default:
            return Piece::INVALID;
        }
    }

    Piece getPiece(Direction::Direction direction,
                   Direction::Direction nextDirection)
    {
        if (direction == nextDirection)
            return getPiece(direction);

        if (direction == Direction::LEFT &&
            nextDirection == Direction::UP)
        {
            return Piece::LEFT_UP;
        }
        else if (direction == Direction::LEFT &&
            nextDirection == Direction::DOWN)
        {
            return Piece::LEFT_DOWN;
        }
        else if (direction == Direction::RIGHT &&
            nextDirection == Direction::UP)
        {
            return Piece::RIGHT_UP;
        }
        else if (direction == Direction::RIGHT &&
            nextDirection == Direction::DOWN)
        {
            return Piece::RIGHT_DOWN;
        }
        else if (direction == Direction::UP &&
            nextDirection == Direction::LEFT)
        {
            return Piece::UP_LEFT;
        }
        else if (direction == Direction::DOWN &&
            nextDirection == Direction::LEFT)
        {
            return Piece::DOWN_LEFT;
        }
        else if (direction == Direction::UP &&
            nextDirection == Direction::RIGHT)
        {
            return Piece::UP_RIGHT;
        }
        else if (direction == Direction::DOWN &&
            nextDirection == Direction::RIGHT)
        {
            return Piece::DOWN_RIGHT;
        }
        else
        {
            return Piece::INVALID;
        }
    }
}
