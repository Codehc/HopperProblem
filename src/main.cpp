#include <iostream>
#include <fstream>
#include <thread>
#include "IterativeSimulation.h"

std::mutex mtx;
std::vector<std::unique_ptr<IterativeSimulation>> iterativeSimulations;

void runHopperProblem(int id) {
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

int main() {
    const int numThreads = 1000;
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

    return 0;
}