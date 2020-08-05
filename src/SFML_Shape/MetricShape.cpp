#include "MetricShape.h"
using namespace sdaa;
MetricShape::MetricShape(Metric const& metric):sf::Drawable(), m_vertex(sf::Lines)
{
    m_width = metric.getWidth();
    m_height = metric.getHeight();
    m_squareSize = metric.getSquareSize();

    for(unsigned int line = 0; line< metric.getSize().line ; line++)
    {

        sf::Vertex vertexleft(sf::Vector2f(0,line*m_squareSize));
        sf::Vertex vertexright(sf::Vector2f(m_width,line*m_squareSize));
        m_vertex.append(vertexleft);
        m_vertex.append(vertexright);

    }
    for(unsigned int col = 0; col< metric.getSize().col ; col++)
    {


        sf::Vertex vertextop(sf::Vector2f(col*m_squareSize,0));
        sf::Vertex vertexbottom(sf::Vector2f(col*m_squareSize,m_height));
        m_vertex.append(vertextop);
        m_vertex.append(vertexbottom);
    }
    for(int line = 0; line < metric.getSize().line; line++)
    {
        m_occupy.push_back(std::vector<bool>{});
        for(int col = 0; col < metric.getSize().col; col++)
        {
            m_occupy[line].push_back(metric.getOccupy(line,col));
        }
    }
}

void MetricShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(int line = 0; line<m_occupy.size(); line++)
    {
        for(int col = 0; col  < m_occupy[0].size(); col++)
        {
           if(m_occupy[line][col])
           {
                sf::RectangleShape rect(sf::Vector2f(m_squareSize,m_squareSize));
                rect.setPosition(col*m_squareSize,line*m_squareSize);
                target.draw(rect);
           }
        }
    }
    target.draw(m_vertex,states);
}

void MetricShape::update(Metric const& metric)
{
    for(int line = 0; line < m_occupy.size() ; line++)
    {
        for(int col = 0; col <m_occupy[0].size() ; col++)
        {
            m_occupy[line][col] = metric.getOccupy(line,col);
        }
    }
}
