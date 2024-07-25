#include "Player.h"
#include "../../Engine/Source/Engine.h"
#include "../../Engine/Source/Scene.h"
#include "Bullet.h"
#include "Enemy.h"

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
	if (g_engine.GetInput().GetMouseButtonDown(0) && m_fireTimer <= 0) // && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		m_fireTimer = 0.2f;
		std::vector<Vector2> points;
		points.push_back(Vector2{ 5, 0 });
		points.push_back(Vector2{ -5, -5 });
		points.push_back(Vector2{ -5, 5 });
		points.push_back(Vector2{ 5, 0 });
		Model* model = new Model{ points, Colour{ 1, 1, 0 } };

		Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

		std::unique_ptr<Actor> playerBullet1(new Bullet(100.0f, 10, transform, model));
		playerBullet1->SetLifespan(1);
		m_scene->AddActor(playerBullet1);
		AddScore(100);
		//g_engine.GetAudio().PlaySound("");
	}
	if (g_engine.GetInput().GetMouseButtonDown(2) && m_fireTimer <= 0) // && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		m_fireTimer = 5.0f;
		std::vector<Vector2> points;
		points.push_back(Vector2{ 10, 0 });
		points.push_back(Vector2{ -10, -10 });
		points.push_back(Vector2{ -10, 10 });
		points.push_back(Vector2{ 10, 0 });
		Model* model = new Model{ points, Colour{ 1, 0.5f, 0 } };

		Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

		std::unique_ptr<Actor> playerBullet2(new Bullet(100.0f, 100, transform, model));
		playerBullet2->SetLifespan(1);
		m_scene->AddActor(playerBullet2);
		AddScore(100);
		//g_engine.GetAudio().PlaySound("");
	}
	if (m_destroyed == true)
	{
		m_lives -= m_lives;
		if (m_lives <= 0)
		{
			return;
		}
		m_destroyed = false;
	}

	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{

}
