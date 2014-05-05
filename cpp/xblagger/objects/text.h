#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "object.h"

class FontManager;

class Text : public Object
{
public:
  Text(int x, int y, const std::string & text, Fonts::e fontType, FontManager * fontManager);
  void setText(const std::string & text, Fonts::e fontType);

private:
  FontManager * fontManager;
};

#endif
