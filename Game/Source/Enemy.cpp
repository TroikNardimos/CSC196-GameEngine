#include "Enemy.h"
#include "Player.h"
#include "../../Engine/Source/Scene.h"
#include "../../Engine/Source/Colour.h"
#include <vector>
#include "Bullet.h"
#include <iostream>

void Enemy::Update(float dt)
{
	Player* player = m_scene->GetActor<Player>();

	m_fireTimer -= dt;
	if (player && m_fireTimer <= 0)
	{
		Vector2 direction = player->GetTransform().position - m_transform.position;
		m_velocity += direction.Normalized() * m_speed * dt;
		m_transform.rotation = direction.Angle();

		m_fireTimer = 1.0f;
		std::vector<Vector2> points;
		points.push_back(Vector2{ 3, 0 });
		points.push_back(Vector2{ -3, -3 });
		points.push_back(Vector2{ -3, 3 });
		points.push_back(Vector2{ 3, 0 });
		Model* model = new Model{ points, Colour{ 1, 1, 0 } };

		Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

		//Bullet* enemyBullet = new Bullet(200.0f, 10, transform, model);
		std::unique_ptr<Actor> enemyBullet(new Bullet(200.0f, 10, transform, model));
		enemyBullet->SetLifespan(1.0f);
		m_scene->AddActor(enemyBullet);

		if (false)
		{
			//player->TakeDamage(100);
			std::cout << "bullet hit" << std::endl;
		}
	}

	Actor::Update(dt);
}
