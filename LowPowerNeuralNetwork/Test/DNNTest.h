//
// Created by rugge on 7/29/2021.
//

#ifndef LOWPOWERNEURALNETWORK_DNNTEST_H
#define LOWPOWERNEURALNETWORK_DNNTEST_H

#include "../DeepNeuralNetwork.h"

#include <cassert>

class DNNTest {
public:
    DNNTest();
    void test_conv2d();
    void test_maxpool2d();
    void test_dense();
};


#endif //LOWPOWERNEURALNETWORK_DNNTEST_H
