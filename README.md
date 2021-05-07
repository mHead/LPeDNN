# LPeDNN
The project aims to embed a Deep Neural Network in charge of recognize characters from a touchscreen on a Low Power Board, specifically the LandTiger NXP LPC1768 based on ARM Cortex-M3 ucontroller
### Development general constraints
 1. DNN Accuracy > 95%
 2. Low degree of redundancy, small DNN size
 3. Develop keeping in mind that ***reliability tests*** will be performed
    - Pixel flip during transfer is a fault
    - How many faults can the DNN afford?
    - Noise injection will be performed
    - Occlusion learning has to be considered
## Step1
 1. Retrieve character from the touchscreen 
 2. Provide to the user a mechanism to confirm the input (low priority)
 3. If user confirms, the character is compressed and then ready to be sent via USB/RS232 port (if we manage to use USB, great)
 4. The character is sent to the DNN running on a PC
 5. The DNN makes the prediction and it is displayed on the touchscreen
 6. The user can, at this point, give a feedback on the correctness of the predicted character
 7. Decide how we want to display the character which passed all steps
 8. Provide to the user a mechanism to stop the input phase (stop: y/n)
 9. y ? stop : goto 1
 
 ## Step2
  1. No PC is needed then no serial connection is needed anymore
  2. The DNN has to be reduced in order to embed it on the board
  3. With the extra material try to expand the concept of **'reduce the DNN'**

## USB Serial Communication

### Jumper configuration
Use the following configuration for the jumpers:

![Cattura](https://user-images.githubusercontent.com/17108362/114763685-5fd43d00-9d63-11eb-9796-44ccb49d0f8e.PNG)

IMPORTANT: notice that JP9 and JP11 are "switched" to the side of D+ and D- respectively and this is what enables the USB connection

### Serial Write

The Landtiger's side on the communication is based on the USBDevice library (available in the Mbed compiler).
Here's a basic example of its use: https://os.mbed.com/handbook/USBSerial

### Serial Read

The PC's side of the communication is based on this library: https://github.com/ZainUlMustafa/Connect-And-Use-Arduino-via-Cpp-Software-Made-In-Any-IDE/tree/master/Arduino2PC_SC (only main.cpp, SerialPort.cpp and SerialPort.h are important).
IMPORTANT: the main.cpp assumes that the communication takes place in the port COM3, so if things do not work verify via the device manager that the port is actually that one
