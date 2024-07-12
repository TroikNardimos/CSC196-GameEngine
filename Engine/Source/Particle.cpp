#include "Particle.h"

void Particle::Update(float dt)
{
	if (lifespan != 0)
	{
		lifespan -= dt;
	}
	position = position + (velocity * dt);
}

void Particle::Draw(Renderer& renderer)
{
	if (lifespan > 0)
	{
		renderer.DrawRect(position.x, position.y, 4.0f, 4.0f);
	}
}
