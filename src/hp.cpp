//
// Created by Reza Bagheri on 6/9/23.
//

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <random>

#include "hp.h"

int hp::getDirection(unsigned int distance) {
    if (distance == 0) {
        return AWAY;
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