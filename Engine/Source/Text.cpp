#include "Text.h"
#include <iostream>

Text::~Text()
{
    if (m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
    }
}

bool Text::Create(Renderer& renderer, const std::string& text, const Colour& colour)
{
    // creates a surface using the font, text, and colour
    SDL_Color c{ Colour::ToInt(colour.r), Colour::ToInt(colour.g), Colour::ToInt(colour.b), Colour::ToInt(colour.a) };
    SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), c);

    if (surface == nullptr)
    {
        std::cerr << "Could not create surface.\n";
        return false;
    }

    // creates a texture from the surface, only textures can render to the renderer
    m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
    if (surface == nullptr)
    {
        SDL_FreeSurface(surface);
        std::cerr << "Could not create surface.\n";
        return false;
    }

    //free suface, as its no longer needed after creating texture
    SDL_FreeSurface(surface);
    return true;
}

void Text::Draw(Renderer& renderer, int x, int y)
{
    //query the texture for width and height
    int width, height;
    SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);

    //copies the texture onto renderer
    SDL_Rect rect{ x, y, width, height };
    SDL_RenderCopy(renderer.m_renderer, m_texture, NULL, &rect);
}
