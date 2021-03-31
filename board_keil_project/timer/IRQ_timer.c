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
#include "../setup/setup.h"

#define DEBUG 

extern int startGame;
extern int isWritten;
extern int inferenceStarted;
extern uint8_t drawnPoints[28][28];
extern int threshold;

int charPos;

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
	int i,j;
	Coordinate p;
  getDisplayPoint(&display, Read_Ads7846(), &matrix ) ; //resto in attesa di un punto che venga toccato
	if(display.x <= 240 && display.x > 0){
		if(display.y >= 52 && display.y <= 275 && display.x >=8 && display.x <= 232){//punto in zona alta (start writing)
			if(!startGame){
			  startGame=1;
				clearPad();
				charPos=0;
			}	
			else{//game already started: handwriting input
				if(charPos<26*8){ //topbar bound: otherwise the topbar is full
					#ifdef DEBUG 
					if(!isWritten)
						clearPad();//clear to delete the testing result printed on screen	before		
					#endif
					TP_DrawPoint(display.x,display.y);
					isWritten=1;
					p.x=display.x-8;
					p.y=display.y-52;
					drawnPoints[p.x/8][p.y/8]++; //count +1 for the macrocell containing this pixel
				}
			}
		}
		else{		
			if(display.y >= 283 && display.y <= 315 && display.x >=8 && display.x <= 87 && startGame && !isWritten && !inferenceStarted){//punto in tasto Space
				if(charPos<26*8){ //topbar bound: otherwise the topbar is full
					drawButton(space,Yellow);

					//space operation: writing a whitespace into the topbar
			
					//--TO BE COMPLETED--//
					if(charPos!=0)
							LCD_DrawLine(15+charPos-8, 35, 15+charPos+8-8, 35, White); //delete last cursor
					GUI_Text(15+charPos, 20, (uint8_t *) " ", Black, White,1); //testing space on topbar
					LCD_DrawLine(15+charPos, 35, 15+charPos+8, 35, Black); //cursor
					charPos+=8;
					
					clearPad(); //useful only to see the same response time of the other buttons
					
					drawButton(space,White);
				}
			}
			else{
				if(display.y >= 283 && display.y <= 315 && display.x >=100 && display.x <= 139 && startGame && isWritten &&!inferenceStarted){//punto in tasto Infer
					//wait flag to able
					
					drawButton(infer,Yellow);
					
					inferenceStarted=1;
					//infer operation: compress the matrix and send the final 28x28 matrix to the inference step 
					
					//--TO BE COMPLETED--//
					for(i=0;i<28;i++) //if the counter of the macrocell is greater than threshold, set the final cell to 1, otherwise it would be a 0-cell
						for(j=0;j<28;j++)
							drawnPoints[i][j]=drawnPoints[i][j]>=threshold?1:0; 
					
					#ifdef DEBUG
					showCompression();
					if(charPos!=0)
						LCD_DrawLine(15+charPos-8, 35, 15+charPos+8-8, 35, White); //delete last cursor
					GUI_Text(15+charPos, 20, (uint8_t *) "T", Black, White,1); //testing text on topbar
					LCD_DrawLine(15+charPos, 35, 15+charPos+8, 35, Black); //cursor
					charPos+=8;
					#else
					clearPad(); //here the matix is also cleaned
					#endif
					
					isWritten=0;
					inferenceStarted=0;
					
					
					drawButton(infer,White);
				}
				else{
					if(display.y >= 283 && display.y <= 315 && display.x >=153 && display.x <= 232 && startGame &&!inferenceStarted){//punto in tasto Delete
						//wait flag to able
						
						drawButton(del,Yellow);
						
						if(isWritten){ //delete operation - handwriting on pad, before inference: clear the pad
							clearPad();
							isWritten=0;
						}
						else{ //delete operation - no handwriting on pad, after inference: delete last char printed on the topbar
							//--TO BE COMPLETED--//
							clearPad(); //useful only to see the same response time of the other cases
							if(charPos!=0){
								LCD_DrawLine(15+charPos-8, 35, 15+charPos+8-8, 35, White); //delete last cursor
								GUI_Text(15+charPos-8, 20, (uint8_t *) " ", Black, White,1); //testing text on topbar
								if(charPos!=8){ //otherwise we are going to the first character, no cursor
									LCD_DrawLine(15+charPos-16, 35, 15+charPos-8, 35, Black); //cursor
								}
								charPos-=8;
							}
						}
							
						drawButton(del,White);
					}
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
