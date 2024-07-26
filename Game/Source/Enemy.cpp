#include "Enemy.h"
#include "Player.h"
#include "../../Engine/Source/Scene.h"
#include "../../Engine/Source/Engine.h"
#include <iostream>
#include "Bullet.h"



void Enemy::Update(float dt)
{
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		Vector2 direction = player->GetTransform().position - m_transform.position;
		m_velocity += direction.Normalized() * m_speed * dt;
		m_transform.rotation = direction.Angle();

		m_fireTimer -= dt;
		if (m_fireTimer <= 0)
		{
			m_fireTimer = 1.0f;
			std::vector<Vector2> points;
			points.push_back(Vector2{ 3, 0 });
			points.push_back(Vector2{ -3, -3 });
			points.push_back(Vector2{ -3, 3 });
			points.push_back(Vector2{ 3, 0 });
			Model* model = new Model{ points, Colour{ 1, 1, 0 } };

			Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

			auto bullet = std::make_unique<Bullet>(200, 10, transform, model);
			bullet->SetLifespan(1);
			bullet->SetTag("Enemy");
			m_scene->AddActor(std::move(bullet));
			g_engine.GetAudio().PlaySound("laser.wav");
		}
	}

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* actor)
{
	Player* player = m_scene->GetActor<Player>();
	if ((dynamic_cast<Bullet*>(actor)) && actor->GetTag() != GetTag())
	{
		m_health -= dynamic_cast<Bullet*>(actor)->GetDamage();
		if (m_health <= 0)
		{
			m_destroyed = true;
			g_engine.GetAudio().PlaySound("ship-death.wav");
			player->AddScore(100);
		}
	}
}
