#include "Font.h"
#include <iostream>

Font::~Font()
{
    if (m_ttfFont != nullptr)
    {
        TTF_CloseFont(m_ttfFont);
    }
}

bool Font::Load(const std::string& name, int fontsize)
{
    m_ttfFont = TTF_OpenFont(name.c_str(), fontsize);
    if (m_ttfFont == nullptr)
    {
        std::cerr << "Could not load font: " << name << std::endl;
    }
    return true;
}
