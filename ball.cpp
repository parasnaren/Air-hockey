class Ball{

public:

	sf::CircleShape ball;

	int size;

	int x;

	int y;

	sf::Vector2f velocity;

	Ball(int size, int x, int y);

	void move();

	void collides();

};

Ball::Ball(int size, int x, int y){

	this->size = size;

	this->x = x;

	this->y = y;

	velocity.x = 10;

	velocity.y=-5;

	ball.setRadius(size);

	ball.setPosition(sf::Vector2f(x, y));

}

void Ball::move(){

	ball.move(velocity);

}

void Ball::collides(){

	if(ball.getPosition().y<=0 || ball.getPosition().y >=HEIGHT)

		velocity.y*=-1;
}
