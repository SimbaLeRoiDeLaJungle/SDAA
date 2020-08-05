#include "Metric.h"
#include <iostream>
#include <cmath>
using namespace sdaa;
/*-----------------------------------------------------------------------------------*/
/*----------------------------- public methods--------------------------------------*/
/*-----------------------------------------------------------------------------------*/

Metric::Metric(int width,int height,int squareSize)
{
    m_width = width;
    m_height = height;
    m_squareSize = squareSize;
    for(unsigned int line = 0; line< m_height/m_squareSize ; line++)
    {
        std::vector<bool> tempClose;
        std::vector<bool> tempOccupy;
        m_squares.push_back(std::vector<Square>{});
        for(unsigned int col = 0; col< m_width/m_squareSize ; col++)
        {
            Square square(line,col);
            Metric::initSquare(square);
            m_squares[line].push_back(square);
            tempClose.push_back(false);
            tempOccupy.push_back(false);
        }
        m_close.push_back(tempClose);
        m_open.push_back(tempClose);
        m_occupy.push_back(tempOccupy);
    }
    m_changeOccupyTrue = false;
    m_changeOccupyFalse = false;
}


/*-----------------------------------------------------------------------------------*/
void Metric::dynamicPathControl(bool BOTH)
{
    if(isOccupyChange(BOTH))
    {
        for(int i = 0 ; i< m_entities.size(); i++)
        {
            Entity* entity = m_entities[i];
            if(BOTH)
                entity->setMode(Entity::REQUESTPATH);
            else
            {
                bool b=true;
                for(int j = 0 ; j< entity->getPathSize() && b; j++)
                {

                    VectInt p=entity->getPath(j);
                    bool beChange = m_occupy[p.line][p.col] ;
                    if(beChange)
                    {
                        entity->setMode(Entity::REQUESTPATH);
                        b= false;
                    }
                }
            }
        }
        endPathControl();
    }
    for(int i = 0 ; i< m_entities.size(); i++)
    {
        if(m_entities[i]->getMode()==Entity::REQUESTPATH)
        {
            VectInt dest = m_entities[i]->getDest();
            m_entities[i]->setMode(Entity::MOVE);
            setPath(*m_entities[i],dest);

        }
        if(m_entities[i]->getMode() == Entity::FOLLOW)
        {
            int ufc = m_entities[i]->getUpdateFollowCount();
            if(ufc>m_entities[i]->getMaxUpdateFollowCount())
            {
                VectInt targetPos = m_entities[i]->getTargetPosInMetric();
                setPath(*m_entities[i],targetPos);
                m_entities[i]->setUpdateFollowCount(0);
            }
            else
            {
                m_entities[i]->setUpdateFollowCount(ufc+1);
            }
        }
     }

}

/*-----------------------------------------------------------------------------------*/

void Metric::setPath(Entity& entity, VectInt dest)
{
    std::vector<VectInt> path;
    VectInt start = entity.getPositionInMetric();
    if(entity.getMode() == Entity::WAIT)
    {
        VectInt start = entity.getPositionInMetric();
        path = pathfinding(start,dest);
        entity.setPath(path);
    }
    else if(entity.getMode() == Entity::MOVE)
    {
        VectInt start = entity.getPath(0);
        path = pathfinding(start,dest);
        entity.stop();
        entity.setPath(path,1);
    }
    else if(entity.getMode() == Entity::FOLLOW)
    {
        VectInt star;
        if(entity.getPathSize()>0)
            start = entity.getPath(0);
        else
            start = entity.getPositionInMetric();
        path = pathfinding(start,dest);
        if(!path.empty())
            path.erase(path.end());
        entity.stop();
        entity.setPath(path,1);
    }
}
/*-----------------------------------------------------------------------------------*/

void Metric::setPath(Entity& entity, VectInt dest,float maxDistance)
{
    std::vector<VectInt> path;
    VectInt start = entity.getPositionInMetric();
    if(entity.getMode() == Entity::WAIT)
    {
        VectInt start = entity.getPositionInMetric();
        path = pathfinding(start,dest,maxDistance);
        entity.setPath(path);
    }
    else if(entity.getMode() == Entity::MOVE)
    {
        VectInt start = entity.getPath(0);
        path = pathfinding(start,dest,maxDistance);
        entity.stop();
        entity.setPath(path,1);
    }
}
/*-----------------------------------------------------------------------------------*/
// not use yet
void Metric::setPath(Entity& entity, std::vector<VectInt> dests)
{
    std::vector<VectInt> path;
    VectInt start = entity.getPositionInMetric();
    if(entity.getMode() == Entity::WAIT)
    {
        VectInt start = entity.getPositionInMetric();
        path = pathfinding(start,dests);
        entity.setPath(path);
    }
    else if(entity.getMode() == Entity::MOVE)
    {
        VectInt start = entity.getPath(0);
        path = pathfinding(start,dests);
        entity.stop();
        entity.setPath(path,1);
    }
}

