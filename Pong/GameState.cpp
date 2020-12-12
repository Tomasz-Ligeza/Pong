#include "GameState.h"
#include <sstream>
#include <iomanip>
#include <charconv>

void GameState::updateTimer(const float& deltaTime)
{
	if (isActive) {
		timeElapsed += deltaTime;
		std::ostringstream oss;
		std::cout << std::setprecision(2) << deltaTime << "\n";
		oss << "Time elapsed: " << std::fixed << std::setprecision(1) << timeElapsed << "s";
		this->timeElapsedText->setString(oss.str());
	}

	//cpp17
}

void GameState::movePlayer()
{
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		if (playersBouncer.getPosition().y <= 0)
		{
			playersBouncer.setPosition({ playersBouncer.getPosition().x, 0.f });
		}
		else
			playersBouncer.move({ 0.f, -1.f });
	}
	else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		if (playersBouncer.getPosition().y + playersBouncer.getSize().y >= window->getSize().y)
		{
			playersBouncer.setPosition({ playersBouncer.getPosition().x, window->getSize().y - playersBouncer.getSize().y });
		}
		else
			playersBouncer.move({ 0.f, 1.f });
	}
}

void GameState::moveComputer()
{
	if (computersBouncer.getPosition().y + 0.5f * computersBouncer.getSize().y < ball.getPosition().y)
	{
		if (computersBouncer.getPosition().y + computersBouncer.getSize().y >= window->getSize().y)
		{
			computersBouncer.setPosition({ computersBouncer.getPosition().x, window->getSize().y - computersBouncer.getSize().y });
		}
		
		else
			computersBouncer.move({ 0.f, 1.f });
	}
	else if (computersBouncer.getPosition().y + 0.5f * computersBouncer.getSize().y > ball.getPosition().y)
	{
		if (computersBouncer.getPosition().y <= 0)
		{
			computersBouncer.setPosition({ computersBouncer.getPosition().x, 0.f });
		}
		else
			computersBouncer.move({ 0.f, -1.f });
	}
}

void GameState::ballCollide()
{
	//with bouncers collisions
	if (ball.getPosition().x < playersBouncer.getSize().x)
	{
		//collisions with player
		if (ball.getPosition().y + ball.getRadius() > playersBouncer.getPosition().y && ball.getPosition().y + ball.getRadius() < playersBouncer.getPosition().y + playersBouncer.getSize().y)
		{
			ballDirection = { -ballDirection.x , ballDirection.y };
		}
		else
		{
			//player lost
			isActive = false;
			ball.setSpeed(0.f);
		}
	}
	else if (ball.getPosition().x + 2.f * ball.getRadius() > window->getSize().x - computersBouncer.getSize().x)
	{
		//collisions with computer
		if (ball.getPosition().y + ball.getRadius() > computersBouncer.getPosition().y && ball.getPosition().y + ball.getRadius() < computersBouncer.getPosition().y + computersBouncer.getSize().y)
		{
			ballDirection = { -ballDirection.x , ballDirection.y };
		}
		else
		{
			//computerLost
			isActive = false;
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

void GameState::initializeMusic()
{
	if (!buffer.loadFromFile("sounds/drop.wav"))
	{
		std::cout << "couldnt load sound\n";
		return;
	}
	music->setBuffer(buffer);
	music->setLoop(false);
	music->play();
	if (!nextBuffer.loadFromFile("sounds/game_st.wav"))
	{
		std::cout << "couldnt load sound\n";
	}
}

void GameState::initializeText()
{
	timeElapsedText = new Text();
	this->timeElapsedText->setString("Time elapsed: 0.00s");
	this->timeElapsedText->setFont(*font);
	this->timeElapsedText->setCharacterSize(18);
	this->timeElapsedText->setPosition(this->window->getSize().x / 6, this->window->getSize().y / 25);
	drawables.push_back(timeElapsedText);
}

void GameState::initializeBouncersPosition()
{
	float speed = 10.f;
	playersBouncer = Bouncer({ 0.f, window->getSize().y / 2.f }, { 10.f, 150.f }, Color::White, speed);
	computersBouncer = Bouncer({ window->getSize().x - 10.f, window->getSize().y / 2.f }, { 10.f, 150.f }, Color::Red, speed);
	ball = Ball({ window->getSize().x / 2.f, window->getSize().y / 2.f }, 30.f, Color::Cyan, speed / 2.f);
	ballDirection = { -1.f, 1.f };
}

void GameState::resetMusic()
{
	if (music->getStatus() == SoundSource::Status::Stopped)
	{
		music->setBuffer(nextBuffer);
		music->setLoop(true);
		music->play();
	}
}

GameState::GameState(sf::RenderWindow* window, Event* event, std::stack<State*>* states, Sound* music, Font* font)
	: State(window, event, states, music)
{
	this->font = font;
	timeElapsed = 0.0f;
	initializeMusic();
	initializeBouncersPosition();
	initializeText();
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
		switch (this->event->type)
		{
		case Event::Closed:
		{
			this->window->close();
			break;
		}
		case Event::KeyPressed:
		{
			if (this->event->key.code == Keyboard::Escape)
				this->quit = true;
			break;
		}
		}
	}
}

void GameState::update(const float& deltaTime)
{
	this->checkForQuit();
	this->resetMusic();

	updateTimer(deltaTime);
	movePlayer();
	moveComputer();
	ballCollide();
	ball.move(ballDirection);
}

void GameState::render(sf::RenderTarget* target)
{
	window->draw(playersBouncer);
	window->draw(computersBouncer);
	window->draw(ball);

	for (Drawable* x : drawables) {
		window->draw(*x);
	}
}
