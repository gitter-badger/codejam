#ifndef EVENT_H
#define EVENT_H

#include "types.h"

class Blagger;

class Event
{
public:
  void processEvents();

  bool * run;
  Blagger * blagger;
};

#endif
