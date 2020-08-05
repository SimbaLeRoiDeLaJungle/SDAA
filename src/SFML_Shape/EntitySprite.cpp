#include "EntitySprite.h"

using namespace sdaa;

EntitySprite::EntitySprite(int line, int col, int squareSize, float velocity) : Entity(line,col,squareSize,velocity), m_vertices(sf::Quads, 4)
{
    m_vertices[0].position = sf::Vector2f(col*squareSize,line*squareSize);
    m_vertices[1].position = sf::Vector2f((col+1)*squareSize,line*squareSize);
    m_vertices[2].position = sf::Vector2f((col+1)*squareSize,(line+1)*squareSize);
    m_vertices[3].position = sf::Vector2f(col*squareSize,(line+1)*squareSize);
    m_texture = nullptr;
}

void EntitySprite::updatePosition()
{
    updateEntityPosition();

    VectFloat pos = getFullPosition();
    int s = getSquareSize();
    m_vertices[0].position = sf::Vector2f(pos.x,pos.y);
    m_vertices[1].position = sf::Vector2f(pos.x+s,pos.y);
    m_vertices[2].position = sf::Vector2f(pos.x+s,pos.y+s);
    m_vertices[3].position = sf::Vector2f(pos.x,pos.y+s);
}

bool EntitySprite::setTexture(sf::Texture const& texture)
{
    m_texture = nullptr;
    m_texture = &texture;
    if(m_texture == nullptr)
        return false;
    else
        return true;

}

void EntitySprite::setTextureRect(sf::FloatRect const& rect)
{
    m_vertices[0].texCoords = sf::Vector2f(rect.left,rect.top);
    m_vertices[1].texCoords = sf::Vector2f(rect.left+rect.width,rect.top);
    m_vertices[2].texCoords = sf::Vector2f(rect.left+rect.width,rect.top+rect.height);
    m_vertices[3].texCoords = sf::Vector2f(rect.left,rect.top+rect.height);
}

void EntitySprite::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    if(m_texture)
        states.texture = m_texture;
    target.draw(m_vertices,states);
}
