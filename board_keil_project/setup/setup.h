#ifndef __SETUP_H 
#define __SETUP_H

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "../TouchPanel/TouchPanel.h"
#include <stdio.h>
#include <stdlib.h>
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"

/*Buttons*/
typedef enum {space,infer,del} button;

/* Private function prototypes -----------------------------------------------*/				
void spaceText(int x1, int x2, int yText, int spessore, uint16_t color);
void clearPad(void);
void showCompression(void);
void clearBar(void);
void drawButtons(void);
void drawButton(button b, uint16_t color);
void start(void);
void drawTriangle(int posX, int posY, int lungMax);


#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
