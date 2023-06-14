//
// Created by Reza Bagheri on 6/11/23.
//

#ifndef HOPPER_PROBLEM_SIM_POSSIBLEPATHSSIMULATION_H
#define HOPPER_PROBLEM_SIM_POSSIBLEPATHSSIMULATION_H


#define FURTHER 0
#define CLOSER 1

namespace hp {

  class PossiblePathsSimulation {
    unsigned int distance;
  public:
    void calcuate();
  };

} // hp

#endif //HOPPER_PROBLEM_SIM_POSSIBLEPATHSSIMULATION_H
