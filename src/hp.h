//
// Created by Reza Bagheri on 6/9/23.
//

#ifndef HOPPER_PROBLEM_SIM_HP_H
#define HOPPER_PROBLEM_SIM_HP_H

#define FURTHER 0
#define CLOSER 1


#include <random>
#include <vector>
#include <tuple>

namespace hp {
    int getDirection(unsigned int distance);

    double calcMovementProbability(unsigned int direction, unsigned int distance);

    std::tuple<long long, long long> calcMovementProbabilityFrac(unsigned int direction, unsigned int distance);

    std::tuple<long long, long long> solveForPathProbability(std::vector<int> path);

    void solveForProbabilities(std::string inputFile, std::string outputFile);

    std::tuple<long long, long long> simplifyFraction(std::tuple<long long, long long> fraction);

    std::vector<std::vector<int>> pathToMatrix(std::vector<int> path);

    void printMatrix(const std::vector<std::vector<int>> &matrix);
}

#endif //HOPPER_PROBLEM_SIM_HP_H
