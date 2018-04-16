#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include<cstdlib>
#define FRAMERATE 60

using namespace std;
const int VELOCITY = 10; // movement of the pads
const int WIDTH = 800;
const int HEIGHT = 600;
int score1 = 0;
int score2 = 0;
//----------------------BALL-------------------
class Ball
{
public:
	sf::CircleShape ball;
	int size;
	int x;
	int y;
	sf::Vector2f velocity;
	Ball(int size, int x, int y);
	void moveBall();
	void collidesWall();
};
Ball::Ball(int size, int x, int y)
{
	this->size = size;
	this->x = x;
	this->y = y;
	velocity.x = 10;
	velocity.y = -5;
	ball.setRadius(size);
	ball.setPosition(sf::Vector2f(x, y));
}
void Ball::moveBall()// Making ball move
{
	ball.move(velocity);
}
void Ball::collidesWall()// Ball colliding with the edges
{
	if(ball.getPosition().y <= 0 || ball.getPosition().y >= HEIGHT-10)

		velocity.y *= -1;
}
//-----------------PADDLE----------------------
class Paddle
{
public:
	sf::RectangleShape body;
	int height;
	int width;
	int x;
	int y;
	int player;
	Paddle(int height, int width, int x, int y , int player)
    {
		this->height = height;
		this->width = width;
		this->x = x;
		this->y = y;
		this->player = player;
		body.setPosition(this->x, this->y);
		body.setSize(sf::Vector2f(this->width, this->height));
    }
	void input();
};

void Paddle::input()
{
		if(player == 1)
        {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
					cout<< body.getPosition().y  <<endl;

			if(body.getPosition().y > 0)
				body.move(sf::Vector2f(0,-VELOCITY));
            }

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
					cout<<body.getPosition().y <<endl;

			if(body.getPosition().y + body.getSize().y < HEIGHT)
                body.move(sf::Vector2f(0,VELOCITY));
			}
		}

		if(player == 2)
        {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
					cout<< body.getPosition().y  <<endl;

			if(body.getPosition().y > 0)
                body.move(sf::Vector2f(0,-VELOCITY));
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
					cout << body.getPosition().y <<endl;

			if(body.getPosition().y+body.getSize().y < HEIGHT)
                body.move(sf::Vector2f(0,VELOCITY));
			}

		}
}

void collision(Paddle& pad, Ball& puck)
{
	if(puck.ball.getPosition().x <= pad.body.getPosition().x + pad.body.getSize().x &&
		puck.ball.getPosition().x >= pad.body.getPosition().x && puck.ball.getPosition().y <= pad.body.getPosition().y +  pad.body.getSize().y &&
		puck.ball.getPosition().y >= pad.body.getPosition().y)
        {

		puck.velocity.x *= -1;

        if(puck.ball.getPosition().y < pad.body.getPosition().y + pad.body.getSize().y/3)
			puck.velocity.y = -4;

		if(puck.ball.getPosition().y > pad.body.getPosition().y + pad.body.getSize().y - pad.body.getSize().y/3)
            puck.velocity.y = 4;
        }
}

bool score(Ball& puck)
{
	if(puck.ball.getPosition().x > WIDTH)
    {
		score1 +=1;
		return true;
	}
	if(puck.ball.getPosition().x < 0)
	{
        score2+=1;
		return true;
	}
	return false;
}

string to_string(int val)
{
    ostringstream str1;
    str1 << val;
    string conv = str1.str();
    return conv;
}

void reset(Ball& puck, sf::Text& text)
{
	puck.ball.setPosition(WIDTH/2 + 5, HEIGHT/2 + 5);
	puck.velocity.x = 0;
	puck.velocity.y = 0;
	text.setString(to_string(score1) + " | " + to_string(score2));
}

void start(Ball& puck) // ball at initial position
{
	if(puck.velocity.x == 0 && puck.velocity.y == 0)
    {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
			puck.velocity.x = 10;

			if(score2 >score1)
				puck.velocity.x *= -1;

			puck.velocity.y = rand()%5;
		}
    }
}

//------------------------MAIN----------------------------
int main()
{
	int score1=0;
	int score2=0;
	sf::Text Scores;
	sf::Font font;
	font.loadFromFile("arial.ttf");

	Scores.setFont(font);
    Scores.setString(to_string(score1) + " | " + to_string(score2));
	Scores.setCharacterSize(30);
	Scores.setPosition(WIDTH/2 - 30, 50);
	Scores.setStyle(sf::Text::Bold);

    Paddle paddle = Paddle(100, 10, 20, HEIGHT/2, 1 );
	Paddle paddle2 = Paddle(100, 10, WIDTH-30, HEIGHT/2, 2);
	Ball puck = Ball(7, WIDTH/2 + 5, HEIGHT/2 + 5);
	puck.velocity.x = 0;
	puck.velocity.y = 0;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Air Hockey");
	window.setFramerateLimit(FRAMERATE);
    while (window.isOpen())
    {
		start(puck);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		window.clear();
		paddle.input();
		paddle2.input();
		puck.collidesWall();
		collision(paddle, puck);
		collision(paddle2, puck);
		puck.moveBall();

		if(score(puck))
			reset(puck, Scores);

        window.draw(paddle.body);
		window.draw(paddle2.body);
		window.draw(puck.ball);
		window.draw(Scores);
        window.display();
    }
    return 0;
}
