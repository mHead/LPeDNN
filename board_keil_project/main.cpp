#include "mbed.h"
#include "GLCD.h"
#include "GLCD.c"
#include "AsciiLib.c"
#include "HzLib.c"
//#include "USBSerial.h"
#include "TouchPanel.h"
#include "DeepNeuralNetwork.h"
 
#define DEBUG 

DeepNeuralNetwork dnn;

const int sample_2[28][28] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    
uint8_t *letter0 = (uint8_t *)"0";
                    uint8_t *letter1 = (uint8_t *)"1";
                    uint8_t *letter2 = (uint8_t *)"2";
                    uint8_t *letter3 = (uint8_t *)"3";
                    uint8_t *letter4 = (uint8_t *)"4";
                    uint8_t *letter5 = (uint8_t *)"5";
                    uint8_t *letter6 = (uint8_t *)"6";
                    uint8_t *letter7 = (uint8_t *)"7";
                    uint8_t *letter8 = (uint8_t *)"8";
                    uint8_t *letter9 = (uint8_t *)"9";
                    
                    uint8_t *letterA = (uint8_t *)"A";
                    uint8_t *letterB = (uint8_t *)"B";
                    uint8_t *letterC = (uint8_t *)"C";
                    uint8_t *letterD = (uint8_t *)"D";
                    uint8_t *letterE = (uint8_t *)"E";
                    uint8_t *letterF = (uint8_t *)"F";
                    uint8_t *letterG = (uint8_t *)"G";
                    uint8_t *letterH = (uint8_t *)"H";
                    uint8_t *letterI = (uint8_t *)"I";
                    uint8_t *letterJ = (uint8_t *)"J";
                    uint8_t *letterK = (uint8_t *)"K";
                    uint8_t *letterL = (uint8_t *)"L";
                    uint8_t *letterM = (uint8_t *)"M";
                    uint8_t *letterN = (uint8_t *)"N";
                    uint8_t *letterO = (uint8_t *)"O";
                    uint8_t *letterP = (uint8_t *)"P";
                    uint8_t *letterQ = (uint8_t *)"Q";
                    uint8_t *letterR = (uint8_t *)"R";
                    uint8_t *letterS = (uint8_t *)"S";
                    uint8_t *letterT = (uint8_t *)"T";
                    uint8_t *letterU = (uint8_t *)"U";
                    uint8_t *letterV = (uint8_t *)"V";
                    uint8_t *letterW = (uint8_t *)"W";
                    uint8_t *letterX = (uint8_t *)"X";
                    uint8_t *letterY = (uint8_t *)"Y";
                    uint8_t *letterZ = (uint8_t *)"Z";
 
//FUNZIONI GIORGIO
void readtouch();
 
//VARIABILI GIORGIO
Coordinate tocco;
int x,y,k,avg_x,avg_y,ready;
 
int startGame=0;
int isWritten=0;
int inferenceStarted=0;
int drawnPoints[28][28];
int threshold = 32;
//USBSerial serial;
 
int charPos;
 
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
void readTouch(void);
 
int main() {
    //LCD_Initialization();
    //TP_Init();
    //TouchPanel_Calibrate();
    
    //LCD_Clear(Blue2);
    
    //clearBar();
    //drawButtons();
    start();
    
    while(1){
        //readTouch();
        wait_us(500);
    }
}
 
