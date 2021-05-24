#include <iostream>
#include "Board.h"
#include "Square.h"
#include <time.h>
#include <stdlib.h>
#include "Random.h"
using namespace std;

void Board::setBoard()
{
    board[0][0].setColor(WHITE);
    board[1][0].setColor(WHITE);
    board[2][0].setColor(WHITE);
    board[3][0].setColor(WHITE);
    board[4][0].setColor(WHITE);

    board[25][0].setColor(BLACK);
    board[26][0].setColor(BLACK);
    board[27][0].setColor(BLACK);
    board[28][0].setColor(BLACK);
    board[29][0].setColor(BLACK);

    board[0][4].setColor(BLACK);
    board[1][4].setColor(BLACK);
    board[2][4].setColor(BLACK);

    board[27][4].setColor(WHITE);
    board[28][4].setColor(WHITE);
    board[29][4].setColor(WHITE);

    board[0][7].setColor(BLACK);
    board[1][7].setColor(BLACK);
    board[2][7].setColor(BLACK);
    board[3][7].setColor(BLACK);
    board[4][7].setColor(BLACK);

    board[25][7].setColor(WHITE);
    board[26][7].setColor(WHITE);
    board[27][7].setColor(WHITE);
    board[28][7].setColor(WHITE);
    board[29][7].setColor(WHITE);

    board[0][12].setColor(WHITE);
    board[1][12].setColor(WHITE);

    board[28][12].setColor(BLACK);
    board[29][12].setColor(BLACK);
    //  board[29][6].setColor(WHITE);
}
Board::Board()
{
    setBoard();
    turn = NONE;
    winner = NONE;
    whitePiecesAtHome = blackPiecesAtHome = 0;
    whiteCapturedPiece = blackCapturedPiece = false;
    flagFirstDice = flagSecondDice = false;
    myseed = 0;
}

Board::~Board()
{
    cout << "d'ctor" << endl;
}
void Board::setSeed(unsigned int seed)
{
    myseed = seed;
}

