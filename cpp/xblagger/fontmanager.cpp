#include "fontmanager.h"

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <string>
#include "xblagger.h"

FontManager::FontManager()
{
  SDL_Surface * image = SDL_LoadBMP("sprites.bmp");
  SDL_Surface * spriteSheet = zoomSurface(image, XBlagger::scale, XBlagger::scale, SMOOTHING_OFF);
  SDL_FreeSurface(image);
  
  this->setFont(Fonts::SMALL, 'a', 'z', 8, 63, 8, 8, spriteSheet);
  this->setFont(Fonts::SMALL, '0', '9', 144, 71, 8, 8, spriteSheet);
  this->setFont(Fonts::LARGE, '0', '0', 224, 71, 16, 8, spriteSheet);
  this->setFont(Fonts::LARGE, '1', '9', 0, 79, 16, 8, spriteSheet);
  SDL_FreeSurface(spriteSheet);
}

FontManager::~FontManager()
{
  std::map<Fonts::e, Chars>::const_iterator it;
  for (it = font.begin(); it != font.end(); it++) {
    Chars::const_iterator it2;
    for (it2 = it->second.begin(); it2 != it->second.end(); it2++)
      SDL_FreeSurface(it2->second);
  }
}

SDL_Surface *
FontManager::getText(const std::string & text, Fonts::e fontType)
{
  int defaultWidth = 8;

  int bboxWidth = 0;
  for (unsigned i = 0; i < text.length(); i++) {
    char c = text.at(i);
    if (this->font[fontType].count(c) == 0) {
      bboxWidth += defaultWidth;
      continue;
    }

    bboxWidth += this->font[fontType][c]->w;
  }
  int bboxHeight = this->font[fontType].begin()->second->h;
  
  SDL_Surface * textSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, bboxWidth, bboxHeight, 32, 0, 0, 0, 0);

  for (unsigned int i = 0, x = 0; i < text.length(); i++) {
    char c = text.at(i);
    if (this->font[fontType].count(c) == 0) {
      x += defaultWidth;
      continue;
    }

    SDL_Surface * charSurface = this->font[fontType][c];
    SDL_Rect pos = {x};
    SDL_BlitSurface(charSurface, NULL, textSurface, &pos);
    x += charSurface->w;
  }

  SDL_SetColorKey(textSurface, SDL_SRCCOLORKEY, 0xff00ff);

  return textSurface;
}

void
FontManager::setFont(Fonts::e fontType, char fromChar, char toChar, int x, int y, int w, int h, SDL_Surface * spriteSheet)
{
  x *= XBlagger::scale;
  y *= XBlagger::scale;
  w *= XBlagger::scale;
  h *= XBlagger::scale;
  
  int numChars = toChar - fromChar;
  for (int i = 0; i <= numChars; i++) {
    char c = fromChar + i;
    int x2 = i * w + x;

    SDL_Surface * charSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
    SDL_Rect rect = {x2, y, w, h};
    SDL_BlitSurface(spriteSheet, &rect, charSurface, NULL);
    this->font[fontType][c] = charSurface;
  }
}
