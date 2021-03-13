/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Andrea Protopapa
** Modified date:           13/03/2021
** Version:                 v2.0
** Descriptions:            Touch Panel - Char Acquisition 
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

void start(void);
void clearPad(void);
void clearBar(void);
void spaceText(int x1, int x2, int yText, int spessore, uint16_t color);
void gameInit(void);


extern void controllo_pericolo(void);

int startGame=0;
																 

																 
int mode = 0; //move=0 explore=1
																 
																 
int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	
  LCD_Initialization();
	
  
	TP_Init();
	TouchPanel_Calibrate();
	
	//init_timer(0, 0x1312D0 ); 						/* 50ms * 25MHz = 1.25*10^6 = 0x1312D0 */
	//init_timer(0, 0x6108 ); 						  /* 1ms * 25MHz = 25*10^3 = 0x6108 */
	init_timer(0, 0x4E2 ); 						    /* 500us * 25MHz = 1.25*10^3 = 0x4E2 */
																				/*TIM0: gestisce le azioni sul touchscreen*/
	
	LCD_Clear(Blue2);
	
	clearBar();
	
	spaceText(7,7+8*13-1,283,8,White);
	GUI_Text(7, 283, (uint8_t *) "    Space    ", Blue, White,1);
	spaceText(7,7+8*13-1,283+16+8,8,White);
	
	spaceText(129,129+8*13-1,283,8,White);
	GUI_Text(129, 283, (uint8_t *) "    Delete   ", Blue, White,1);
	spaceText(129,129+8*13-1,283+16+8,8,White);
	
	start();
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}

void start(){
	disable_timer(0);
	reset_timer(0);
	
	//won=1; //non faccio ancora usare il joystick in IRQ_RIT
	clearPad();
	GUI_Text(22, 85, (uint8_t *) "Touch to", Black, White, 3);
	GUI_Text(32, 133, (uint8_t *)" start", Black, White, 3);
	GUI_Text(22, 181, (uint8_t *) "writing!", Black, White, 3);
	
	startGame=0;
	enable_timer(0);
	
	return;
}

void spaceText(int x1, int x2, int yText, int spessore, uint16_t color){ //Spazio di un unico colore
	int i;
	for(i=spessore;i>0;i--){
		LCD_DrawLine(x1,yText-i,x2,yText-i,color);
	}
	return;
}

void clearPad(){
	int i;
	for(i=0;i<195;i++){
		LCD_DrawLine(7,64+i,232,64+i,White);
	}
	return;
}

void clearBar(){
	int i;
	for(i=0;i<32;i++){
		LCD_DrawLine(7,16+i,232,16+i,White);
	}
	return;
}




/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
