#pragma once
#include <string>
#include <SDL_ttf.h>

class Font
{
	friend class Text;
public:
	Font() = default;
	~Font();

	bool Load(const std::string& name, int fontsize);

protected:
	_TTF_Font* m_ttfFont{ nullptr };
};