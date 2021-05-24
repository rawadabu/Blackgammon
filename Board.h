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
    void setBoard();           /*SETTING BOARD*/
    void set_turn();           /*SETTING TURN*/
    bool doMove();             /*DO THE NEXT MOVE*/
    bool playGame();           /*PLAY THE GAME*/
    int MaxCulUp();            
    int MaxCulDown();          
    bool blackCorner();        /*CHECKS IF ALL BLACK DISKS AT HOME*/
    bool whiteCorner();        /*CHECKS IF ALL WHITE DISKS AT HOME*/
    Color checkDiskColor(int); 
    int checkDiskNumber(int);  
    void addDisk(int);         
    void deleteDisk(int);      
    bool moveDisk(int, int);   
    void switchTurn();         
    void printBoard();         
    void setSeed(unsigned int);
    void setRandom();
};

#endif // !BOARD_H_
