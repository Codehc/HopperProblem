#include "hp.h"
#include <iostream>

int main() {

  hp::solveForProbabilities("res/paths/possible_paths.txt", "res/paths/probabilities.txt");

  std::vector<int> path = {1, 1, -1, -1};
  hp::printMatrix(hp::pathToMatrix(path));

  std::cout << hp::pathToString(path) << std::endl;

  return 0;
}
