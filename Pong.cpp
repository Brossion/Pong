#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>


int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game

	RenderWindow window(vm, "Pong", Style::Fullscreen);


	int score = 0;
	int lives = 3;

	bool isDead = false;

	// Create a bat
	Bat bat(1920 / 2, 1080 - 20);

	// We will add a ball in the next chapter
	Ball ball(1920 / 2, 0);

	// Create a Text object called HUD
	Text hud;

	// A cool retro-style font
	Font font;
	font.loadFromFile("fonts/DS-DIGI.ttf");

	// Set the font to our retro-style
	hud.setFont(font);

	// Make it nice and big
	hud.setCharacterSize(75);

	// Choose a color
	hud.setFillColor(Color::White);

	hud.setPosition(20, 20);

	// Here is our clock for timing everything
	Clock clock;

	while (window.isOpen())
	{
		/*
		Handle the player input
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// Quit the game when the window is closed
				window.close();

		}

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle the pressing and releasing of the arrow keys
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.MoveLeft();
		}
		else
		{
			bat.StopLeft();
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.MoveRight();
		}
		else
		{
			bat.StopRight();
		}

		/*
		Update the bat, the ball and the HUD
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/
		// Update the delta time
		Time dt = clock.restart();
		bat.Update(dt);
		ball.Update(dt);
		// Update the HUD text
		std::stringstream ss;
		ss << "Score:" << score << "    Lives:" << lives;
		hud.setString(ss.str());


		// Handle ball hitting the bottom
		if (ball.getPosition().top > window.getSize().y)
		{
			// reverse the ball direction
			ball.reboundBottom();

			// Remove a life
			lives--;

			isDead = true;

			ball.resetSpeed();

			// Check for zero lives
			if (lives < 1) {
				// reset the score
				score = 0;
				// reset the lives
				lives = 3;
			}

		}

		// Handle ball hitting top
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatOrTop();

			// Add a point to the players score
			if (!isDead)
			{
				score++;
			}
		}

		// Handle ball hitting sides
		if (ball.getPosition().left - 20 < 0 ||
			ball.getPosition().left + 20 > window.getSize().x)
		{
			ball.reboundSides();
		}

		// Has the ball hit the bat?
		if (ball.getPosition().intersects(bat.getPosition()))
		{
			// Hit detected so reverse the ball and score a point
			ball.reboundBatOrTop();

			ball.increaseSpeed();

			if (isDead)
			{
				isDead = false;
			}
		}
		/*
		Draw the bat, the ball and the HUD
		*********************************************************************
		*********************************************************************
		*********************************************************************
		*/
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();
	}

	return 0;
}

