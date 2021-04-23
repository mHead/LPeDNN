#include <vector>
#include <math.h>
#include "LPeDNN.h"

using namespace std;

int main() {
    vector<unsigned> topology;
    vector<float> inputVals, targetVals, resultsVals; 
    
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);


    LPeDNN dnn = LPeDNN(topology);


    dnn.feedForward(inputVals);
    dnn.backProp(targetVals);
    dnn.getResults(resultsVals);
}