//
// Created by Reza Bagheri on 6/9/23.
//

#include "../hp.h"
#include "IterativeSimulation.h"
#include <thread>
#include <iostream>
#include <fstream>

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

    if (hp::getDirection(distance) == FURTHER) {
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

std::mutex mtx;
std::vector<std::unique_ptr<IterativeSimulation>> iterativeSimulations;

void hp::runHopperProblem(int id) {
    std::unique_ptr<IterativeSimulation> iterativeSimulation = std::make_unique<IterativeSimulation>(id);

    std::ofstream log;
    log.open ( "./../logs/Thread" + std::to_string(id) + "Log.txt");

    while (true) {
        iterativeSimulation->iterate();

        if (iterativeSimulation->isDone()) {
            break;
        }

        log << "Iteration #" << iterativeSimulation->getIteration() << " at distance " << iterativeSimulation->getDistance() << std::endl;
    }

    mtx.lock();
    iterativeSimulations.push_back(std::move(iterativeSimulation));
    mtx.unlock();

    log.close();
}

void hp::multithreadSimulation(int threadsNum) {
    const int numThreads = threadsNum;
    std::thread threads[numThreads];

    // Create and start the threads
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = std::thread(runHopperProblem, i);
    }

    for (auto & thread : threads) {
        thread.join();
    }

    std::sort(iterativeSimulations.begin(), iterativeSimulations.end(), [](const std::unique_ptr<IterativeSimulation>& a, const std::unique_ptr<IterativeSimulation>& b) {
        return a->getMaxDistance() > b->getMaxDistance();
    });

    unsigned int totalIterations = 0;
    unsigned int totalDistance = 0;
    for (std::unique_ptr<IterativeSimulation> & simulation : iterativeSimulations) {
        totalIterations += simulation->getIteration();
        totalDistance += simulation->getMaxDistance();
        std::cout << "Sim ID " << simulation->getID() << " max distance achieved was " << simulation->getMaxDistance() << ". Took " << simulation->getIteration() << " iterations" << std::endl;
    }

    std::cout << "Average iterations: " << totalIterations / (double) iterativeSimulations.size() << "   Average max distance: " << totalDistance / (double) iterativeSimulations.size() << std::endl;
}