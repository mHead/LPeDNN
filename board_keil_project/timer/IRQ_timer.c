/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"

extern void start(void);
extern void clearPad(void);
extern void spaceText(int x1, int x2, int yText, int spessore, uint16_t color);

extern int startGame;

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void)
{
  getDisplayPoint(&display, Read_Ads7846(), &matrix ) ; //resto in attesa di un punto che venga toccato
	if(display.x <= 240 && display.x > 0){
		if(display.y >= 64 && display.y <= 259 && display.x >=8 && display.x <= 232){//punto in zona alta (start writing)
			if(!startGame){
			  startGame=1;
				clearPad();
			}	
			else{//game already started: handwriting input
				
			}
		}
		else{		
			if(display.y >= 275 && display.y <= 307 && display.x >=8 && display.x <= 110 &&startGame){//punto in tasto Space
				//wait flag to able
				
				spaceText(7,7+8*13-1,283,8,Yellow);
				GUI_Text(7, 283, (uint8_t *) "    Space    ", Blue, Yellow,1);
				spaceText(7,7+8*13-1,283+16+8,8,Yellow);
				
				//space operation
				
				spaceText(7,7+8*13-1,283,8,White);
				GUI_Text(7, 283, (uint8_t *) "    Space    ", Blue, White,1);
				spaceText(7,7+8*13-1,283+16+8,8,White);
			}
			else{
				if(display.y >= 275 && display.y <= 307 && display.x >=129 && display.x <= 232 &&startGame){//punto in tasto Delete
					//wait flag to able
					
					spaceText(129,129+8*13-1,283,8,Yellow);
					GUI_Text(129, 283, (uint8_t *) "    Delete   ", Blue, Yellow,1);
					spaceText(129,129+8*13-1,283+16+8,8,Yellow);
					
					//delete operation
					
					spaceText(129,129+8*13-1,283,8,White);
					GUI_Text(129, 283, (uint8_t *) "    Delete   ", Blue, White,1);
					spaceText(129,129+8*13-1,283+16+8,8,White);
				}
			}
		}
	}
	else{
		//do nothing if touch returns values out of bounds
	}
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void) /*TIM1*/
{
	if((LPC_TIM1->IR & (1<<0)) !=0 ){ //MR0 INTERRUPT
	
		LPC_TIM1->IR = 1;			/* clear interrupt flag (bit 0 di IR)*/
	}
	else{ 
		if((LPC_TIM1->IR & (1<<1)) !=0 ){ //MR1 INTERRUPT
			
			LPC_TIM1->IR = 2;			/* clear interrupt flag (bit 1 di IR)*/
		}
	}
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
