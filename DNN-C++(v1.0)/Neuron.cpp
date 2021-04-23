#define ReLU 0
#define LEAKY_ReLU 1
#include "Neuron.h"

Neuron::Neuron(unsigned nOutputs, unsigned myIndex) {
    unsigned conn = 0;
    for(conn = 0; conn < nOutputs; ++conn) {
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = randomWeight();
    }
    m_myIndex = myIndex;
}

Neuron::~Neuron() { }

void Neuron::setOutputValue(float value) {
    this->m_outputVal = value;
}
float Neuron::getOutputValue() const {
    return this->m_outputVal;
}

void Neuron::feedForward(const Layer &prevL) {
    //output = f(sum[i](i[i]*w[i]))
    float sum = 0;
    unsigned n = 0; //handle for each neuron

    //sum the previous layer's outputs (which are out inputs)
    //include the bias node from the prevLayer
    for(n = 0; n < prevL.size(); ++n) {
        //what is the index of m_outputsWeights?
        sum += prevL[n].getOutputValue() * prevL[n].m_outputWeights[m_myIndex].weight;
    }

    //defining the activation function to shape the sum and set the output right
    m_outputVal = Neuron::transferFunction(sum, LEAKY_ReLU);

}

static float Neuron::transferFunction(float x, unsigned type) {
    //implement a LeakyReLU
    /*
    * f(x) = 0.01x if x < 0
    * f(x) = x otherwise
    */
    switch(type) {
        case ReLU:
            float y = x < 0 ? 0 : x;
            break;
        case LEAKY_ReLU:
            slope = 0.01;
            float y = x < 0 ? (slope*x) : x;
            break;
        default:
            break;
    }
    
    return y; 
}

static float Neuron::transferFunctionDerivative(float x, unsigned type) {
    float slope = 0;
    switch(type) {
        case ReLU:
            float y = x < 0 ? 0 : 1;
            break;
        case LEAKY_ReLU:
            slope = 0.01;
            float y = x < 0 ? slope : 1;
            break;
        default:
            break;
    }
    
    return y; 
}


void Neuron::calculateOutputGradients(float targetVal) {
    float delta = targetVal - m_outputVal;
    m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}
void Neuron::calculateHiddenGradients(const Layer &nextL) {
    float dow = sumDOW(nextL);
    m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal); 
}
void Neuron::updateInputWeights(const Layer &prevL) {
    //The weights to be updated are in the Connection container in the neurons in the previous layer
    unsigned n = 0;
    for(n = 0; n < prevL.size(); ++n) {
        Neuron &neuron = prevL[n];
        float oldDeltaWeight = neuron.m_outputWeight[m_myIndex].deltaWeight;
        /* newDeltaWeight is composed by different factors
        *   individual input, magnified by the gradient and train rate (eta)
        *       eta: overall net learning rate
        *           0.0 slow learner
        *           0.2 medium learner
        *           1.0 reckless learner
        *   prevLayer neurons output values * our neuron gradient
        *       alpha: momentum
        *           0.0 no momentum
        *           0.5 moderate momentum
        */  
        float newDeltaWeight = eta * neuron.getOutputValue() * m_gradient + alpha * oldDeltaWeight;
        neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
        neuron.m_outputWeights[m_myIndex].weight += newDeltaWeights;
    }
}

float Neuron::sumDOW(const Layer &nextL) const {
    float sum = 0.0
    unsigned n = 0;
    //Sum our contributions of the errors at the nodes we feed
    for(n = 0; nextL.size() - 1; ++n) {
        sum += m_outputWeights[n].weight * nextL[n].m_gradient;
    }
    return sum;
}