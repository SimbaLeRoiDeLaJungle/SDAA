#include <SFML/Graphics.hpp>
#include "SDAA.h"
#include "SFML_Shape/MetricShape.h"
#include "SFML_Shape/EntitySprite.h"

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");
    app.setFramerateLimit(50);
    int squareSize =10;
    sdaa::Metric metric(800,600,squareSize);
    sdaa::MetricShape metricShape(metric);
    sf::Mouse mouse;
    std::vector<sdaa::EntitySprite> entities;

    entities.push_back(sdaa::EntitySprite(0,0,squareSize,0.1));
    entities.push_back(sdaa::EntitySprite(20,30,squareSize,0.1));
    entities.push_back(sdaa::EntitySprite(10,10,squareSize,0.1));

    for(int i = 0; i< entities.size(); i++)
        metric.addEntity(entities[i]);
    int entitySelected =-1;

    metric.follow(entities[0],entities[1]);
    metric.follow(entities[1],entities[2]);
	// Start the game loop
    while (app.isOpen())
    {

        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        sf::Vector2i mousePos = mouse.getPosition(app);
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::O)
                {
                    int line = mousePos.y/ squareSize;
                    int col = mousePos.x/ squareSize;
                    if(metric.isIn(line,col))
                    {
                        metric.setOccupy(line,col,true);
                    }
                }
                if(event.key.code == sf::Keyboard::Space)
                {
                    entities[0].stopToFollow();
                    entities[1].stopToFollow();
                }
                if(event.key.code == sf::Keyboard::M)
                {
                    metric.follow(entities[0],entities[1]);
                    metric.follow(entities[1],entities[2]);
                }
            }
        }
        if(mouse.isButtonPressed(sf::Mouse::Right))
        {
            int line = mousePos.y/ squareSize;
            int col = mousePos.x/ squareSize;
            if(entitySelected !=-1 && metric.isIn(line,col))
                metric.setPath(entities[entitySelected],sdaa::VectInt(line,col));
        }
        if(mouse.isButtonPressed(sf::Mouse::Left))
        {
            int line = mousePos.y/ squareSize;
            int col = mousePos.x/ squareSize;
            int temp = -1;
            for(int i = 0; i< entities.size(); i++)
            {
                sdaa::VectInt entityPos = entities[i].getPositionInMetric();
                if(entityPos.line == line && entityPos.col == col)
                {
                    temp = i;
                }
            }
            entitySelected = temp;

        }
        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        for(int i = 0; i < entities.size() ; i++)
            entities[i].updatePosition();


        metricShape.update(metric);


        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////

        metric.dynamicPathControl();

        //////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////
        app.clear();
        for(int i = 0 ; i<entities.size(); i++)
        {
            app.draw(entities[i]);
        }
        app.draw(metricShape);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
