//
// Created by rugge on 7/29/2021.
//

//#include "DNNTest.h"
//
//DNNTest::DNNTest() {
//
//}
//
//void DNNTest::test_conv2d() {
//    DeepNeuralNetwork dnn;
//
//    float input[CONV2D_INPUT_SIZE][CONV2D_INPUT_SIZE] = {
//            {1.0, 2.0, 3.0},
//            {0.0, 0.5, 1.0},
//            {2.0, 1.0, 1.0}
//    };
//
//    float conv2D_filter[CONV2D_SIZE][CONV2D_SIZE] = {
//            {2.0, 3.0},
//            {1.0, 2.0}
//    };
//
//    float conv2d_output[CONV2D_OUTPUT_SIZE][CONV2D_OUTPUT_SIZE];
//
//    dnn.conv2d(input, conv2D_filter, conv2d_output);
//
//    assert(conv2d_output[0][0] == 9.0);
//    assert(conv2d_output[0][1] == 15.5);
//    assert(conv2d_output[1][0] == 5.5);
//    assert(conv2d_output[1][1] == 7.0);
//
//}
//
//void DNNTest::test_maxpool2d() {
//    DeepNeuralNetwork dnn;
//
//    float input[MAX_POOL_INPUT_SIZE][MAX_POOL_INPUT_SIZE] = {
//            {1.0, 2.0, 3.0, 1.5},
//            {0.0, 0.5, 1.0, 3.5},
//            {2.0, 1.0, 1.0, 1.0},
//            {5.0, 1.0, 2.0, 2.0}
//    };
//
//    float output[MAX_POOL_OUTPUT_SIZE][MAX_POOL_OUTPUT_SIZE];
//
//    dnn.maxpool2d(input, output);
//
//    assert(output[0][0] == 2.0);
//    assert(output[0][1] == 3.5);
//
//    assert(output[1][0] == 5.0);
//    assert(output[1][1] == 2.0);
//
//}
//
//void DNNTest::test_dense() {
//    DeepNeuralNetwork dnn;
//
//    float input[DENSE_INPUT_SIZE] = {1.0, 0.0, 2.5, 3.0, 2.0};
//
//    float output[DENSE_OUTPUT_SIZE];
//
//    dnn.dense(input, output);
//
//    assert(output[0] == 24.5);
//    assert(output[1] == 23.0);
//    assert(output[2] == 39.5);
//
//}