//
// Created by Reza Bagheri on 6/9/23.
//

#include <cmath>
#include <iostream>
#include <random>

#include "hp.h"
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>

int hp::getDirection(unsigned int distance) {
  if (distance == 0) {
    return FURTHER;
  }

  std::random_device rd;
  std::mt19937 engine(rd());
  std::uniform_real_distribution<double> dist(0, 1);
  double randomNum = dist(engine);

  double threshold = pow(2.0, distance);
  threshold = (threshold) / (1 + threshold);
  // 1 is closer, 0 is away
  return randomNum <= threshold;
}

double hp::calcMovementProbability(unsigned int direction, unsigned int distance) {
  if (direction == 1) {
    return pow(2.0, distance) / (1 + pow(2.0, distance));
  } else if (direction == -1) {
    return 1 / (1 + pow(2.0, distance));
  } else {
    return 0;
  }
}

std::tuple<long, long> hp::calcMovementProbabilityFrac(unsigned int direction, unsigned int distance) {
  if (direction == 1) {
    return std::make_tuple(pow(2ll, distance), (1ll + pow(2ll, distance)));
  } else if (direction == -1) {
    return std::make_tuple(1ll, (1ll + pow(2ll, distance)));
  } else {
    return std::make_tuple(0ll, 1ll);
  }
}

std::tuple<long, long> hp::solveForPathProbability(std::vector<int> path) {
  unsigned int distance = 0;
  std::tuple<long, long> probability = std::tuple(1, 1);

  for (const int &direction: path) {
    std::tuple<long, long> calc = hp::calcMovementProbabilityFrac(direction, distance);
    std::get<0>(probability) *= std::get<0>(calc);
    std::get<1>(probability) *= std::get<1>(calc);

    probability = hp::simplifyFraction(probability);

    distance += direction;
  }

  return probability;
}


bool hp::solveForProbabilities(std::string inputFileName, std::string outputFileName) {
  // Note input file has to have these criteria
  //   * Spaces before every line
  //   * 1 or -1 seperated by spaces to separate paths

  std::ifstream inputFile(inputFileName);
  std::ofstream outputFile(outputFileName);

  if (!inputFile.is_open() || !outputFile.is_open()) {
    return false;
  }

  std::string line;

  while (std::getline(inputFile, line)) {
    // Process the line here
    std::vector<int> path = hp::getPathFromString(line);

    std::tuple<long, long> probability = hp::solveForPathProbability(path);

    //std::cout << line << ": " << std::get<0>(probability) << " / " << std::get<1>(probability) << std::endl;
    outputFile << line << ": " << std::get<0>(probability) << " / " << std::get<1>(probability) << std::endl;
  }

  inputFile.close();
 
  return true;
}

std::tuple<long, long> hp::simplifyFraction(std::tuple<long, long> fraction) {
  long numerator = std::get<0>(fraction);
  long denominator = std::get<1>(fraction);
  long gcd = std::gcd(numerator, denominator);
  return std::make_tuple(numerator / gcd, denominator / gcd);
}

std::vector<std::vector<int>> hp::pathToMatrix(std::vector<int> path) {
  std::vector<std::vector<int>> pathMatrix;

  unsigned int distance = 0;

  for (const int &direction: path) {
    if (pathMatrix.size() < distance + 1) {
      std::vector<int> emptyDistance = {0, 0};
      pathMatrix.push_back(emptyDistance);
    }
    int index = direction == 1 ? 0 : 1;

    pathMatrix[distance][index]++;

    distance += direction;
  }

  return pathMatrix;
}

void hp::printMatrix(const std::vector<std::vector<int>> &matrix) {
  for (const auto &row: matrix) {
    for (const auto &element: row) {
      std::cout << element << " ";
    }
    std::cout << std::endl;
  }
}


std::vector<int> hp::getPathFromString(std::string pathString) {
  std::vector<int> path;

  std::stringstream ss(pathString);
  std::string token;

  while (std::getline(ss, token, ' ')) {
   std::stringstream tokenStream(token);
   int direction;
   ss >> direction;

   path.push_back(direction);
  }

  return path;
}


std::string hp::pathToString(std::vector<int> path) {
  std::stringstream pathString;

  for (int & direction : path) {
   pathString << ((direction == 1) ? ">" : "<") << " "; 
  }

  return pathString.str();
}
