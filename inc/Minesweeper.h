#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <BoardGame.h>
#include <Space.h>
class Minesweeper : public BoardGame {
    //2d-Objects
    std::vector<std::vector<Space>> board;

    int height;
    int width;
    int mines;
    int totalMines;
    int foundMines;
    int flags;
    int gameState;
    bool firstClick;
public:
    Minesweeper();
    Minesweeper(int, int, int);
    Minesweeper(const Minesweeper& other);
    
    //Setters
    void setHeight(int height);
    void setWidth(int width);
    void setMines(int mines);
    void setBoard(std::vector<std::vector<Space>> board);
    void setFirstClick(bool first);
    
    //Getters
    int getHeight() const;
    int getWidth() const;
    int getMines() const;
    bool getFirstClick() const;
    std::vector<std::vector<Space>> getBoard() const;

    //Virtual Functions from boardgame
    void reset();
    void handle(int, int, MouseButton=left);
    ucm::json getBoard();

    //Addtional Utility Functions
    void openSpace(int  x, int y);
    void generateMines();
    void countNearbyMines();
    void initializeBoard();

	~Minesweeper(); 
};

#endif
