#pragma once
#include "Font.h"
#include "Colour.h"
#include "Renderer.h"

class Text
{
public: 
	Text() = default;
	Text(Font* font) : m_font{ font } {}
	~Text();

	bool Create(Renderer& renderer, const std::string& text, const Colour& colour);
	void Draw(Renderer& renderer, int x, int y);

protected:
	Font* m_font{ nullptr };
	SDL_Texture* m_texture{ nullptr };
};