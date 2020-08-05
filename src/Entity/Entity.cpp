#include "Entity.h"
#include <cmath>
#include <iostream>
using namespace sdaa;

/*-----------------------------------------------------------------------------------*/
/*------------------------------ public methods--------------------------------------*/
/*-----------------------------------------------------------------------------------*/


Entity::Entity(int line, int col,int squareSize,float velocity) : m_positionInMetric(line,col), m_offset(0,0), m_dest(line,col)
{
    if(velocity > 1)
        m_velocity=1;
    else if(velocity<0)
        m_velocity=0;
    else
        m_velocity = velocity;

    m_squareSize = squareSize;
    m_mode = Entity::WAIT;
    m_target = nullptr;
    m_metricID = -1;
    m_maxUpdateFollowCount = 50;
}

/*-----------------------------------------------------------------------------------*/
Entity::Entity(): m_positionInMetric(0,0), m_offset(0,0)
{
    m_velocity = 1;
    m_mode = Entity::WAIT;
    m_squareSize = 1;
    m_metricID = -1;
    m_maxUpdateFollowCount = 50;
}
/*-----------------------------------------------------------------------------------*/
Entity::Entity(int line,int col,int squareSize) : m_positionInMetric(line,col), m_offset(0,0)
{
    m_velocity = 1;
    m_mode == Entity::WAIT;
    m_squareSize = squareSize;
    m_metricID = -1;
    m_maxUpdateFollowCount = 50;
}
/*-----------------------------------------------------------------------------------*/
void Entity::updateEntityPosition()
{
    if(!m_path.empty())
    {
        if(m_mode == Entity::WAIT)
            m_mode = Entity::MOVE;
        VectInt dest = m_path[0];
        VectInt direction;
        direction.col = dest.col-m_positionInMetric.col;
        direction.line = dest.line-m_positionInMetric.line;
        if(direction.col !=0)
        {
            m_offset.x+= m_velocity*direction.col;
            if(abs(m_offset.x)>=1)
            {
                m_offset.x=0;
                m_positionInMetric.col = dest.col;
                m_path.erase(m_path.begin());
            }
        }
        else if(direction.line !=0)
        {
            m_offset.y+= m_velocity*direction.line;
            if(abs(m_offset.y)>=1)
            {
                m_offset.y=0;
                m_positionInMetric.line = dest.line;
                m_path.erase(m_path.begin());
            }
        }
    }
    else if(m_mode != Entity::FOLLOW)
        m_mode = Entity::WAIT;

}

/*-----------------------------------------------------------------------------------*/
void Entity::stop()
{
    if(m_path.size()>1)
        m_path.erase(m_path.begin()+1,m_path.end());
}
/*-----------------------------------------------------------------------------------*/
VectFloat Entity::getFullPosition() const
{
    VectFloat position;
    position.x = (m_positionInMetric.col + m_offset.x)*m_squareSize;
    position.y = (m_positionInMetric.line + m_offset.y)*m_squareSize;
    return position;
}
/*-----------------------------------------------------------------------------------*/
/*------------------------------ getters/setters ------------------------------------*/
/*-----------------------------------------------------------------------------------*/

