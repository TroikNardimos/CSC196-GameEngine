#include "Player.h"
#include "Enemy.h"
#include "../../Engine/Source/Engine.h"
#include "../../Engine/Source/Scene.h"
#include "Bullet.h"
#include <iostream>

void Player::Update(float dt)
{
	float thrust = 0;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_UP) || g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = m_speed;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN) || g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT) || g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) m_transform.rotation -= Math::DegToRad(100) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT) || g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) m_transform.rotation += Math::DegToRad(100) * dt;

	Vector2 acceleration = Vector2{ 1.0f, 0.0f }.Rotate(m_transform.rotation)* thrust;
	m_velocity += acceleration * dt;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	m_fireTimer -= dt;
	if (g_engine.GetInput().GetMouseButtonDown(0) && m_fireTimer <= 0)
	{
		m_fireTimer = 0.2f;
		std::vector<Vector2> points;
		points.push_back(Vector2{ 5, 0 });
		points.push_back(Vector2{ -5, -5 });
		points.push_back(Vector2{ -5, 5 });
		points.push_back(Vector2{ 5, 0 });
		Model* model = new Model{ points, Colour{ 1, 1, 0 } };

		Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

		auto bullet1 = std::make_unique<Bullet>(400, 25, transform, model);
		bullet1->SetLifespan(1);
		bullet1->SetTag("Player");
		m_scene->AddActor(std::move(bullet1));
		g_engine.GetAudio().PlaySound("laser.wav");
	}
	if (g_engine.GetInput().GetMouseButtonDown(2) && m_fireTimer <= 0)
	{
		m_fireTimer = 3.0f;
		std::vector<Vector2> points;
		points.push_back(Vector2{ 10, 0 });
		points.push_back(Vector2{ -10, -10 });
		points.push_back(Vector2{ -10, 10 });
		points.push_back(Vector2{ 10, 0 });
		Model* model = new Model{ points, Colour{ 1, 0.5f, 0 } };

		Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

		auto bullet2 = std::make_unique<Bullet>(100, 100, transform, model);
		bullet2->SetLifespan(1);
		bullet2->SetTag("Player");
		m_scene->AddActor(std::move(bullet2));
		g_engine.GetAudio().PlaySound("rocket.wav");
	}

	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	if ((dynamic_cast<Bullet*>(actor)) && actor->GetTag() != GetTag())
	{
		m_health -= dynamic_cast<Bullet*>(actor)->GetDamage();
		if (m_health <= 0)
		{
			if (m_lives <= 1)
			{
				m_destroyed = true;
				
				g_engine.GetAudio().PlaySound("ship-death.wav");
			}
			m_lives -= 1;
			m_health = 100;
		}
	}
}
