#include "GameState.h"

void GameState::movePlayer()
{
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		if (player.getPosition().y <= 0)
		{
			player.setPosition({ player.getPosition().x, 0.f });
		}
		else
			player.move({ 0.f, -1.f });
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		if (player.getPosition().y + player.getSize().y >= window->getSize().y)
		{
			player.setPosition({ player.getPosition().x, window->getSize().y - player.getSize().y });
		}
		else
			player.move({ 0.f, 1.f });
	}
}

void GameState::moveComputer()
{
	if (computer.getPosition().y + 0.5f * computer.getSize().y < ball.getPosition().y)
	{
		if (computer.getPosition().y + computer.getSize().y >= window->getSize().y)
		{
			computer.setPosition({ computer.getPosition().x, window->getSize().y - computer.getSize().y });
		}
		
		else
			computer.move({ 0.f, 1.f });
	}
	else if (computer.getPosition().y + 0.5f * computer.getSize().y > ball.getPosition().y)
	{
		if (computer.getPosition().y <= 0)
		{
			computer.setPosition({ computer.getPosition().x, 0.f });
		}
		else
			computer.move({ 0.f, -1.f });
	}
}

void GameState::ballCollide()
{
	//with bouncers collisions
	if (ball.getPosition().x < player.getSize().x)
	{
		//collisions with player
		if (ball.getPosition().y + ball.getRadius() > player.getPosition().y && ball.getPosition().y + ball.getRadius() < player.getPosition().y + player.getSize().y)
		{
			ballDirection = { -ballDirection.x , ballDirection.y };
		}
		else
		{
			//player lost
			ball.setSpeed(0.f);
		}
	}
	else if (ball.getPosition().x + 2.f * ball.getRadius() > window->getSize().x - computer.getSize().x)
	{
		//collisions with computer
		if (ball.getPosition().y + ball.getRadius() > computer.getPosition().y && ball.getPosition().y + ball.getRadius() < computer.getPosition().y + computer.getSize().y)
		{
			ballDirection = { -ballDirection.x , ballDirection.y };
		}
		else
		{
			//computerLost
			ball.setSpeed(0.f);
		}
	}
	
	//collisions with walls
	if (ball.getPosition().y < 0.f)
	{
		ballDirection = { ballDirection.x , -ballDirection.y };
	}
	else if (ball.getPosition().y > window->getSize().y - 2.f * ball.getRadius())
	{
		ballDirection = { ballDirection.x, -ballDirection.y };
	}
}

GameState::GameState(sf::RenderWindow* window, Event* event, std::stack<State*>* states) 
	: State(window, event, states)
{
	float speed = 10.f;
	player = Bouncer({ 0.f, window->getSize().y / 2.f }, { 10.f, 150.f }, Color::White, speed);
	computer = Bouncer({ window->getSize().x - 10.f, window->getSize().y / 2.f }, { 10.f, 150.f }, Color::Red, speed);
	ball = Ball({ window->getSize().x / 2.f, window->getSize().y / 2.f }, 30.f, Color::Cyan, speed / 2.f);
	ballDirection = { -1.f, 1.f };
}

GameState::~GameState()
{

}

void GameState::endState()
{
	std::cout << "getting out of gameState\n";
}

void GameState::pollEvents()
{
	while (this->window->pollEvent(*event))
	{
		if (this->event->type == Event::KeyPressed)
		{
			if (this->event->key.code == Keyboard::Escape)
				this->quit = true;
		}
	}
}

void GameState::update(const float& deltaTime)
{
	this->checkForQuit();
	movePlayer();
	moveComputer();
	ballCollide();
	ball.move(ballDirection);
}

void GameState::render(sf::RenderTarget* target)
{
	window->draw(player);
	window->draw(computer);
	window->draw(ball);
}
