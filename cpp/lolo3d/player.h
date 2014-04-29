#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "object3d.h"

class Player : public Object3D
{
public:
    Player(int x, int y, const string & filename, const string & animation = "idle") : Object3D(filename)
    {
        position.x = float(x);
        position.y = float(y);
        setAnimation(animation);
    }
};

class Tux : public Player
{
public:
    Tux(int x, int y) : Player(x, y, "data/tux.obj") {}
};

class Gol : public Player
{
public:
    Gol(int x, int y) : Player(x, y, "data/gol.obj") {}
};

class Rock : public Player
{
public:
    Rock(int x, int y) : Player(x, y, "data/rock.obj") {}
};

class Tree : public Player
{
public:
    Tree(int x, int y) : Player(x, y, "data/tree.obj") {}
};

#endif