void Board::set_turn()
{
    unsigned int seed;
    unsigned int blackPlayer,
        whitePlayer;
    if (turn == WHITE)
    {
        turn = BLACK;
    }
    else if (turn == BLACK)
    {
        turn = WHITE;
    }
    else
    {

        cout << "Enter seed" << endl;
        cin >> seed;
        setSeed(seed);
        cout << "White player casts 1, black player casts 2" << endl;
        /*DO THE MATH FOR WHICH PLAYER WILL START*/
        customRandom random(myseed);
        /* generate secret number between 1 and 6: */
        blackPlayer = random.get_rand() % 6 + 1;
        whitePlayer = random.get_rand() % 6 + 1;
        while (blackPlayer == whitePlayer)
        {
            whitePlayer = random.get_rand() % 6 + 1;
            blackPlayer = random.get_rand() % 6 + 1;
        }
        if (blackPlayer > whitePlayer)
        {
            cout << "Black plays first." << endl;
            turn = BLACK;
        }

        if (whitePlayer > blackPlayer)
        {
            cout << "White plays first." << endl;
            turn = WHITE;
        }
    }
}
/*MAX DISKS IN A GIVEN COLUMN*/
int Board::MaxCulUp()
{
    int MaxSum = 0;
    int Count = 0;
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j <= 15; j++)
        {
            if (board[j][i].getColor() != NONE)
                Count++;
        }
        if (Count > MaxSum)
        {
            MaxSum = Count;
            Count = 0;
        }
        else
            Count = 0;
    }
    return MaxSum;
}
int Board::MaxCulDown()
{

    int MaxSum = 0;
    int Count = 0;
    for (int i = 0; i < 12; i++)
    {
        for (int j = 15; j < 30; j++)
        {
            if (board[j][i].getColor() != NONE)
                Count++;
        }
        if (Count > MaxSum)
        {
            MaxSum = Count;
            Count = 0;
        }
        else
            Count = 0;
    }
    return MaxSum;
}
/*---------------------------------------------*/
/*TO MOVE ANY DISK FROM GIVEN COLUMN TO ANOTHER*/
bool Board::moveDisk(int src, int dest)
{
    if (turn == WHITE)
    {
        if (src == 25) /*IF ANY CAPTURED DISKS*/
        {
            if (checkDiskColor(dest) == WHITE || checkDiskNumber(dest) == 0)
            {
                deleteDisk(25);
                addDisk(dest);
                return true;
            }
        }
        if (checkDiskColor(dest) == BLACK && checkDiskNumber(dest) == 1 && checkDiskColor(src) == WHITE)
        { /*IAM WHITE AND MOVING DISK TO ONE BLACK DISK*/
            deleteDisk(dest);
            addDisk(dest);
            deleteDisk(src);
            addDisk(25);
            blackCapturedPiece = true;
            blackCapturedPieceNumber++;
            return true;
        }
        if (checkDiskColor(dest) == WHITE && checkDiskColor(src) == WHITE)
        { /*MOVING WHITE TO WHITE*/
            addDisk(dest);
            deleteDisk(src);
            return true;
        }

        if (((checkDiskColor(src) == WHITE && checkDiskNumber(dest) == 0 && (checkDiskColor(dest) == WHITE)) || (checkDiskColor(dest) == NONE) || (checkDiskColor(src) == WHITE && checkDiskColor(WHITE))))
        { /*MOVING WHITE TO EMPTY SPOT*/
            deleteDisk(src);
            addDisk(dest);
            return true;
        }

        return false;
    }
    if (turn == BLACK)
    {
        if (src == 25)
        {
            if (checkDiskColor(dest) == BLACK || checkDiskNumber(dest) == 0)
            {
                deleteDisk(25);
                addDisk(dest);
                return true;
            }
        }
        if (checkDiskColor(dest) == WHITE && checkDiskNumber(dest) == 1 && checkDiskColor(src) == BLACK)
        {
            deleteDisk(dest);
            addDisk(dest);
            deleteDisk(src);
            addDisk(25);
            whiteCapturedPiece = true;
            whiteCapturedPieceNumber++;
            return true;
        }
        if (checkDiskColor(dest) == BLACK && checkDiskColor(src) == BLACK)
        {
            deleteDisk(src);
            addDisk(dest);
            return true;
        }
        if (((checkDiskColor(src) == BLACK && checkDiskNumber(dest) == 0 && (checkDiskColor(dest) == BLACK)) || (checkDiskColor(dest) == NONE) || (checkDiskColor(src) == BLACK && checkDiskColor(BLACK))))
        {
            deleteDisk(src);
            addDisk(dest);
            return true;
        }
        return false;
    }
    return false;
}
/*---------------------------------------------*/
/*CHECKS IF ITS A LEGAL MOVE*/
bool Board::possibleMove(int src, int dest)
{
    if (turn == WHITE)
    {
        if (src == 25)
        {
            if (checkDiskColor(dest) == WHITE || checkDiskNumber(dest) == 0)
            {

                return true;
            }
        }
        if (checkDiskColor(dest) == BLACK && checkDiskNumber(dest) == 1 && checkDiskColor(src) == WHITE)
        { /*IAM WHITE AND MOVING DISK TO ONE BLACK DISK*/

            return true;
        }
        if (checkDiskColor(dest) == WHITE && checkDiskColor(src) == WHITE)
        { /*MOVING WHITE TO WHITE*/

            return true;
        }

        if (((checkDiskColor(src) == WHITE && checkDiskNumber(dest) == 0 && (checkDiskColor(dest) == WHITE)) || (checkDiskColor(dest) == NONE) || (checkDiskColor(src) == WHITE && checkDiskColor(WHITE))))
        { /*MOVING WHITE TO EMPTY SPOT*/

            return true;
        }
        cerr << "No possible move for White." << endl;
        return false;
    }
    if (turn == BLACK)
    {
        if (src == 25)
        {
            if (checkDiskColor(dest) == BLACK || checkDiskNumber(dest) == 0)
            {

                return true;
            }
        }
        if (checkDiskColor(dest) == WHITE && checkDiskNumber(dest) == 1 && checkDiskColor(src) == BLACK)
        {

            return true;
        }
        if (checkDiskColor(dest) == BLACK && checkDiskColor(src) == BLACK)
        {

            return true;
        }
        if (((checkDiskColor(src) == BLACK && checkDiskNumber(dest) == 0 && (checkDiskColor(dest) == BLACK)) || (checkDiskColor(dest) == NONE) || (checkDiskColor(src) == BLACK && checkDiskColor(BLACK))))
        {

            return true;
        }
        cerr << "No possible move for Black." << endl;
        return false;
    }
    return false; /*TO AVOID WARNING*/
}
/*---------------------------------------------*/
/*THE MAIN FUNCTION TO START THE GAME*/
bool Board::doMove()
{
    int src, dest, firstDice, secondDice;
    int if_dices_are_equals = 4;

    if (turn == BLACK)
    {
        /* generate secret number between 1 and 6: */
        firstDice = random.get_rand() % 6 + 1;
        secondDice = random.get_rand() % 6 + 1;
        cout << "Black rolls " << firstDice << "-" << secondDice << endl;

        if (firstDice != secondDice) /*ELSE, THE PLAYER CAN DO 4 MOVES*/
        {
            while ((!flagFirstDice || !flagSecondDice)) /*TO CHECK IF MY 2 DICES WERE CHOSEN*/
            {
                if (cin.fail()) /*FOR NONDIGIT INPUTS*/
                {
                    cerr << "Missing user input - quiting game." << endl;
                    return false;
                }
                cout << "Enter Black move: " << endl;
                cin >> src;
                cin >> dest;
                {
                    if (abs(src - dest) == firstDice) /*IF THE GIVEN MOVE ALLOWED(ACCORDING TO MY DICES)*/
                    {
                        if (!flagFirstDice)
                        {
                            if (blackCapturedPiece) /*IF CAPTURED DISK AVAILBLE*/
                            {
                                while (src != 25 && !possibleMove(src, dest))
                                {
                                    if (cin.fail())
                                    {
                                        cerr << "Missing user input - quiting game." << endl;
                                        return false;
                                    }
                                    cerr << "Illegal move: Player still has captured piece(s) ." << endl;
                                    cout << "Enter Black move: " << endl;
                                    cin >> src;
                                    cin >> dest;
                                }
                                blackCapturedPieceNumber--;
                                if (blackCapturedPieceNumber == 0)
                                {
                                    blackCapturedPiece = false;
                                }
                            }

                            while (!possibleMove(src, dest))
                            {
                                if (cin.fail())
                                {
                                    cerr << "Missing user input - quiting game." << endl;
                                    return false;
                                }
                                cout << "Enter Black move: " << endl;
                                cin >> src;
                                cin >> dest;
                            }
                            if (possibleMove(src, dest))
                            {
                                moveDisk(src, dest);
                                flagFirstDice = true;
                            }
                        }
                        else
                        {
                            cerr << "Illegal move: No value of " << abs(src - dest) << " in dice roll" << endl;
                        }
                    }
                    if (abs(src - dest) == secondDice)
                    {
                        if (!flagSecondDice)
                        {
                            if (blackCapturedPiece)
                            {
                                while (src != 25 && !possibleMove(src, dest))
                                {
                                    if (cin.eof())
                                    {
                                        cerr << "Missing user input - quiting game." << endl;
                                        return false;
                                    }
                                    cerr << "Illegal move: Player still has captured piece(s) ." << endl;
                                    cout << "Enter Black move: " << endl;
                                    cin >> src;
                                    cin >> dest;
                                }
                                blackCapturedPieceNumber--;
                                if (blackCapturedPieceNumber == 0)
                                {
                                    blackCapturedPiece = false;
                                }
                            }

                            while (!possibleMove(src, dest))
                            {
                                if (cin.eof())
                                {
                                    cerr << "Missing user input - quiting game." << endl;
                                    return false;
                                }
                                cout << "Enter Black move: " << endl;
                                cin >> src;
                                cin >> dest;
                            }
                            if (possibleMove(src, dest))
                            {
                                moveDisk(src, dest);
                                flagSecondDice = true;
                            }
                        }
                        else
                        {
                            cerr << "Illegal move: No value of " << abs(src - dest) << " in dice roll" << endl;
                        }
                    }
                    if ((src - dest) != firstDice && (src - dest) != secondDice)
                    {
                        if (cin.eof())
                        {
                            cerr << "Missing user input - quiting game." << endl;
                            return false;
                        }
                        cerr << "Illegal move: No value of " << abs(src - dest) << " in dice roll" << endl;
                        //  cerr << "Illegal move: Cannot capture more that one piece at location " << dest << endl;
                        cout << "Enter Black move: " << endl;
                        cin >> src;
                        cin >> dest;
                    }
                }
            }
        }
        else
        {
            // cout << "Same dice values, player BLACK can do 4 moves." << endl;
            if (blackCapturedPiece)
            {
                while (src != 25 && !possibleMove(src, dest))
                {
                    if (cin.eof())
                    {
                        cerr << "Missing user input - quiting game." << endl;
                        return false;
                    }
                    cerr << "Illegal move: Player still has captured piece(s) ." << endl;
                    cout << "Enter Black move: " << endl;
                    cin >> src;
                    cin >> dest;
                }
                moveDisk(src, dest);
                blackCapturedPieceNumber--;
                if (blackCapturedPieceNumber == 0)
                {
                    blackCapturedPiece = false;
                }
                if_dices_are_equals--;
            }
            for (int i = 0; i < if_dices_are_equals; i++)
            {
                cout << "Enter Black move: " << endl;
                cin >> src;
                cin >> dest;
                if (!moveDisk(src, dest))
                {
                    if (cin.eof())
                    {
                        cerr << "Missing user input - quiting game." << endl;
                        return false;
                    }
                    cout << "Enter Black move: " << endl;
                    cin >> src;
                    cin >> dest;
                }
            }
        }
        flagSecondDice = flagFirstDice = false;
        if_dices_are_equals = 4;
        return true;
    }

    if (turn == WHITE) /*SAME AS BLACK*/
    {
        /* generate secret number between 1 and 6: */
        firstDice = random.get_rand() % 6 + 1;
        secondDice = random.get_rand() % 6 + 1;
        cout << "White rolls " << firstDice << "-" << secondDice << endl;

        if (firstDice != secondDice)
        {
            while (!flagFirstDice || !flagSecondDice)
            {
                if (cin.eof())
                {
                    cerr << "Missing user input - quiting game." << endl;
                    return false;
                }
                cout << "Enter White move: " << endl;
                cin >> src;
                cin >> dest;
                {
                    if (abs(src - dest) == firstDice)
                    {
                        if (!flagFirstDice)
                        {
                            if (whiteCapturedPiece)
                            {
                                while (src != 25 && !possibleMove(src, dest))
                                {
                                    cerr << "Illegal move: Player still has captured piece(s) ." << endl;
                                    cout << "Enter White move: " << endl;
                                    cin >> src;
                                    cin >> dest;
                                }
                                whiteCapturedPieceNumber--;
                                if (whiteCapturedPieceNumber == 0)
                                {
                                    whiteCapturedPiece = false;
                                }
                            }

                            while (!possibleMove(src, dest))
                            {
                                if (cin.eof())
                                {
                                    cerr << "Missing user input - quiting game." << endl;
                                    return false;
                                }
                                cout << "Enter White move: " << endl;
                                cin >> src;
                                cin >> dest;
                            }
                            if (possibleMove(src, dest))
                            {
                                moveDisk(src, dest);
                                flagFirstDice = true;
                            }
                        }
                        else
                        {
                            cerr << "Illegal move: No value of " << abs(src - dest) << " in dice roll" << endl;
                        }
                    }
                    if (abs(src - dest) == secondDice)
                    {
                        if (!flagSecondDice)
                        {
                            if (whiteCapturedPiece)
                            {
                                while (src != 25 && !possibleMove(src, dest))
                                {
                                    cerr << "Illegal move: Player still has captured piece(s) ." << endl;
                                    cout << "Enter White move: " << endl;
                                    cin >> src;
                                    cin >> dest;
                                }
                                whiteCapturedPieceNumber--;
                                if (whiteCapturedPieceNumber == 0)
                                {
                                    whiteCapturedPiece = false;
                                }
                            }

                            while (!possibleMove(src, dest))
                            {
                                if (cin.eof())
                                {
                                    cerr << "Missing user input - quiting game." << endl;
                                    return false;
                                }
                                cout << "Enter White move: " << endl;
                                cin >> src;
                                cin >> dest;
                            }
                            if (possibleMove(src, dest))
                            {
                                moveDisk(src, dest);
                                flagSecondDice = true;
                            }
                        }
                        else
                        {
                            cerr << "Illegal move: No value of " << abs(src - dest) << " in dice roll" << endl;
                        }
                    }
                    if ((src - dest) != firstDice && (src - dest) != secondDice)
                    {
                        if (cin.eof())
                        {
                            cerr << "Missing user input - quiting game." << endl;
                            return false;
                        }
                        cerr << "Illegal move: No value of " << abs(src - dest) << " in dice roll" << endl;
                        //  cerr << "Illegal move: Cannot capture more that one piece at location " << dest << endl;
                        cout << "Enter White move: " << endl;
                        cin >> src;
                        cin >> dest;
                    }
                }
            }
        }
        else
        {
            //  cout << "Same dice values, player WHITE can do 4 moves." << endl;
            if (whiteCapturedPiece)
            {
                while (src != 25 && !possibleMove(src, dest))
                {
                    cerr << "Illegal move: Player still has captured piece(s) ." << endl;
                    cout << "Enter White move: " << endl;
                    cin >> src;
                    cin >> dest;
                }
                moveDisk(src, dest);
                whiteCapturedPieceNumber--;
                if (whiteCapturedPieceNumber == 0)
                {
                    whiteCapturedPiece = false;
                }
                if_dices_are_equals--;
            }
            for (int i = 0; i < if_dices_are_equals; i++)
            {
                cout << "Enter White move: " << endl;
                cin >> src;
                cin >> dest;
                if (!moveDisk(src, dest) && !cin)
                {
                    if (cin.eof())
                    {
                        cerr << "Missing user input - quiting game." << endl;
                        return false;
                    }
                    cout << "Enter White move: " << endl;
                    cin >> src;
                    cin >> dest;
                }
            }
        }
        flagSecondDice = flagFirstDice = false;
        if_dices_are_equals = 4;
        return true;
    }
    return true;
}
/*--------------------------------------------------*/
/*TO DELETE DISK FROM A GIVEN POSITION*/
void Board::deleteDisk(int Position)
{
    /*IN THIS FUNCTION IAM WORKING WITH 4 QUARTERS,2 HALFS*/
    if (turn == WHITE)
    {
        if (Position == 25)
        {
            for (int i = 0; i < MaxCulUp(); i++)
            {
                if (board[i + 1][6].getColor() == NONE && board[i][6].getColor() != NONE)
                {
                    board[i][6].setColor(NONE);
                }
            }
        }
        if (Position >= 19)
        {
            for (int i = 0; i < MaxCulUp(); ++i)
            {
                if (board[i + 1][13 - (24 - Position) - 1].getColor() == NONE)
                {
                    board[i][13 - (24 - Position) - 1].setColor(NONE);
                    return;
                    ;
                }
            }
        }
        if (Position >= 13)
        {
            for (int i = 0; i < MaxCulUp(); ++i)
            {
                if (board[i + 1][13 - (24 - Position + 1) - 1].getColor() == NONE)
                {
                    board[i][13 - (24 - Position + 1) - 1].setColor(NONE);
                    return;
                    ;
                }
            }
        }
        if (Position <= 6)
        {
            for (int k = 30 - MaxCulDown(); k < 30; ++k)
            {
                if (board[k - 1][12 - Position + 1].getColor() == NONE &&
                    board[k][12 - Position + 1].getColor() != NONE)
                {
                    board[k][12 - Position + 1].setColor(NONE);
                    return;
                    ;
                }
            }
        }
        if (Position < 13)
        {
            for (int k = 30 - MaxCulDown(); k < 30; ++k)
            {
                if (board[k - 1][12 - Position].getColor() == NONE &&
                    board[k][12 - Position].getColor() != NONE)
                {
                    board[k][12 - Position].setColor(NONE);
                    return;
                    ;
                }
            }
        }
    }
    if (turn == BLACK)
    {
        if (Position == 25)
        {
            for (int i = 29; i > 30 - MaxCulDown(); --i)
            {
                if (board[i][6].getColor() != NONE && board[i - 1][6].getColor() == NONE)
                {
                    board[i][6].setColor(NONE);
                }
            }
        }
        if (Position >= 19)
        {
            for (int k = 30 - MaxCulDown(); k < 30; ++k)
            {
                if (board[k - 1][13 - (24 - Position) - 1].getColor() == NONE &&
                    board[k][13 - (24 - Position) - 1].getColor() != NONE)
                {
                    board[k][13 - (24 - Position) - 1].setColor(NONE);
                    return;
                    ;
                }
            }
        }
        if (Position >= 13)
        {
            for (int j = 30 - MaxCulDown(); j < 30; ++j)
            {
                if (board[j - 1][12 - (24 - Position) - 1].getColor() == NONE &&
                    board[j][12 - (24 - Position) - 1].getColor() != NONE)
                {
                    board[j][12 - (24 - Position) - 1].setColor(NONE);
                    return;
                    ;
                }
            }
        }
        if (Position <= 6)
        {
            for (int i = 0; i < MaxCulUp(); ++i)
            {
                if (board[i + 1][12 - Position + 1].getColor() == NONE)
                {
                    board[i][12 - Position + 1].setColor(NONE);
                    return;
                    ;
                }
            }
        }
        if (Position < 13)
        {
            for (int i = 0; i < MaxCulUp(); ++i)
            {
                if (board[i + 1][12 - Position].getColor() == NONE)
                {
                    board[i][12 - Position].setColor(NONE);
                    return;
                    ;
                }
            }
        }
    }
}
/*--------------------------------------------------*/
/*TO ADD DISK TO A GIVEN POSITION*/
void Board::addDisk(int Position)
{
    /*IN THIS FUNCTION IAM WORKING WITH 4 QUARTERS,2 HALFS*/
    if (turn == BLACK)
    {
        if (Position == 25)
        {
            for (int j = 0; j < MaxCulUp(); ++j)
            {
                if (board[j][6].getColor() == NONE)
                {
                    board[j][6].setColor(WHITE);
                    return;
                }
            }
        }
        if (Position >= 19)
        {
            for (int j = 30 - MaxCulDown() - 1; j < 30; ++j)
            {
                if (board[j + 1][13 - (24 - Position) - 1].getColor() != NONE)
                {
                    board[j][13 - (24 - Position) - 1].setColor(BLACK);
                    return;
                }
            }
        }
        if (Position >= 13)
        {
            for (int j = 30 - MaxCulDown() - 1; j < 30; ++j)
            {
                if (board[j + 1][12 - (24 - Position) - 1].getColor() != NONE)
                {
                    board[j][12 - (24 - Position) - 1].setColor(BLACK);
                    return;
                }
            }
        }
        if (Position <= 6)
        {
            for (int i = 0; i < MaxCulUp() + 1; ++i)
            {
                if (board[i][13 - Position].getColor() == NONE)
                {
                    board[i][13 - Position].setColor(BLACK);
                    return;
                }
            }
        }
        if (Position < 13)
        {
            for (int i = 0; i < MaxCulUp() + 1; ++i)
            {
                if (board[i][12 - Position].getColor() == NONE)
                {
                    board[i][12 - Position].setColor(BLACK);
                    return;
                }
            }
        }
    }
    if (turn == WHITE)
    {
        if (Position == 25)
        {
            for (int j = 29; j < MaxCulDown(); --j)
            {
                if (board[j + 1][6].getColor() != NONE)
                {
                    board[j][6].setColor(BLACK);
                    return;
                }
            }
        }
        if (Position <= 6)
        {
            for (int i = 30 - MaxCulDown() - 1; i < 30; ++i)
            {
                if (board[i + 1][13 - Position].getColor() != NONE)
                {
                    board[i][13 - Position].setColor(WHITE);
                    return;
                }
            }
        }
        if (Position < 13)
        {
            for (int j = 30 - MaxCulDown() - 1; j < 30; ++j)
            {
                if (board[j + 1][12 - Position].getColor() != NONE)
                {
                    board[j][12 - Position].setColor(WHITE);
                    return;
                }
            }
        }
        if (Position >= 19)
        {
            for (int i = 0; i < MaxCulUp() + 1; ++i)
            {
                if (board[i][12 - (24 - Position)].getColor() == NONE)
                {
                    board[i][12 - (24 - Position)].setColor(WHITE);
                    return;
                }
            }
        }
        if (Position >= 13)
        {
            for (int i = 0; i < MaxCulUp(); ++i)
            {
                if (checkDiskColor(Position) == BLACK && checkDiskNumber(Position) == 1)
                {
                    deleteDisk(Position);
                }
                if (board[i][12 - (24 - Position) - 1].getColor() == NONE)
                {
                    board[i][12 - (24 - Position) - 1].setColor(WHITE);
                    return;
                }
                if (board[i + 1][12 - (24 - Position) - 1].getColor() == NONE)
                {
                    board[i + 1][12 - (24 - Position) - 1].setColor(WHITE);
                    return;
                }
            }
        }
    }
}
/*--------------------------------------------------*/
/*A FUNCTION TO CHECK THE DISK TYPE(BLACK/WHITE or NONE)*/
Color Board::checkDiskColor(int Position)
{
    /*IN THIS FUNCTION IAM WORKING WITH 4 QUARTERS,2 HALFS*/
    if (turn == WHITE)
    {
        if (Position == 25)
        {
            return board[0][6].getColor();
        }
        if (Position >= 19)
        {
            return board[0][12 - (24 - Position)].getColor();
        }
        if (Position >= 13)
        {
            return board[0][12 - (24 - Position) - 1].getColor();
        }
        if (Position <= 6)
        {
            return board[29][13 - Position].getColor();
        }
        if (Position < 13)
        {
            return board[29][12 - Position].getColor();
        }
    }
    if (turn == BLACK)
    {
        if (Position == 25)
        {
            return board[29][6].getColor();
        }
        if (Position >= 19)
        {
            return board[29][12 - (24 - Position)].getColor();
        }
        if (Position >= 13)
        {
            return board[29][12 - (24 - Position) - 1].getColor();
        }
        if (Position <= 6)
        {
            return board[0][13 - Position].getColor();
        }
        if (Position < 13)
        {
            return board[0][12 - Position].getColor();
        }
    }
    return NONE; /*TO AVOID WARNING*/
}
/*--------------------------------------------------*/
/*A FUNCTION TO CHECK DISKS NUMBER FOR THE GIVEN POSITION*/
int Board::checkDiskNumber(int Position)
{
    /*IN THIS FUNCTION IAM WORKING WITH 4 QUARTERS,2 HALFS*/
    int c = 0;
    if (turn == WHITE)
    {
        if (Position >= 19)
        {
            for (int i = 0; i < MaxCulUp(); ++i)
            {
                if (board[i][12 - (24 - Position)].getColor() != NONE)
                    c++;
            }
            return c;
        }
        if (Position >= 13)
        {
            for (int i = 0; i < MaxCulUp(); ++i)
            {
                if (board[i][12 - (24 - Position) - 1].getColor() != NONE)
                    c++;
            }
            return c;
        }
        if (Position <= 6)
        {
            for (int k = 30 - MaxCulDown(); k < 30; ++k)
            {
                if (board[k][13 - Position].getColor() != NONE)
                {
                    c++;
                }
            }
            return c;
        }
        if (Position < 13)
        {
            for (int k = 30 - MaxCulDown(); k < 30; ++k)
            {
                if (board[k][12 - Position].getColor() != NONE)
                {
                    c++;
                }
            }
            return c;
        }
    }
    if (turn == BLACK)
    {
        if (Position >= 19)
        {
            for (int k = 30 - MaxCulDown(); k < 30; ++k)
            {
                if (board[k][12 - (24 - Position)].getColor() != NONE)
                {
                    c++;
                }
            }
            return c;
        }
        if (Position >= 13)
        {
            for (int k = 30 - MaxCulDown(); k < 30; ++k)
            {
                if (board[k][12 - (24 - Position) - 1].getColor() != NONE)
                {
                    c++;
                }
            }
            return c;
        }
        if (Position <= 6)
        {
            for (int k = 0; k < MaxCulUp(); ++k)
            {
                if (board[k][13 - Position].getColor() != NONE)
                {
                    c++;
                }
            }
        }
        if (Position < 13)
        {
            for (int k = 0; k < MaxCulUp(); ++k)
            {
                if (board[k][12 - Position].getColor() != NONE)
                {
                    c++;
                }
            }
        }
    }
    return 0; /*TO AVOID WARNINGS*/
}
void Board::switchTurn()
{
    if (turn == WHITE)
    {
        turn = BLACK;
    }
    else if (turn == BLACK)
        turn = WHITE;
}
bool Board::playGame()
{
    while (winner == NONE && doMove())
    {
        // doMove();
        switchTurn();
        printBoard();
    }
    if (winner == WHITE)
    {
        cout << "WHITE player wins!" << endl;
    }
    else if (winner == BLACK)
    {
        cout << "BLACK player wins!" << endl;
    }

    return true;
}
/*PRRIIINNTTT PLZZZZZ*/
void Board::printBoard()
{
    if (turn == WHITE)
    {
        cout << "  13 14 15 16 17 18    19 20 21 22 23 24" << endl;
        cout << "+------------------+-+------------------+" << endl;
        for (int i = 0; i < MaxCulUp(); i++)
        {
            cout << "+";
            for (int j = 0; j < 13; j++)
            {
                if (j == 6)
                {
                    if (board[i][j].getColor() == WHITE)
                        cout << "+W+";
                    else if (board[i][j].getColor() == BLACK)
                        cout << "+B+";
                    else if (board[i][j].getColor() == NONE)
                        cout << "+ +";
                    continue;
                }
                if (board[i][j].getColor() == WHITE)
                    cout << " W ";
                else if (board[i][j].getColor() == BLACK)
                    cout << " B ";
                else if (board[i][j].getColor() == NONE)
                    cout << " | ";
            }
            cout << "+";
            cout << endl;
        }
        cout << "+                  + +                  +" << endl;
        for (int i = 30 - MaxCulDown(); i < 30; i++)
        {
            cout << "+";
            for (int j = 0; j < 13; j++)
            {
                if (j == 6)
                {
                    if (board[i][j].getColor() == WHITE)
                        cout << "+W+";
                    else if (board[i][j].getColor() == BLACK)
                        cout << "+B+";
                    else if (board[i][j].getColor() == NONE)
                        cout << "+ +";
                    continue;
                }

                if (board[i][j].getColor() == WHITE)
                    cout << " W ";
                else if (board[i][j].getColor() == BLACK)
                    cout << " B ";
                else if (board[i][j].getColor() == NONE)
                    cout << " | ";
            }
            cout << "+";

            cout << endl;
        }
        cout << "+------------------+-+------------------+" << endl;
        cout << "  12 11 10 9  8  7     6  5  4  3  2  1" << endl;
    }
    if (turn == BLACK)
    {
        {
            cout << "  12 11 10  9  8  7    6  5  4  3  2  1" << endl;
            cout << "+------------------+-+------------------+" << endl;
            for (int i = 0; i < MaxCulUp(); i++)
            {
                cout << "+";
                for (int j = 0; j < 13; j++)
                {
                    if (j == 6)
                    {
                        if (board[i][j].getColor() == WHITE)
                            cout << "+W+";
                        else if (board[i][j].getColor() == BLACK)
                            cout << "+B+";
                        else if (board[i][j].getColor() == NONE)
                            cout << "+ +";
                        continue;
                    }
                    if (board[i][j].getColor() == WHITE)

                        cout << " W ";
                    else if (board[i][j].getColor() == BLACK)
                        cout << " B ";
                    else if (board[i][j].getColor() == NONE)
                        cout << " | ";
                }
                cout << "+";

                cout << endl;
            }
            cout << "+                  + +                  +" << endl;
            for (int i = 30 - MaxCulDown(); i < 30; i++)
            {
                cout << "+";
                for (int j = 0; j < 13; j++)
                {
                    if (j == 6)
                    {
                        if (board[i][j].getColor() == WHITE)
                            cout << "+W+";
                        else if (board[i][j].getColor() == BLACK)
                            cout << "+B+";
                        else if (board[i][j].getColor() == NONE)
                            cout << "+ +";
                        continue;
                    }
                    if (board[i][j].getColor() == WHITE)

                        cout << " W ";
                    else if (board[i][j].getColor() == BLACK)
                        cout << " B ";
                    else if (board[i][j].getColor() == NONE)
                        cout << " | ";
                }
                cout << "+";

                cout << endl;
            }
            cout << "+------------------+-+------------------+" << endl;
            cout << " 13 14 15 16 17 18    19 20 21 22 23 24" << endl;
        }
    }
}
