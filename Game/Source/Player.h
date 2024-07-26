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
	Player(float speed, float health, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_health{ health }
	{}

	void Update(float dt);
	int GetScore() { return m_score; }
	int GetLives() { return m_lives; }
	void AddScore(int score) { m_score += score; }

	virtual void OnCollision(Actor* actor);

private:
	float m_speed = 0;
	float m_fireTimer = 0;
	float m_health = 100;
	int m_score = 0;
	int m_lives = 3;

};