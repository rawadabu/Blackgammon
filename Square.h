#ifndef SQUARE_H_
#define SQUARE_H_
#include <iostream>

enum Color /*[0,1,2]*/
{
    WHITE,
    BLACK,
    NONE
};

class Square /*EACH INDEX IN BOARD HAVE SQUARE*/
{
private:
    Color color;

public:
    Square();
    void setColor(Color Setcolor)
    {
        color = Setcolor;
    }
    Color getColor()
    {
        return color;
    }
};

#endif // !SQUARE_H_
