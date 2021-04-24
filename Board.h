#ifndef BOARD_H_
#define BOARD_H_
#include <iostream>
#include <cmath>
#include <string>
#include "Square.h"
#include "Random.h"
using namespace std;
class Board
{
    Square board[30][13];
    Color turn;
    int whitePiecesAtHome, blackPiecesAtHome;
    int whiteCapturedPieceNumber, blackCapturedPieceNumber;
    bool whiteCapturedPiece, blackCapturedPiece;
    bool flagSecondDice, flagFirstDice;
    Color winner;
    unsigned int myseed;
    customRandom random;

public:
    Board(); /*DONE*/
    ~Board();
    void setBoard();           /*DONE*/
    void set_turn();           /*DONE*/
    bool doMove();             /*DONE*/
    bool playGame();           /*DONE*/
    int MaxCulUp();            /*DONE*/
    int MaxCulDown();          /*DONE*/
    bool blackCorner();        /*CHECKS IF ALL BLACK DISKS AT HOME*/
    bool whiteCorner();        /*CHECKS IF ALL WHITE DISKS AT HOME*/
    Color checkDiskColor(int); /*DONE*/
    int checkDiskNumber(int);  /*DONE*/
    void addDisk(int);         /*DONE*/
    void deleteDisk(int);      /*DONE*/
    bool moveDisk(int, int);   /*DONE&NEED MORE IF*/
    void switchTurn();         /*DONE*/
    void printBoard();         /*DONE*/
    void setSeed(unsigned int);
    void setRandom();
};

#endif // !BOARD_H_
