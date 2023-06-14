//
// Created by Reza Bagheri on 6/9/23.
//

#ifndef HOPPER_PROBLEM_SIM_ITERATIVESIMULATION_H
#define HOPPER_PROBLEM_SIM_ITERATIVESIMULATION_H


#include <random>

class IterativeSimulation {
    unsigned int id;
    unsigned int iteration;
    unsigned int distance;
    unsigned int maxDistance;
    bool done;
public:
    IterativeSimulation(unsigned int id);

    void iterate();
    unsigned int getID() const;
    unsigned int getDistance() const;
    unsigned int getMaxDistance() const;
    unsigned int getIteration() const;
    bool isDone() const;
};

namespace hp {
    void multithreadSimulation(int threadsNum);
    void runHopperProblem(int id);
}


#endif //HOPPER_PROBLEM_SIM_ITERATIVESIMULATION_H