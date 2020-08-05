#ifndef METRICSHAPE_H
#define METRICSHAPE_H

#include <SFML/Graphics.hpp>
#include "Metric.h"
namespace sdaa{
class MetricShape : public sf::Drawable
{
    public:
        MetricShape(Metric const& metric);
        void update(Metric const& metric);
    protected:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::VertexArray m_vertex;
        int m_squareSize;
        int m_width;
        int m_height;
        std::vector<std::vector<bool>> m_occupy;
};
}
#endif // METRICSHAPE_H