/*-----------------------------------------------------------------------------------*/
float Metric::distance(Entity const& entityA, Entity const& entityB) const
{
    VectFloat posA = entityA.getFullPosition();
    VectFloat posB = entityB.getFullPosition();
    float deltaX = posA.x-posB.x ;
    float deltaY = posA.y-posB.y ;
    return sqrt(pow(deltaX,2)+pow(deltaY,2));
}

/*-----------------------------------------------------------------------------------*/
float Metric::distance(Entity const& entity,VectFloat pos) const
{
    VectFloat posEntity = entity.getFullPosition();
    float deltaX = posEntity.x-pos.x ;
    float deltaY = posEntity.y-pos.y ;
    return sqrt(pow(deltaX,2)+pow(deltaY,2));
}
/*-----------------------------------------------------------------------------------*/
float Metric::distance(VectFloat posA,VectFloat posB) const
{
    float deltaX = posA.x-posB.x ;
    float deltaY = posA.y-posB.y ;
    return sqrt(pow(deltaX,2)+pow(deltaY,2));
}
/*-----------------------------------------------------------------------------------*/
float Metric::distance(VectInt posA,VectInt posB) const
{
    float deltaX = posA.col-posB.col ;
    float deltaY = posA.line-posB.line ;
    return sqrt(pow(deltaX,2)+pow(deltaY,2));
}
/*-----------------------------------------------------------------------------------*/
bool Metric::isIn(int line, int col) const
{
    return (line>=0 && line<m_occupy.size() && col>=0 && col<m_occupy[0].size());
}


/*-----------------------------------------------------------------------------------*/
/*-----------------------------getters/setters--------------------------------------*/
/*-----------------------------------------------------------------------------------*/

int Metric::getWidth() const
{
    return m_width;
}

/*-----------------------------------------------------------------------------------*/

void Metric::setOccupy(int line, int col, bool B)
{
    m_occupy[line][col] = B;
    if(B)
        m_changeOccupyTrue = true;
    else
        m_changeOccupyFalse = true;
}

/*-----------------------------------------------------------------------------------*/

int Metric::getHeight() const
{
    return m_height;
}

/*-----------------------------------------------------------------------------------*/

int Metric::getSquareSize() const
{
    return m_squareSize;
}

/*-----------------------------------------------------------------------------------*/

bool Metric::getOccupy(int line, int col) const
{
    return m_occupy[line][col];
}
/*-----------------------------------------------------------------------------------*/

bool Metric::isOccupyChange(bool BOTH) const
{
    if(BOTH)
        return (m_changeOccupyTrue || m_changeOccupyFalse);
    else
        return m_changeOccupyTrue;
}
/*-----------------------------------------------------------------------------------*/
void Metric::endPathControl()
{
    m_changeOccupyTrue = false;
    m_changeOccupyFalse = false;
}
/*-----------------------------------------------------------------------------------*/
VectInt Metric::getSize() const
{
    int line = m_occupy.size();
    int col = m_occupy[0].size();
    return VectInt(line,col);

}
/*-----------------------------------------------------------------------------------*/

bool Metric::addEntity(Entity& entity)
{
    m_entities.push_back(nullptr);
    m_entities[m_entities.size()-1] = &entity;
    if(m_entities[m_entities.size()-1]==nullptr)
        return false;
    else
    {
        int id = m_entities.size()-1;
        entity.setMetricID(id);
        return true;
    }
}
/*-----------------------------------------------------------------------------------*/

void Metric:: deleteEntity(Entity& entity)
{
    int id = entity.getMetricID();
    entity.setMetricID(-1);
    m_entities.erase(m_entities.begin()+id);
    for(int i = 0 ; i < m_entities.size(); i++)
    {
        m_entities[i]->setMetricID(i);
    }
}

/*-----------------------------------------------------------------------------------*/

void Metric::follow(Entity& entityA, Entity& entityB)
{
    entityA.setTarget(entityB);
    entityA.setMode(Entity::FOLLOW);
    int ufc = entityA.getUpdateFollowCount()+1;
    entityA.setUpdateFollowCount(ufc);
}

