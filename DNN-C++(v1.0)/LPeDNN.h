#include <sys/types.h>
#include <iostream>
#include <vector>
#include <cassert>
#include <math.h>
#include "Neuron.h"
#include "Layer.h"
using namespace std;

//class Neuron {};
typedef vector<Neuron> Layer;
float Neuron::eta = 0.15; //learning rate
float Neuron::alpha = 0.5; //momentum, multiplier of last deltaWeight


class LPeDNN {
    private:
        vector<Layer> m_layers; //m_layers[layerN][neuronNum]
        float m_error;
        float m_recentAverageError;
        float m_recentAverageSmoothingFactor;
    public:
        LPeDNN(const vector<unsigned> &topology);
        ~LPeDNN();
        /*
        * @param vector<float> &inputs
        * passed by reference, feedF has only to read values
        * and transfer to the input neurons, so the vector will not change
        */
        void feedForward(const vector<float> &inputVals);
        /*
        * @param vector<float> &targets
        * passed by reference, backProp has only to read values
        * and transfer back to the input neurons, so the vector will not change
        */
        void backProp(const vector<float> &targetVals);
        /*
        * @param vector<float> &results
        * passed by reference, backProp has only to read values
        * and transfer back to the input neurons, so the vector will not change
        */
        void getResults(vector<float> &resultsVals) const;


};