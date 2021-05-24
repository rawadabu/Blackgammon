#include <iostream>
using namespace std;
#include "Board.h"
int main()
{
    Board board;
    board.set_turn();
    board.printBoard();
    board.playGame();

    return 0;
}
/*BACKGAMMON GAME.
ACCORDING TO MY CODE, I'VE USED TO WORK WITH 4 QUARTERS TO ADD/REMOVE/MOVE DISKS,
AND TO PRINT.
*/
