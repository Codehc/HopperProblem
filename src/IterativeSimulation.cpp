//
// Created by Reza Bagheri on 6/9/23.
//

#include "hp.h"
#include "IterativeSimulation.h"

IterativeSimulation::IterativeSimulation(unsigned int id): id(id), iteration(0), distance(0), maxDistance(0), done(false) {}

bool IterativeSimulation::isDone() const {
    return done;
}

unsigned int IterativeSimulation::getID() const {
    return id;
}

void IterativeSimulation::iterate() {
    if (distance < 0 || (distance == 0 && iteration != 0)) {
        done = true;
        return;
    }

    iteration++;

    if (hp::getDirection(distance) == AWAY) {
        distance++;
    } else {
        distance--;
    }

    if (distance > maxDistance) {
        maxDistance = distance;
    }
}

unsigned int IterativeSimulation::getDistance() const {
    return distance;
}

unsigned int IterativeSimulation::getMaxDistance() const {
    return maxDistance;
}

unsigned int IterativeSimulation::getIteration() const {
    return iteration;
}
