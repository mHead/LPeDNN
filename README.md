# LPeDNN
The project aims to embed a Deep Neural Network in charge of recognize characters from a touchscreen on a Low Power Board, specifically the LandTiger NXP LPC1768 based on ARM Cortex-M3 ucontroller
### Development general constraints
 1. DNN Accuracy > 90%
 2. Develop keeping in mind that ***reliability tests*** will be performed
    - Pixel flip during transfer is a fault
    - How many faults can the DNN afford?
    - Noise injection will be performed
## Step1
 1. Retrieve character from the touchscreen
 2. Provide to the user a mechanism to confirm the input 
 3. If user confirms, the character is compressed and then ready to be sent via UARTS port
 4. The character is sent to the DNN running on a PC
 5. The DNN makes the prediction and it is displayed on the touchscreen
 6. The user can, at this point, give a feedback on the correctness of the predicted character
 7. Decide how we want to display the character which passed all steps
 8. Provide to the user a mechanism to stop the input phase (stop: y/n)
 9. y ? stop : goto 1
 
 ## Step2
  1. No PC is needed then no UARTS connection is needed anymore
  2. The DNN has to be reduced in order to embed it on the board
  3. With the extra material try to expand the concept of **'reduce the DNN'**
