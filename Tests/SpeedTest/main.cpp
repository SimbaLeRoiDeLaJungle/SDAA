#include <SFML/Graphics.hpp>
#include "Astars.h"
#include "SFML_Shape/MetricShape.h"
#include <iostream>
#include <queue>

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 590), "SFML window");
    int squareSize = 10;
    Astars::Metric metric(2000,2000,squareSize);
    Astars::MetricShape metricShape(metric);
    sf::Clock clock;
    sf::Mouse mouse;
    Astars::VectInt start(0,0);
    Astars::VectInt dest(55,45);
	std::vector<Astars::VectInt> path;

    // Start the game loop
    while (app.isOpen())
    {
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
                    int line = mousePos.y / squareSize;
                    int col = mousePos.x / squareSize;
                    if(metric.isIn(line,col))
                        metric.setOccupy(line,col,true);
                }
                if(event.key.code == sf::Keyboard::Space)
                {
                    path.clear();
                    clock.restart();
                    path = metric.pathfinding(start,dest);
                    std::cout<<clock.getElapsedTime().asMilliseconds()<<std::endl;
                }
            }

        }

        metricShape.update(metric);
        // Clear screen
        app.clear();
        for(int i = 0; i< path.size(); i++)
        {
            sf::Vector2f pos(path[i].col*squareSize,path[i].line*squareSize);
            sf::RectangleShape rect(sf::Vector2f(squareSize,squareSize));
            rect.setPosition(pos);
            rect.setFillColor(sf::Color::Blue);
            app.draw(rect);
        }

        sf::RectangleShape shape1(sf::Vector2f(squareSize,squareSize));
        shape1.setPosition(start.col*squareSize,start.line*squareSize);
        app.draw(shape1);
        sf::RectangleShape shape2(sf::Vector2f(squareSize,squareSize));
        shape2.setPosition(dest.col*squareSize,dest.line*squareSize);
        app.draw(shape2);

        app.draw(metricShape);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
