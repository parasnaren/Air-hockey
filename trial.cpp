#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <sstream>

int WIDTH = 400, HEIGHT = 500;
int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Air Hockey");
    sf::CircleShape ball;
    ball.setRadius(10);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		window.clear();
		window.draw(ball);
        window.display();
    }
    return 0;
}