void Entity::setPositionInMetric(int line, int col)
{
    m_positionInMetric.line = line;
    m_positionInMetric.col  = col;
}
/*-----------------------------------------------------------------------------------*/
VectInt Entity::getPositionInMetric() const
{
    return m_positionInMetric;
}
/*-----------------------------------------------------------------------------------*/
void Entity::setOffset(float dx, float dy)
{
    m_offset.x = dx;
    m_offset.y = dy;
}
/*-----------------------------------------------------------------------------------*/
VectFloat Entity::getOffset() const
{
    return m_offset;
}
/*-----------------------------------------------------------------------------------*/
Entity::Mode Entity::getMode() const
{
    return m_mode;
}
/*-----------------------------------------------------------------------------------*/
void Entity::setMode(Entity::Mode mode)
{
    m_mode = mode;
}
/*-----------------------------------------------------------------------------------*/
void Entity::setPath(std::vector<VectInt> const& path)
{
    m_path.clear();
    for(int i = 0; i< path.size(); i++)
    {
        m_path.push_back(path[i]);
    }
    if(!m_path.empty())
        m_dest = m_path[m_path.size()-1];
    else
        m_dest = m_positionInMetric;
}
/*-----------------------------------------------------------------------------------*/
void Entity::setPath(std::vector<VectInt> const& path,int begin)
{
    for(int i = begin; i< m_path.size(); i++)
    {
        m_path.pop_back();
    }
    for(int i =0; i<path.size(); i++)
    {
        m_path.push_back(path[i]);
    }
    if(!m_path.empty())
        m_dest = m_path[m_path.size()-1];
    else
        m_dest = m_positionInMetric;
}
/*-----------------------------------------------------------------------------------*/
void Entity::setPath(std::vector<VectInt> const& path, int begin, int pathSize)
{
    for(int i = begin; i< m_path.size(); i++)
    {
        m_path.pop_back();
    }

    if(pathSize> path.size())
        pathSize = path.size();

    for(int i = 0; i<pathSize; i++)
    {
        m_path.push_back(path[i]);
    }
    if(!m_path.empty())
        m_dest = m_path[m_path.size()-1];
    else
        m_dest = m_positionInMetric;
}
/*-----------------------------------------------------------------------------------*/
VectInt Entity::getPath(unsigned int i) const
{
    if(i<m_path.size())
        return m_path[i];
    else
        return m_positionInMetric;
}
/*-----------------------------------------------------------------------------------*/
void Entity::setVelocity(float velocity)
{
 if(velocity>1)
    m_velocity = 1;
 else if(velocity<0)
    m_velocity = 0;
 else
    m_velocity = velocity;
}
/*-----------------------------------------------------------------------------------*/
float Entity::getVelocity() const
{
    return m_velocity;
}

/*-----------------------------------------------------------------------------------*/
VectInt Entity::getDest() const
{
    return m_dest;
}
/*-----------------------------------------------------------------------------------*/
size_t Entity::getPathSize() const
{
    return m_path.size();
}
/*-----------------------------------------------------------------------------------*/

void Entity::setSquareSize(int squareSize)
{
    m_squareSize = squareSize;
}

/*-----------------------------------------------------------------------------------*/

int Entity::getSquareSize() const
{
    return m_squareSize;
}
/*-----------------------------------------------------------------------------------*/
void Entity::setDest(VectInt const& dest)
{
    m_dest = dest;
}
/*-----------------------------------------------------------------------------------*/

bool Entity::setTarget(Entity& entity)
{
    m_target = &entity;
    if(m_target == nullptr)
        return false;
    return true;
}
/*-----------------------------------------------------------------------------------*/
VectInt Entity::getTargetPosInMetric() const
{
    if(m_target == nullptr)
        return VectInt(-1,-1);
    else
    {
        return m_target->getPositionInMetric();
    }
}
/*-----------------------------------------------------------------------------------*/
void Entity::setMetricID(int id)
{
    m_metricID = id;
}
/*-----------------------------------------------------------------------------------*/
int Entity::getMetricID() const
{
    return m_metricID;
}
/*-----------------------------------------------------------------------------------*/
void Entity::setUpdateFollowCount(int i)
{
    m_updateFollowCount = i;
}
/*-----------------------------------------------------------------------------------*/
int Entity::getUpdateFollowCount() const
{
    return m_updateFollowCount;
}
/*-----------------------------------------------------------------------------------*/
Entity::Mode Entity::getTargetMode() const
{
    return m_target->getMode();
}
/*-----------------------------------------------------------------------------------*/
int Entity::getTargetMetricID() const
{
    return m_target->getMetricID();
}
/*-----------------------------------------------------------------------------------*/
int Entity::getMaxUpdateFollowCount() const
{
    return m_maxUpdateFollowCount;
}
/*-----------------------------------------------------------------------------------*/
void Entity::setMaxUpdateFollowCount(int i)
{
    m_maxUpdateFollowCount = i;
}
/*-----------------------------------------------------------------------------------*/
void Entity::stopToFollow(bool saveTarget)
{
    stop();
    m_mode = Entity::WAIT;
    if(!saveTarget)
        m_target = nullptr;
}

bool Entity::asATarget() const
{
    return !(m_target == nullptr);
}

VectFloat Entity::getTargetFullPosition() const
{
    return m_target->getFullPosition();
}
