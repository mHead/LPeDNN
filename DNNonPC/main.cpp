#include <iostream>
#include <string>
#include <stdlib.h>
#include "SerialPort.h"
#include "DeepNeuralNetwork.h"

char serialMessage[MAX_DATA_LENGTH];
char port[10] = "\\\\.\\COM3";
uint8_t mat[INPUT_IMAGE_SIZE * INPUT_IMAGE_SIZE];
int well[INPUT_IMAGE_SIZE][INPUT_IMAGE_SIZE];

int main() {
    DeepNeuralNetwork dnn;

    int nR;
    int ind = 0;
    char curr[2] = "0";
    SerialPort landtigerSerialPort(port);
    if (landtigerSerialPort.isConnected())
        std::cout << "Connection established\n";
    else
        std::cout << "Connection failed\n";

    std::cout << "Reading next character.." << std::endl;
    while (landtigerSerialPort.isConnected()) {
        nR = landtigerSerialPort.readSerialPort(serialMessage, MAX_DATA_LENGTH);
        if (nR > 0) {
            //std::cout << "Read characters: " << nR << "\n";
            for (int i = 0; i < nR; i++) {
                curr[0] = serialMessage[i];
                mat[ind] = atoi(curr);
                ind++;
            }
            //serialMessage[nR] = '\0';
            //std::cout << serialMessage;
            int j = 0;
            int k = 0;
            if (ind == 784) {
                for (int i = 0; i < 784; i++) {
                    if (i % 28 == 0) {
                        k++;
                        j=0;
                        //std::cout << "\n";
                    }
                    well[k][j] = mat[i];
                    //printf("%d", (int)mat[i]);
                    j++;
                }
                //printf("\n");
                //printf("\n");

                std::cout << "Character received:" << std::endl;
                for (int i=0; i<28; i++) {
                    for (int j = 0; j < 28; j++) {
                        printf("%d", (int) well[i][j]);
                    }
                    printf("\n");
                }
                std::cout << '\n';
                std::cout << "Trying to predict the character.." << std::endl;
                int prediction = dnn.inference(well);
                std::cout << "Predicted: " << DeepNeuralNetwork::label_to_char(prediction) << std::endl;

                ind = 0;
                std::cout << '\n';
                std::cout << "Reading next character.." << std::endl;
            }
        }
    }

    return 0;
}
