#ifndef ENTITYSPRITE_H
#define ENTITYSPRITE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
namespace sdaa{

class EntitySprite : public Entity, public sf::Drawable
{
    public:
        EntitySprite(int line, int col,int squareSize,float velocity);
        bool setTexture(sf::Texture const& texture);
        void setTextureRect(sf::FloatRect const& rect);
        void updatePosition();

    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        sf::VertexArray m_vertices;
        const sf::Texture* m_texture;
};

}

#endif // ENTITYSPRITE_H
