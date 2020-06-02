#include <iostream>

#include "Game.h"

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    std::cerr << "Cantidad de parametros incorrecta" << std::endl;
    return 1;
  }
  Game game(argv[1]);
  if (!game.isValid()) {return 1;}
  if (game.add_resources(argv[2]) < 0) {return 1;}

  game.run();
  game.printStats();

  return 0;
}
