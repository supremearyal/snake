#include "board.h"

#include "window.h"

#include <SDL2/SDL.h>
#include <cstdlib>

Position Board::LEFT_OFFSET  = {0, -1};
Position Board::RIGHT_OFFSET = {0, 1};
Position Board::UP_OFFSET    = {-1, 0};
Position Board::DOWN_OFFSET  = {1, 0};
Position Board::ZERO_OFFSET  = {0, 0};

Board::Board(SDL_Renderer *renderer, int numRows, int numCols) :
    numRows(numRows),
    numCols(numCols),
    board(Grid(numRows, GridRow(numCols, Piece::EMPTY))),
    texture(renderer)
{
    reset();
}

void Board::draw(Window &window)
{
    SDL_Renderer *renderer = window.getRenderer();
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);

    int scaleX = window.getBoardWidth() / numCols * window.getScalePixel();
    int scaleY = window.getBoardHeight() / numRows * window.getScalePixel();

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            SDL_Rect rect = { j * scaleX,
                              i * scaleY + Window::INFO_SCREEN_HEIGHT,
                              scaleX, scaleY };
            if (board[i][j] == Piece::EMPTY)
            {
                SDL_RenderFillRect(renderer, &rect);
            }
            else if (board[i][j] == Piece::POWER)
            {
                SDL_Texture *powerTexture = texture.getTexture(Texture::POWER);
                SDL_RenderCopy(renderer, powerTexture, nullptr, &rect);
            }
            else
            {
                SDL_Texture *snakeTexture =
                    texture.getPieceTexture(board[i][j]);
                SDL_RenderCopy(renderer, snakeTexture, nullptr, &rect);
            }
        }
    }

    SDL_Rect rect = { tail.col * scaleX,
                      tail.row * scaleY + Window::INFO_SCREEN_HEIGHT,
                      scaleX, scaleY };
    Piece::Piece currentTailPiece = Piece::getPiece(tailDirection);
    SDL_Texture *tailTexture = texture.getTailTexture(currentTailPiece);
    SDL_RenderCopy(renderer, tailTexture, nullptr, &rect);

    rect = { head.col * scaleX,
             head.row * scaleY + Window::INFO_SCREEN_HEIGHT,
             scaleX, scaleY };
    Piece::Piece currentHeadPiece = Piece::getPiece(currentHeadDirection);
    SDL_Texture *headTexture = texture.getHeadTexture(currentHeadPiece);
    SDL_RenderCopy(renderer, headTexture, nullptr, &rect);

    if (gameOver)
    {
        SDL_Texture *rawTexture = texture.getTexture(Texture::GAME_OVER);
        SDL_Rect rect = { 0, Window::INFO_SCREEN_HEIGHT,
                          Texture::getWidth(rawTexture),
                          Texture::getHeight(rawTexture) };
        SDL_RenderCopy(renderer, rawTexture, nullptr, &rect);
    }

    for (int i = 5, digitScore = score; i >= 0; --i, digitScore /= 10)
    {
        SDL_Texture *fontTexture = texture.getTexture(Texture::FONT);
        int fontWidth = Texture::getHeight(fontTexture);
        int fontHeight = Texture::getWidth(fontTexture) / 10;
        int digit = digitScore % 10;
        SDL_Rect srcRect = { 0, digit * fontHeight,
                             fontWidth, fontHeight };
        SDL_Rect dstRect = { i * fontWidth, 0,
                             fontWidth, fontHeight };
        SDL_RenderCopy(renderer, fontTexture, &srcRect, &dstRect);
    }
}

Board::~Board()
{
}

void Board::move()
{
    if (gameOver)
        return;

    Direction::Direction nextHeadDirection = currentHeadDirection;
    if (!nextHeadDirections.empty())
    {
        nextHeadDirection = nextHeadDirections.front();
        nextHeadDirections.pop();
    }

    if (nextHeadDirection != currentHeadDirection)
    {
        bends.push(nextHeadDirection);
        bendPositions.push(head);
    }
    
    Position headOffset = getOffset(nextHeadDirection);
    if (bounds(head + headOffset))
    {
        board[head.row][head.col] = Piece::getPiece(currentHeadDirection,
                                                    nextHeadDirection);
        head = head + headOffset;

        currentHeadDirection = nextHeadDirection;

        if (board[head.row][head.col] != Piece::POWER)
        {
            if (!bendPositions.empty() &&
                bendPositions.front() == tail)
            {
                tailDirection = bends.front();
                bends.pop();
                bendPositions.pop();
            }

            board[tail.row][tail.col] = Piece::EMPTY;
            Position tailOffset = getOffset(tailDirection);
            tail = tail + tailOffset;

            if (!bendPositions.empty() &&
                bendPositions.front() == tail)
            {
                tailDirection = bends.front();
                bends.pop();
                bendPositions.pop();
            }
        }
        else
        {
            score += 10;
            
            int row = rand() % numRows;
            int col = rand() % numCols;
            while (board[row][col] > 0)
            {
                row = rand() % numRows;
                col = rand() % numCols;
            }
            board[row][col] = Piece::POWER;
        }

        gameOver = Piece::isSnakePiece(board[head.row][head.col]);
    }
    else
    {
        gameOver = true;
    }
}

bool Board::bounds(const Position &position)
{
    return position.row >= 0 &&
           position.row < numRows &&
           position.col >= 0 &&
           position.col < numCols;
}

void Board::setDirection(Direction::Direction direction)
{
    Direction::Direction previousDirection = currentHeadDirection;
    if (!nextHeadDirections.empty())
    {
        previousDirection = nextHeadDirections.front();
    }
    
    if ((direction != previousDirection)                &&
        ((previousDirection == Direction::LEFT  &&
          direction         != Direction::RIGHT)    ||
         (previousDirection == Direction::RIGHT &&
          direction         != Direction::LEFT)     ||
         (previousDirection == Direction::UP    &&
          direction         != Direction::DOWN)     ||
         (previousDirection == Direction::DOWN  &&
          direction         != Direction::UP)))
    {
        nextHeadDirections.push(direction);
    }
}


Position Board::getOffset(Direction::Direction direction) const
{
    switch (direction)
    {
    case Direction::LEFT:
        return LEFT_OFFSET;
    case Direction::RIGHT:
        return RIGHT_OFFSET;
    case Direction::UP:
        return UP_OFFSET;
    case Direction::DOWN:
        return DOWN_OFFSET;
    case Direction::INVALID:
    default:
        return ZERO_OFFSET;
    }
}

void Board::reset()
{
    for (auto &row : board)
        for (auto &col : row)
            col = Piece::EMPTY;
    
    head = {0, 10};
    tail = {0, 0};
    currentHeadDirection = Direction::RIGHT;
    tailDirection = currentHeadDirection;

    nextHeadDirections = std::queue<Direction::Direction>();
    bends = std::queue<Direction::Direction>();
    bendPositions = std::queue<Position>();

    for (int i = tail.col; i <= head.col; ++i)
        board[0][i] = Piece::getPiece(currentHeadDirection,
                                      currentHeadDirection);

    int row = rand() % numRows;
    int col = rand() % numCols;
    while (board[row][col] != Piece::EMPTY)
    {
        row = rand() % numRows;
        col = rand() % numCols;
    }
    board[row][col] = Piece::POWER;

    gameOver = false;
    score = 0;
}
