#ifndef XBLAGGER_H
#define XBLAGGER_H

class Scene;

class XBlagger
{
public:
  XBlagger(int scale = 1);
  ~XBlagger();

  static int width;
  static int height;
  static int scale;

private:
  Scene * scene;
};

#endif
