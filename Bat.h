#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat
{
private:
	Vector2f m_Position;

	// A RectangleShape object
	RectangleShape m_Shape;

	float m_Speed = 800.0f;

	bool m_MovingLeft = false;
	bool m_MovingRight = false;

public:
	Bat(float startX, float startY);

	FloatRect getPosition();

	RectangleShape getShape();

	void MoveLeft();

	void MoveRight();
	
	void StopLeft();

	void StopRight();

	void Update(Time dt);
};