/*******************************************************************************
* Function Name  : spaceText
* Description    : 
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
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
* Attention      : None
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
* Attention      : None
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
* Attention      : None
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
* Attention      : None
*******************************************************************************/
void drawButton(button b, uint16_t color){
    int i;
    switch(b){
        case space: //Space Button
            spaceText(8,87,291,8,color); 
            GUI_Text(8, 291, (uint8_t *) "  Space   ", Blue, color,1);
            spaceText(8,87,291+16+8,8,color);
            break;
        case infer: //Infer Button
            for(i=0;i<32;i++){ 
                LCD_DrawLine(100,283+i,139,283+i,color);
            }
            drawTriangle(112,289,10);
            break;
        case del: //Delete Button
            spaceText(153,232,291,8,color); 
            GUI_Text(153, 291, (uint8_t *) "  Delete  ", Blue, color,1);
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
* Attention      : None
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
* Attention      : None
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
* Attention      : None
*******************************************************************************/
void start(){
    //disable_timer(0);
    //reset_timer(0);
    
    clearPad();
    GUI_Text(22, 90, (uint8_t *) "Touch to", Black, White, 3);
    GUI_Text(32, 135, (uint8_t *)" start", Black, White, 3);
    GUI_Text(28, 185, (uint8_t *) "writing!", Black, White, 3);
    
    startGame=0;
    isWritten=0;
    inferenceStarted=0;
    //enable_timer(0);
    
    int prediction = dnn.inference(drawnPoints);
    uint8_t *letter;
                    if (prediction == 0)
                        letter = letter0;
                    else if (prediction == 1)
                        letter = letter1;
                    else if (prediction == 2)
                        letter = letter2;
                    else if (prediction == 3)
                        letter = letter3;
                    else if (prediction == 4)
                        letter = letter4;
                    else if (prediction == 5)
                        letter = letter5;
                    else if (prediction == 6)
                        letter = letter6;
                    else if (prediction == 7)
                        letter = letter7;
                    else if (prediction == 8)
                        letter = letter8;
                    else if (prediction == 9)
                        letter = letter9;
                    else if (prediction == 10)
                        letter = letterA;
                    else if (prediction == 11)
                        letter = letterB;
                    else if (prediction == 12)
                        letter = letterC;
                    else if (prediction == 13)
                        letter = letterD;
                    else if (prediction == 14)
                        letter = letterE;
                    else if (prediction == 15)
                        letter = letterF;
                    else if (prediction == 16)
                        letter = letterG;
                    else if (prediction == 17)
                        letter = letterH;
                    else if (prediction == 18)
                        letter = letterI;
                    else if (prediction == 19)
                        letter = letterJ;
                    else if (prediction == 20)
                        letter = letterK;
                    else if (prediction == 21)
                        letter = letterL;
                    else if (prediction == 22)
                        letter = letterM;
                    else if (prediction == 23)
                        letter = letterN;
                    else if (prediction == 24)
                        letter = letterO;
                    else if (prediction == 25)
                        letter = letterP;
                    else if (prediction == 26)
                        letter = letterQ;
                    else if (prediction == 27)
                        letter = letterR;
                    else if (prediction == 28)
                        letter = letterS;
                    else if (prediction == 29)
                        letter = letterT;
                    else if (prediction == 30)
                        letter = letterU;
                    else if (prediction == 31)
                        letter = letterV;
                    else if (prediction == 32)
                        letter = letterW;
                    else if (prediction == 33)
                        letter = letterX;
                    else if (prediction == 34)
                        letter = letterY;
                    else if (prediction == 35)
                        letter = letterZ;
                    
                    GUI_Text(15+charPos, 20, letter, Black, White,1); //testing text on topbar
                    LCD_DrawLine(15+charPos, 35, 15+charPos+8, 35, Black); //cursor
                    charPos+=8;
    
    return;
}
 
// FUNZIONI GIORGIO
 
void readtouch(){
    if(Read_X()!=4095){
        wait(0.1);
        for(k=0; k<400;k++){
            x=Read_Y();
            y=Read_X();
            x=(x-300)*240/3900;
            y=(y-220)*320/3800;
            avg_x+=x;
            avg_y+=y;
        }
        avg_x=avg_x/400;
        avg_y=avg_y/400;
        tocco.x=avg_x+10;
        tocco.y=avg_y+19;
        ready=1;
    }
    else
        ready=0;
}
 
void readTouch(){
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
                        clearPad();//clear to delete the testing result printed on screen   before      
                    #endif
                    isWritten=1;
                    p.x=display.x-8;
                    p.y=display.y-52;
                    for(i=-1;i<2;i++)
                        for(j=-1;j<2;j++){
                            if((p.x+i)>=0&&(p.y+j)>=0&&(p.x+i)<224&&(p.y+j)<224){
                                TP_DrawPoint(display.x+i,display.y+j);
                                drawnPoints[(p.x+i)/8][(p.y+j)/8]++; //count +1 for the macrocell containing this pixel
                                }
                        }
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
                    GUI_Text(15+charPos, 20, (uint8_t *)" ", Black, White,1); //testing space on topbar
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
                            
                    
                    
                    
                    uint8_t *letter;
                    
                    
                    //#ifdef DEBUG
                    showCompression();
                    if(charPos!=0)
                        LCD_DrawLine(15+charPos-8, 35, 15+charPos+8-8, 35, White); //delete last cursor
                    
                    //#endif
                    
                    int prediction = dnn.inference(drawnPoints);
                    if (prediction == 0)
                        letter = letter0;
                    else if (prediction == 1)
                        letter = letter1;
                    else if (prediction == 2)
                        letter = letter2;
                    else if (prediction == 3)
                        letter = letter3;
                    else if (prediction == 4)
                        letter = letter4;
                    else if (prediction == 5)
                        letter = letter5;
                    else if (prediction == 6)
                        letter = letter6;
                    else if (prediction == 7)
                        letter = letter7;
                    else if (prediction == 8)
                        letter = letter8;
                    else if (prediction == 9)
                        letter = letter9;
                    else if (prediction == 10)
                        letter = letterA;
                    else if (prediction == 11)
                        letter = letterB;
                    else if (prediction == 12)
                        letter = letterC;
                    else if (prediction == 13)
                        letter = letterD;
                    else if (prediction == 14)
                        letter = letterE;
                    else if (prediction == 15)
                        letter = letterF;
                    else if (prediction == 16)
                        letter = letterG;
                    else if (prediction == 17)
                        letter = letterH;
                    else if (prediction == 18)
                        letter = letterI;
                    else if (prediction == 19)
                        letter = letterJ;
                    else if (prediction == 20)
                        letter = letterK;
                    else if (prediction == 21)
                        letter = letterL;
                    else if (prediction == 22)
                        letter = letterM;
                    else if (prediction == 23)
                        letter = letterN;
                    else if (prediction == 24)
                        letter = letterO;
                    else if (prediction == 25)
                        letter = letterP;
                    else if (prediction == 26)
                        letter = letterQ;
                    else if (prediction == 27)
                        letter = letterR;
                    else if (prediction == 28)
                        letter = letterS;
                    else if (prediction == 29)
                        letter = letterT;
                    else if (prediction == 30)
                        letter = letterU;
                    else if (prediction == 31)
                        letter = letterV;
                    else if (prediction == 32)
                        letter = letterW;
                    else if (prediction == 33)
                        letter = letterX;
                    else if (prediction == 34)
                        letter = letterY;
                    else if (prediction == 35)
                        letter = letterZ;
                    
                    GUI_Text(15+charPos, 20, letter, Black, White,1); //testing text on topbar
                    LCD_DrawLine(15+charPos, 35, 15+charPos+8, 35, Black); //cursor
                    charPos+=8;
                    
                    /*
                    for(i=0;i<28;i++) {
                        for(j=0;j<28;j++) {
                            serial.printf("%d",static_cast<int>(drawnPoints[j][i]));
                        }
                    }
                    */
                    
                    #ifndef DEBUG
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
                                GUI_Text(15+charPos-8, 20, (uint8_t *)" ", Black, White,1); //testing text on topbar
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
  return;
}