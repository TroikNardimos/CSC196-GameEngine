#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "../../Engine/Source/Engine.h"
#include <iostream>

void Bullet::Update(float dt)
{
	m_velocity = Vector2{ 1, 0 }.Rotate(m_transform.rotation)* m_speed;
	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());
	Actor::Update(dt);
}

void Bullet::OnCollision(Actor* actor)
{
	if (actor != nullptr && (dynamic_cast<Player*>(actor) || dynamic_cast<Enemy*>(actor)) && actor->GetTag() != GetTag())
	{
		m_destroyed = true;
	}
}
