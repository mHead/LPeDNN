#ifndef LOWPOWERNEURALNETWORK_DEEPNEURALNETWORK_H
#define LOWPOWERNEURALNETWORK_DEEPNEURALNETWORK_H

/**
 * Default Hyperparameters for a test set accuracy equals to 95.61%
 * */
#define INPUT_IMAGE_SIZE 28
#define CONV2D_SIZE 3
//#define CONV2D_SIZE 2
#define MAX_POOL_SIZE 2
#define DROPOUT_RATE 0.25
#define N_OUT_CLASSES 36

/**
 * Layers inputs-outputs dimensions (each dimension refers to a single dimension -> matrix are squares)
 */

// CONV1
#define CONV2D_1_INPUT_SIZE INPUT_IMAGE_SIZE
#define CONV2D_1_OUTPUT_SIZE (CONV2D_1_INPUT_SIZE-CONV2D_SIZE+1)

#define MAX_POOL_1_INPUT_SIZE CONV2D_1_OUTPUT_SIZE
#define MAX_POOL_1_OUTPUT_SIZE (MAX_POOL_1_INPUT_SIZE / 2)

// CONV2
#define CONV2D_2_INPUT_SIZE MAX_POOL_1_OUTPUT_SIZE
#define CONV2D_2_OUTPUT_SIZE (CONV2D_2_INPUT_SIZE-CONV2D_SIZE+1)


#define MAX_POOL_2_INPUT_SIZE CONV2D_2_OUTPUT_SIZE
#define MAX_POOL_2_OUTPUT_SIZE (MAX_POOL_2_INPUT_SIZE/2)

//// CONV3
//#define CONV2D_3_INPUT_SIZE MAX_POOL_2_OUTPUT_SIZE
//#define CONV2D_3_OUTPUT_SIZE CONV2D_3_INPUT_SIZE-CONV2D_SIZE+1
//
//#define MAX_POOL_3_INPUT_SIZE CONV2D_3_OUTPUT_SIZE
//#define MAX_POOL_3_OUTPUT_SIZE MAX_POOL_3_INPUT_SIZE / 2

#define FLATTEN_INPUT_SIZE MAX_POOL_2_OUTPUT_SIZE
#define FLATTEN_OUTPUT_SIZE (FLATTEN_INPUT_SIZE * FLATTEN_INPUT_SIZE)


#define DENSE_INPUT_SIZE FLATTEN_OUTPUT_SIZE
//#define DENSE_INPUT_SIZE 5

#define DENSE_OUTPUT_SIZE N_OUT_CLASSES
//#define DENSE_OUTPUT_SIZE 3

#define DENSE_WEIGHTS_LEN (DENSE_INPUT_SIZE * DENSE_OUTPUT_SIZE)


#include <iostream>
#include <algorithm>
#include <limits>

/**
 * Static dimensioned deep neural network without dynamic allocation
 */
class DeepNeuralNetwork {
//private:
public:
    float conv2d_1_output[CONV2D_1_OUTPUT_SIZE][CONV2D_1_OUTPUT_SIZE];
    float maxpool_1_output[MAX_POOL_1_OUTPUT_SIZE][MAX_POOL_1_OUTPUT_SIZE];
    float conv2d_2_output[CONV2D_2_OUTPUT_SIZE][CONV2D_2_OUTPUT_SIZE];
    float maxpool_2_output[MAX_POOL_2_OUTPUT_SIZE][MAX_POOL_2_OUTPUT_SIZE];
//    float conv2d_3_output[CONV2D_3_OUTPUT_SIZE][CONV2D_3_OUTPUT_SIZE];
//    float maxpool_3_output[MAX_POOL_3_OUTPUT_SIZE][MAX_POOL_3_OUTPUT_SIZE];
    float flatten_output[FLATTEN_OUTPUT_SIZE];
    float dense_output[DENSE_OUTPUT_SIZE];

    float leaky_relu(float x);

    void conv2d_1(const float input[][CONV2D_1_INPUT_SIZE], const float kernel[][CONV2D_SIZE], float output[][CONV2D_1_OUTPUT_SIZE]);
    void maxpool2d_1(const float input[][MAX_POOL_1_INPUT_SIZE], float output[][MAX_POOL_1_OUTPUT_SIZE]);
    void conv2d_2(const float input[][CONV2D_2_INPUT_SIZE], const float kernel[][CONV2D_SIZE], float output[][CONV2D_2_OUTPUT_SIZE]);
    void maxpool2d_2(const float input[][MAX_POOL_2_INPUT_SIZE], float output[][MAX_POOL_2_OUTPUT_SIZE]);
//    void conv2d_3(const float input[][CONV2D_3_INPUT_SIZE], const float kernel[][CONV2D_SIZE], float output[][CONV2D_3_OUTPUT_SIZE]);
//    void maxpool2d_3(const float input[][MAX_POOL_3_INPUT_SIZE], float output[][MAX_POOL_3_OUTPUT_SIZE]);
    void flatten(const float input[][FLATTEN_INPUT_SIZE], float *output);
    void dense(const float *input, float *output);
//public:
    DeepNeuralNetwork();

    int inference(const int image[][INPUT_IMAGE_SIZE]);

};


#endif //LOWPOWERNEURALNETWORK_DEEPNEURALNETWORK_H
