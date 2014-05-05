#include "xblagger.h"

#include <SDL/SDL.h>
#include <string>

int main(int argc, char * argv[])
{
  int scale = 1;
  
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
        printf("Usage: ./xblagger [OPTIONS]\n");
        printf("      --scale2x\n");
        printf("      --scale3x\n");
        printf("  -v, --version\n");
        printf("  -h, --help\n");
        return 0;
      } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
        printf("xblagger\n");
        printf("GNU 2012 Jostein Topland\n");
        return 0;
      } else if (strcmp(argv[i], "--scale2x") == 0) {
        scale = 2;
      } else if (strcmp(argv[i], "--scale3x") == 0) {
        scale = 3;
      }
    }
  }
  
  XBlagger * game = new XBlagger(scale);
  delete game;

  return 0;
}
