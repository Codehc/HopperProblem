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

double hp::probabilityCalc(unsigned int direction, unsigned int distance) {
    if (direction == 1) {
        return pow(2.0, distance) / (1 + pow(2.0, distance));
    } else if (direction == -1) {
        return 1 / (1 + pow(2.0, distance));
    } else {
        return 0;
    }
}

std::tuple<long long, long long> hp::probabilityCalcSplit(unsigned int direction, unsigned int distance) {
    if (direction == 1) {
        return std::make_tuple(pow(2ll, distance), (1ll + pow(2ll, distance)));
    } else if (direction == -1) {
        return std::make_tuple(1ll, (1ll + pow(2ll, distance)));
    } else {
        return std::make_tuple(0ll, 1ll);
    }
}

std::tuple<long long, long long> hp::solveForPathProbability(std::vector<int> path) {
    unsigned int distance = 0;
    std::tuple<long long, long long> probability = std::tuple(1, 1);

    for (int & direction : path) {
        std::tuple<long long, long long> calc = hp::probabilityCalcSplit(direction, distance);
        std::get<0>(probability) *= std::get<0>(calc);
        std::get<1>(probability) *= std::get<1>(calc);

        probability = hp::simplifyFraction(probability);

        distance += direction;
    }

    return probability;
}


void hp::solveForProbabilities(std::string inputFileName, std::string outputFileName) {
    // Note input file has to have these criteria
    //   * Spaces before every line
    //   * 1 or -1 seperated by spaces to separate paths

    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);

    if (inputFile.is_open() && outputFile.is_open()) {
        std::string line;

        while (std::getline(inputFile, line)) {
            // Process the line here
            std::vector<int> path;

            std::stringstream ss(line);
            std::string token;

            while (std::getline(ss, token, ' ')) {
                // Process each token (substring) here
                std::stringstream tokenStream(token);
                int direction;
                ss >> direction;

                path.push_back(direction);
            }

            std::tuple<long long, long long> probability = hp::solveForPathProbability(path);

            std::cout << line << ": " << std::get<0>(probability) << " / " << std::get<1>(probability) << std::endl;
            outputFile << line << ": " << std::get<0>(probability) << " / " << std::get<1>(probability) << std::endl;
        }

        inputFile.close();
        outputFile.close();
    } else {
        std::cout << "Unable to open one of the two files" << std::endl;
    }
}

std::tuple<long long, long long> hp::simplifyFraction(std::tuple<long long, long long> fraction) {
    int numerator = std::get<0>(fraction);
    int denominator = std::get<1>(fraction);
    int gcd = std::gcd(numerator, denominator);
    return std::make_tuple(numerator / gcd, denominator / gcd);
}