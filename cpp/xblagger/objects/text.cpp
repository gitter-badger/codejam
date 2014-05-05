#include "text.h"

#include "../fontmanager.h"
#include <SDL/SDL.h>
#include "object.h"

Text::Text(int x, int y, const std::string & text, Fonts::e fontType, FontManager * fontManager) : Object(x, y), fontManager(fontManager)
{
  this->setText(text, fontType);
}

void Text::setText(const std::string & text, Fonts::e fontType)
{
  this->sprites.push_back(this->fontManager->getText(text, fontType));
}
