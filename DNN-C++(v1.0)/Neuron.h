#include <cstdlib>
#include <vector>

struct Connection {
    float weight;
    float deltaWeight;
};
float slope = 0;

class Neuron {
    private:
        //tunable parameters
        static float eta; //[0.0 ... 1.0]
        static float alpha; // [0.0 ... n] multiplier of last weight change (momentum)

        //attributes
        unsigned m_myIndex;
        float m_outputVal;
        float m_gradient;
        vector<Connection> m_outputWeights; 
        static float randomWeight(void) {return rand() / float(RAND_MAX); } // return a random number between 0 and 1
        static float transferFunction(float x);
        static float transferFunctionDerivative(float x); //to be used in backward propagation
        float sumDOW(const Layer &nextL) const;
    public:
        Neuron(unsigned nOutputs, unsigned myIndex);
        ~Neuron();
        void setOutputValue(float value);
        float getOutputValue() const;
        void feedForward(const Layer &prevL);
        void calculateOutputGradients(float targetVal);
        void calculateHiddenGradients(const Layer &nextL);
        void updateInputWeights(const Layer &prevL);


};