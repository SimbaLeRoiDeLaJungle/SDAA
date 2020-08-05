#include "Metric.h"
#include <cmath>
#include <iostream>
using namespace sdaa;


/*-----------------------------------------------------------------------------------*/
/*----------------------------- public methods--------------------------------------*/
/*-----------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------*/

std::vector<VectInt> Metric::pathfinding(VectInt const& start, VectInt const& dest)
{
    std::priority_queue<Square*,std::vector<Square*>,CompareSquare> openList;
    std::vector<VectInt> empty;
    if(m_occupy[dest.line][dest.col])
    {
//        std::cout<< " case occuper" <<std::endl;
        return empty;

    }
    if(dest.col == start.col && start.line== dest.line)
    {
//        std::cout<< " meme case" <<std::endl;
        return empty;
    }
    m_squares[start.line][start.col].parentPosition.line = -1;
    m_squares[start.line][start.col].parentPosition.col = -1;
    m_squares[start.line][start.col].g = CalculG(m_squares[start.line][start.col]);
    m_squares[start.line][start.col].h = CalculH(m_squares[start.line][start.col],dest);
    m_squares[start.line][start.col].f = m_squares[start.line][start.col].g + m_squares[start.line][start.col].h;

    float h = m_squares[start.line][start.line].h;
    VectInt currentPos = start;

    while(h!=0)
    {

        std::vector<VectInt> nearSquarePos = getNearSquare(currentPos.line,currentPos.col);
        for(int i = 0; i < nearSquarePos.size(); i++)
        {

            int line = nearSquarePos[i].line;
            int col = nearSquarePos[i].col;
            if(!m_open[line][col] && !m_close[line][col] && !m_occupy[line][col])
            {
                m_squares[line][col].parentPosition.line = m_squares[currentPos.line][currentPos.col].position.line;
                m_squares[line][col].parentPosition.col = m_squares[currentPos.line][currentPos.col].position.col;
                m_squares[line][col].parentG = m_squares[currentPos.line][currentPos.col].g;
                m_squares[line][col].g = CalculG(m_squares[line][col]);
                m_squares[line][col].h = CalculH(m_squares[line][col],dest);
                m_squares[line][col].f = m_squares[line][col].g + m_squares[line][col].h;
                m_open[line][col] = true;
                openList.push(&m_squares[line][col]);
            }
            else if(m_open[line][col])
            {
                float CWOPG = CalculGWithOldParent(m_squares[line][col]);
                if(CWOPG<m_squares[line][col].g)
                {
                    m_squares[line][col].g =CWOPG;
                }
            }
        }
        if(openList.empty())
        {
//            std::cout<<"Pas de chemin" << std::endl;
            resetOpenAndClose();
            return empty;
        }
        m_open[currentPos.line][currentPos.col]=false;
        m_close[currentPos.line][currentPos.col]=true;
        Square *square = openList.top();
        currentPos.line = square->position.line;
        currentPos.col = square->position.col;
        h= m_squares[currentPos.line][currentPos.col].h;
        openList.pop();
    }

    std::vector<VectInt> reverseWay;
    reverseWay.push_back(currentPos);
    while(m_squares[currentPos.line][currentPos.col].parentPosition.line != -1)
    {
        int line = m_squares[currentPos.line][currentPos.col].parentPosition.line;
        int col = m_squares[currentPos.line][currentPos.col].parentPosition.col;
        currentPos.line = line;
        currentPos.col = col;
        reverseWay.push_back(currentPos);
    }
    resetOpenAndClose();
    std::vector<VectInt> way;
    for(int i = reverseWay.size()-2; i >=0 ; i--)
    {
        way.push_back(reverseWay[i]);
    }
    return way;
}

/*-----------------------------------------------------------------------------------*/
std::vector<VectInt> Metric::pathfinding(VectInt const& start, VectInt const& dest,float maxDistance)
{
//
}

/*-----------------------------------------------------------------------------------*/

std::vector<VectInt> Metric::pathfinding(VectInt const& start, std::vector<VectInt> const& dests)
{
//
}
/*-----------------------------------------------------------------------------------*/
/*----------------------------- static methods --------------------------------------*/
/*-----------------------------------------------------------------------------------*/

void Metric::initSquare(Square& square)
{
    square.f = FLT_MAX;
    square.g = FLT_MAX;
    square.h = FLT_MAX;
    square.parentG = -1;
    square.parentPosition.line = -1;
    square.parentPosition.col = -1;
}

/*-----------------------------------------------------------------------------------*/
/*----------------------------- private methods--------------------------------------*/
/*-----------------------------------------------------------------------------------*/

std::vector<VectInt> Metric::getNearSquare(int line, int col) const
{

    std::vector<VectInt> nearSquare;
    if(line-1>=0)
        nearSquare.push_back(VectInt(line-1,col));
    if(line+1< getSize().line)
        nearSquare.push_back(VectInt(line+1,col));
    if(col-1>=0)
        nearSquare.push_back(VectInt(line,col-1));
    if(col+1< getSize().col)
        nearSquare.push_back(VectInt(line,col+1));
    return nearSquare;
}

/*-----------------------------------------------------------------------------------*/

int Metric::CalculH(Square const& square,VectInt dest) const
{
    int H = abs(square.position.col-dest.col)*m_squareSize;
    int Q = abs(square.position.line-dest.line)*m_squareSize;
    return H+Q;
}

/*-----------------------------------------------------------------------------------*/

float Metric::CalculG(Square const& square) const
{
    float tempG;
    if(square.parentPosition.col == -1)
        return 0;

    tempG = square.parentG + m_squareSize * sqrt(2);
    return tempG;
}

/*-----------------------------------------------------------------------------------*/
float Metric::CalculGWithOldParent(Square const& square) const
{
    int line = square.position.line;
    int col = square.position.col;
    int pLine = m_squares[line][col].parentPosition.line;
    int pCol = m_squares[line][col].parentPosition.col;
    if(pLine ==-1)
        return FLT_MAX;

    int opLine = m_squares[pLine][pCol].parentPosition.line;
    int opCol = m_squares[pLine][pCol].parentPosition.col;

    if(opCol == -1)
        return FLT_MAX;

    float opG = m_squares[opLine][opCol].g;

    if(line != opLine && col != opCol)
        return opG + m_squareSize*sqrt(2);
    else
        return opG +m_squareSize;


}
/*-----------------------------------------------------------------------------------*/
void Metric::resetOpenAndClose()
{
    for(int line = 0; line < m_open.size(); line++)
    {
        for(int col = 0; col < m_open[0].size(); col++)
        {
            m_open[line][col]= false;
            m_close[line][col]= false;
            initSquare(m_squares[line][col]);
        }
    }
}
