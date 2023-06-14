//
// Created by Reza Bagheri on 6/11/23.
//

#include <vector>
#include <cmath>
#include "PossiblePathsSimulation.h"

namespace hp {
    void PossiblePathsSimulation::calcuate() {
        unsigned int maxIterations = distance * 2;

        std::vector<std::unique_ptr<std::vector<int>>> simulations;

        if (distance == 1 || distance == 2) {
            // These are known so I'm not even going to bother calculating them
            std::unique_ptr<std::vector<int>> simulation;

            for (int i = 0; i < distance; i++) {
                simulation->push_back(FURTHER);
            }
            for (int i = 0; i < distance; i++) {
                simulation->push_back(CLOSER);
            }

            simulations.push_back(std::move(simulation));
        } else {
            std::unique_ptr<std::vector<int>> baseSim;

            // Create the base baseSim
            for (int i = 0; i < maxIterations/2; i++) {
                baseSim->push_back(FURTHER);
            }
            for (int i = 0; i < maxIterations/2; i++) {
                baseSim->push_back(CLOSER);
            }
        }
    }

    /*std::vector<int> iterate(std::vector<int> current) {

    }*/
} // hp