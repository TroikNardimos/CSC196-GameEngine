#pragma once
#include "../../Engine/Source/Actor.h"

class Player : public Actor
{
public: 
	Player() = default;
	Player(const Transform& transform) : Actor{ transform } {}
	Player(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}
	Player(float speed, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{ speed }
	{}

	void Update(float dt);
	float GetScore() { return m_score; }
	void AddScore(int score) { m_score += score; }

	virtual void OnCollision(Actor* actor);

private:
	float m_speed = 0;
	float m_fireTimer = 0;
	int m_score = 0;
	int m_lives = 3;

};