#pragma once
#include "MathUtils.h"
#include <cmath>
#include <stdint.h>

struct Colour
{
	float r;
	float g;
	float b;
	float a;

	Colour() = default;
	Colour(float r, float g, float b, float a = 0)
	{ this->r = r; this->g = g;  this->b = b;  this->a = a; }

	float operator [] (unsigned int index) const { return (&r)[index]; }
	float& operator [] (unsigned int index) { return (&r)[index]; }

	Colour operator + (const Colour& c) const { return Colour{ r + c.r, g + c.g, b + c.b, a + c.a }; }
	Colour operator - (const Colour& c) const { return Colour{ r - c.r, g - c.g, b - c.b, a - c.a }; }
	Colour operator * (const Colour& c) const { return Colour{ r * c.r, g * c.g, b * c.b, a * c.a }; }
	Colour operator / (const Colour& c) const { return Colour{ r / c.r, g / c.g, b / c.b, a / c.a }; }

	//Colour operator + (float s) const { return Colour{ x + s, y + s }; }
	//Colour operator - (float s) const { return Colour{ x - s, y - s }; }
	//Colour operator * (float s) const { return Colour{ x * s, y * s }; }
	//Colour operator / (float s) const { return Colour{ x / s, y / s }; }

	//Colour& operator += (const Colour& v) { x += v.x; y += v.y; return *this; }
	//Colour& operator -= (const Colour& v) { x -= v.x; y -= v.y; return *this; }
	//Colour& operator *= (const Colour& v) { x *= v.x; y *= v.y; return *this; }
	//Colour& operator /= (const Colour& v) { x /= v.x; y /= v.y; return *this; }

	//Colour& operator += (float s) { x += s; y += s; return *this; }
	//Colour& operator -= (float s) { x -= s; y -= s; return *this; }
	//Colour& operator *= (float s) { x *= s; y *= s; return *this; }
	//Colour& operator /= (float s) { x /= s; y /= s; return *this; }

	static uint8_t ToInt(float value) { return static_cast<uint8_t>(Math::Clamp(value, 0.0f, 1.0f) * 255); }
};