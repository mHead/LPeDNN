#include "LPeDNN.h"

LPeDNN::LPeDNN(const vector<unsigned> &topology) {
    unsigned nLayers = topology.size();
    unsigned layerN = 0;
    for(layerN; layerN < nLayers; layerN++) {
        //create empty layer (we can then specify the layerType by passing it to the Layer() constructor)
        m_layers.push_back(Layer());
        //now foreach Layer we have to create neurons inside that Layer
        //the nNeurons of the layer are inside the topology vector
        //the <= is because we want to add the additional bias neuron, for each Layer
        unsigned neuronN = 0;
        unsigned nOutputs = layerN == topology.size() - 1 ? 0 : topology[layerN + 1];
        for(neuronN = 0; neuronN <= topology[layerN]; ++neuronN) {
            //get last element in the container
            m_layers.back().push_back(Neuron(nOutputs, neuronN));
            cout << "Neuron Created" << endl;


        }
    }
}

LPeDNN::~LPeDNN() { }

void LPeDNN::feedForward(const vector<float> &inputVals) {
    unsigned i = 0;
    unsigned layerN = 0;
    //input values has to be equal to the number of input neurons
    assert(inputVals.size() == m_layers[0].size() - 1);
    //assign (latch) the input values into the input neurons
    for(i = 0; i < inputVals.size(); ++i) {
        m_layers[0][i].setOutputValue(inputVals[i]);
    }

    //Forward propagation, looping in each next layer and tell to neurons 'please, feedforward'
    for(layerN = 1; layerN < m_layers.size(); ++layerN) {
        Layer &prevLayer = m_layers[layerN - 1];
        unsigned n = 0;
        for(n = 0; n < m_layers[layerN].size() - 1; ++n) { //the -1 is because of the bias neuron
            m_layers[layerN][n].feedForward(prevLayer); //this feedForward is a Neuron member function

        }
    }


}

void LPeDNN::backProp(const vector<float> &targetVals) {
    //calculate overall net error (RootMeanSquareError? or something else) this is the metric the backprop algorithm is trying to minimize
    //rms = sqrt[(1/n)*(sum[i < n](target[i] - actual[i])^2)]
    Layer &outputL = m_layers.back();
    m_error = 0.0;
    unsigned n = 0, layerN = 0;
    for(n = 0; n < outputL.size() - 1; ++n) {
        float delta = targetVals[n] - outputL[n].getOutputValue();
        m_error += delta*delta;
    }
    m_error /= outputL.size() - 1; //get the average error squared
    m_error = sqrt(m_error); //RMS

    //Implement a recent average measurement
    m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);


    //calculate output layer gradients
    for(n = 0; n < outputL.size() - 1; ++n) {
        outputL[n].calculateOutputGradients(targetVals[n]);
    }
    //calculate gradients on hidden layers
    for(layerN = m_layers.size() - 2; layerN > 0; --layerN) {
        Layer &hiddenL = m_layers[layerN];
        Layer &nextL = m_layers[layerN + 1];

        for(n = 0; n < hiddenL.size(); ++n) {
            hiddenL[n].calculateHiddenGradients(nextL);
        }
    }
    //for all layers from outputs to first hidden layer,
    //update connection weights
    for(layerN = m_layers.size() - 1; layerN > 0; --layerN) {
        Layer &actualL = m_layers[layerN];
        Layer &prevL = m_layers[layerN - 1];

        for(n = 0; n < actualL.size() - 1; ++n) {
            actualL[n].updateInputWeights(prevL);
        }

    }

    
}

void LPeDNN::getResults(vector<float> &resultsVals) const {
    resultsVals.clear();
    unsigned n;
    for(n = 0; n < m_layers.back().size() - 1; ++n) {
        resultsVals.push_back(m_layers.back()[n].getOutputValue());
    }
}
