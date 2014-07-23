#ifndef BOARD_H_
#define BOARD_H_

#include "window.h"
#include "position.h"
#include "piece.h"
#include "direction.h"
#include "texture.h"

#include <vector>
#include <queue>

typedef std::vector<Piece::Piece> GridRow;
typedef std::vector<GridRow> Grid;

class Board
{
public:
    Board(SDL_Renderer *renderer, int numRows, int numCols);
    virtual ~Board();
    void draw(Window &window);
    void move();
    bool bounds(const Position &position);
    void setDirection(Direction::Direction direction);
    bool isGameOver() const { return gameOver; }
    bool isSnakePiece(Piece::Piece piece) const;
    Position getOffset(Direction::Direction direction) const;
    Piece::Piece getPiece(Direction::Direction direction) const;
    Piece::Piece getPiece(Direction::Direction direction,
                          Direction::Direction nextDirection) const;
    void reset();
private:
    int numRows;
    int numCols;
    Grid board;

    Position head;
    Position tail;
    Direction::Direction currentHeadDirection;
    std::queue<Direction::Direction> nextHeadDirections;
    Direction::Direction tailDirection;
    std::queue<Direction::Direction> bends;
    std::queue<Position> bendPositions;

    bool gameOver;
    int score;

    Texture texture;
public:
    static Position LEFT_OFFSET;
    static Position RIGHT_OFFSET;
    static Position UP_OFFSET;
    static Position DOWN_OFFSET;
    static Position ZERO_OFFSET;
};

#endif
