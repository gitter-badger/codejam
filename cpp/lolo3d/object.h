#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "object3d.h"

class Object : public Object3D
{
public:
    Object(int x, int y, const string & filename, const string & animation = "idle") : Object3D(filename)
    {
        position.x = float(x);
        position.y = float(y);
        setAnimation(animation);
    }
};

class Tux : public Object
{
public:
    Tux(int x, int y) : Object(x, y, "data/tux.obj") {}
};

class Gol : public Object
{
public:
    Gol(int x, int y) : Object(x, y, "data/gol.obj") {}
};

class Rock : public Object
{
public:
    Rock(int x, int y) : Object(x, y, "data/rock.obj") {}
};

class Tree : public Object
{
public:
    Tree(int x, int y) : Object(x, y, "data/tree.obj") {}
};

#endif
