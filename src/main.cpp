#include "hp.h"

int main() {

    //hp::solveForProbabilities("../res/marshall_requested_paths.txt", "../res/probabilities.txt");
    //hp::solveForProbabilities("../res/paths/possible_paths.txt", "../res/paths/probabilities.txt");

    std::vector<int> path = {1, 1, -1, -1};
    hp::printMatrix(hp::pathToMatrix(path));

    return 0;
}