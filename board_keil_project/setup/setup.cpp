/* Includes ------------------------------------------------------------------*/
#include "setup.h"

int startGame=0;
int isWritten=0;
int inferenceStarted=0;
uint8_t drawnPoints[28][28];
int threshold = 32;

/*******************************************************************************
* Function Name  : spaceText
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void spaceText(int x1, int x2, int yText, int spessore, uint16_t color){ //Spazio di un unico colore
	int i;
	for(i=spessore;i>0;i--){
		LCD_DrawLine(x1,yText-i,x2,yText-i,color);
	}
	return;
}

/*******************************************************************************
* Function Name  : clearPad
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void clearPad(){
	int i,j;
	for(i=0;i<224;i++){
		LCD_DrawLine(8,52+i,232,52+i,White);
	}
	for(i=0;i<28;i++) //also clear the matrix
		for(j=0;j<28;j++)
			drawnPoints[i][j]=0;
	
	return;
}

/*******************************************************************************
* Function Name  : showCompression
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void showCompression(){
	int i,j;
	for(i=0;i<224;i++){ //clean the pad
		LCD_DrawLine(8,52+i,232,52+i,White);
	}
	for(i=0;i<28;i++)
		for(j=0;j<28;j++)
			if(drawnPoints[i][j]==1)
				LCD_SetPoint(i+110,j+150,Black);  
	
	return;
}

/*******************************************************************************
* Function Name  : clearBar
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void clearBar(){
	int i;
	for(i=0;i<32;i++){
		LCD_DrawLine(8,10+i,232,10+i,White);
	}
	return;
}

/*******************************************************************************
* Function Name  : drawButton
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void drawButton(button b, uint16_t color){
	int i;
	switch(b){
		case space: //Space Button
			spaceText(8,87,291,8,color); 
			GUI_Text(8, 291, "  Space   ", Blue, color,1);
			spaceText(8,87,291+16+8,8,color);
			break;
		case infer:	//Infer Button
			for(i=0;i<32;i++){ 
				LCD_DrawLine(100,283+i,139,283+i,color);
			}
			drawTriangle(112,289,10);
			break;
		case del: //Delete Button
			spaceText(153,232,291,8,color); 
			GUI_Text(153, 291, "  Delete  ", Blue, color,1);
			spaceText(153,232,291+16+8,8,color);
			break;
		default:
			break;
	}
	return;
}

/*******************************************************************************
* Function Name  : drawButtons
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void drawButtons(){
	drawButton(space,White);
	drawButton(infer,White);
	drawButton(del,White);
	return;
}

/*******************************************************************************
* Function Name  : drawTriangle
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void drawTriangle(int posX, int posY, int lungMax){
	int i;
	uint16_t color=Green2;
	for(i=0;i<lungMax;i++){ //Direction EAST
			LCD_DrawLine(posX+5,posY+i+1,posX+5+i,posY+i+1,color);
	}
	for(i=0;i<lungMax-1;i++){
			LCD_DrawLine(posX+5,posY+lungMax+i+1,posX+5+(lungMax-2)-i,posY+lungMax+i+1,color);
	}
}

/*******************************************************************************
* Function Name  : start
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void start(){
	disable_timer(0);
	reset_timer(0);
	
	clearPad();
	GUI_Text(22, 90, "Touch to", Black, White, 3);
	GUI_Text(32, 135, " start", Black, White, 3);
	GUI_Text(28, 185, "writing!", Black, White, 3);
	
	startGame=0;
	isWritten=0;
	inferenceStarted=0;
	enable_timer(0);
	
	return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
