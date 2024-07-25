#pragma once
#include "Vector2.h"
#include "Colour.h"
#include "Renderer.h"
#include "Transform.h"

#include <vector>

// * - pointer -> nullptr
// & - reference -> 

class Model
{
public:
	Model() = default;
	Model( const std::vector<Vector2>& points, const Colour& colour) :
		m_points{ points },
		m_colour{ colour }
	{}

	void Draw(Renderer& renderer, const Vector2& position, float angle, float scale);
	void Draw(Renderer& renderer, Transform& transform);

	float GetRadius();

private:
	std::vector<Vector2> m_points;
	Colour m_colour;
};