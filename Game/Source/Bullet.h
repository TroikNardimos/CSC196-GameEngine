#pragma once
#include "../../Engine/Source/Actor.h"

class Bullet : public Actor
{
public:
	Bullet() = default;
	Bullet(const Transform& transform) : Actor{ transform } {}
	Bullet(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}
	Bullet(float speed, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{ speed }
	{}
	Bullet(float speed, float damage, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_damage{ damage }
	{}

	void Update(float dt);

	float GetDamage() { return m_damage; }

	virtual void OnCollision(Actor* actor);
private:
	float m_speed = 0;
	float m_damage = 0;

};