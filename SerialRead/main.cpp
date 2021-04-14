#include <iostream>
#include <string>
#include <stdlib.h>
#include "SerialPort.h"

char serialMessage[MAX_DATA_LENGTH];
char* port = "\\\\.\\COM3";

int main()
{
    SerialPort landtigerSerialPort(port);
	if(landtigerSerialPort.isConnected())
		std::cout << "Connection established\n";
	else
		std::cout << "Connection failed\n";
		
	while (landtigerSerialPort.isConnected()) {
	  landtigerSerialPort.readSerialPort(serialMessage, MAX_DATA_LENGTH);
	  std::cout << serialMessage;
	 }
	return 0;
}
