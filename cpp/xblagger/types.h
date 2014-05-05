#ifndef TYPES_H
#define TYPES_H

//ARROWCAR, BLAGGER, CANDY, CAR, CHINAMAN, DISC, EYES, HANDCAR, HATMAN,
//LONGARMS, PHONE, PRAM, SAFE, SKULL, TEETH
namespace Fonts {
  enum e {SMALL, LARGE};
}

namespace Layer {
  enum e {TILE, SPRITE, TEXT};
}

namespace Sprites {
  enum e {
    WALL = 0x1,
    KEY = 0x2,
    BUSH = 0x3,
    TRAVELATOR_LEFT = 0x4,
    TRAVELATOR_RIGHT = 0x5,
    CROSS = 0x6,
    SINKING_FLOOR = 0x7,
    BLAGGER = 0x8,
    METAL_FLOOR = 0x9,
    HANDCAR = 0xa
  };
}

namespace Direction {
  enum e {LEFT, RIGHT, UP, DOWN, STOP};
}

namespace Axis {
  enum e {HORIZONTAL, VERTICAL};
}

#endif
