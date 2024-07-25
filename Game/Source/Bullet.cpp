#include "Bullet.h"
#include "../../Engine/Source/Engine.h"
//#include "../../Engine/Source/Scene.h"
#include "Player.h"
#include "Enemy.h"

void Bullet::Update(float dt)
{
	//Particle::Data data
	//{
	//	m_transform.position,
	//		Vector2{ 1, 0 }.Rotate(randomf(Math::TwoPi)) * 50,
	//		randomf(0.5f, 2.0f),
	//		255,255,255,255
	//};
	//g_engine.GetPS().AddParticle(data);

	m_velocity = Vector2{ 1, 0 }.Rotate(m_transform.rotation)* m_speed;
	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	Actor::Update(dt);
}

void Bullet::OnCollision(Actor* actor)
{
	if ((dynamic_cast<Player*>(actor) || dynamic_cast<Enemy*>(actor)) && actor->GetTag() != GetTag())
	{
		m_destroyed = true;
	}
}
