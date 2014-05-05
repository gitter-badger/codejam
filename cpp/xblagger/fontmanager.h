#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <map>
#include <string>
#include "types.h"

struct SDL_Surface;

class FontManager
{
public:
  FontManager();
  ~FontManager();
  SDL_Surface * getText(const std::string & text, Fonts::e fontType);

private:
  void setFont();
  void setFont(Fonts::e fontType, char fromChar, char toChar, int x, int y, int w, int h, SDL_Surface * spriteSheet);

  typedef std::map<char, SDL_Surface *> Chars;
  std::map<Fonts::e, Chars> font;
};

#endif
