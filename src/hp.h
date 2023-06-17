//
// Created by Reza Bagheri on 6/9/23.
//

#ifndef HOPPER_PROBLEM_HP_H
#define HOPPER_PROBLEM_HP_H

#define FURTHER 0
#define CLOSER 1


#include <random>
#include <vector>
#include <tuple>

namespace hp {
  int getDirection(unsigned int distance);

  double calcMovementProbability(unsigned int direction, unsigned int distance);

  std::tuple<long, long> calcMovementProbabilityFrac(unsigned int direction, unsigned int distance);

  std::tuple<long, long> solveForPathProbability(std::vector<int> path);

  bool solveForProbabilities(std::string inputFile, std::string outputFile);

  std::vector<int> getPathFromString(std::string pathString);

  std::tuple<long, long> simplifyFraction(std::tuple<long, long> fraction);

  std::vector<std::vector<int>> pathToMatrix(std::vector<int> path);

  std::string pathToString(std::vector<int> path);

  void printMatrix(const std::vector<std::vector<int>> &matrix);
}


#endif //HOPPER_PROBLEM_HP_H
