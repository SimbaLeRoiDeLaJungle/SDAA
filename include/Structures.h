#ifndef STRUCTURES_H
#define STRUCTURES_H
namespace sdaa{

/*-----------------------------------------------------------------------------------*/
struct VectInt
{
    int line;
    int col;
    VectInt(){}
    VectInt(int l, int c){line = l ; col = c;}
};
/*-----------------------------------------------------------------------------------*/
struct VectFloat
{
    float x;
    float y;
    VectFloat(){}
    VectFloat(float X, float Y){x= X; y= Y;}
};
/*-----------------------------------------------------------------------------------*/
struct Square
{
    float h;
    float g;
    float f;
    VectInt position;
    VectInt parentPosition;
    float parentG;
    Square(int l,int c){position.line=l;position.col=c;}
};
/*-----------------------------------------------------------------------------------*/

// for the priority queue.
struct CompareSquare{
    bool operator()(const Square *squareA, const Square *squareB)
    {
        return squareA->f > squareB->f;
    }

};

















}

#endif // STRUCTURES_H
