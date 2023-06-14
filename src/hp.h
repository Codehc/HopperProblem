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
    double probabilityCalc(unsigned int direction, unsigned int distance);
    std::tuple<long long, long long> probabilityCalcSplit(unsigned int direction, unsigned int distance);
    std::tuple<long long, long long> solveForPathProbability(std::vector<int> path);
    std::tuple<long long, long long> simplifyFraction(std::tuple<long long, long long> fraction);
    void solveForProbabilities(std::string inputFile, std::string outputFile);
}

#endif //HOPPER_PROBLEM_SIM_HP_H
