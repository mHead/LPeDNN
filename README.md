# LPeDNN
The project aims to embed a Deep Neural Network in charge of recognize characters from a touchscreen on a Low Power Board, specifically the LandTiger NXP LPC1768 based on ARM Cortex-M3 ucontroller

## Development links
- Github link: [This repo](https://github.com/mHead/LPeDNN)
- Google Colab link: [Google colab notebook](https://colab.research.google.com/drive/1Djr86fD04rr9ghCRvYnNfeGwNH2MOrM6?usp=sharing#scrollTo=OWICnxbwIYg5)
- Mbed repo: [Mbed repo](https://os.mbed.com/users/montie97/code/USB_KeyBoard_Mouse_copy/)

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
