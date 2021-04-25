//***************************************************************************************************************************************
/* Librería para el uso de la pantalla ILI9341 en modo 8 bits
 * Basado en el código de martinayotte - https://www.stm32duino.com/viewtopic.php?t=637
 * Adaptación, migración y creación de nuevas funciones: Pablo Mazariegos y José Morales
 * Con ayuda de: José Guerra
 * IE3027: Electrónica Digital 2 - 2019
 */
//***************************************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "bitmaps.h"
#include "font.h"
#include "lcd_registers.h"

#define LCD_RST PD_0
#define LCD_CS PD_1
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};  

int anim;
int posy;
int posx;
int i;
int j;
char k;
char t;
char check1;
char check2;
char changepos;

//***************************************************************************************************************************************
// Functions Prototypes
//***************************************************************************************************************************************
void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void LCD_DATA(uint8_t data);
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Clear(unsigned int c);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void LCD_Print(String text, int x, int y, int fontSize, int color, int background);

void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);


extern uint8_t fondo[];
extern uint8_t middle[];
extern uint8_t borde[];
extern uint8_t enemy[]; //estatico = 0 spawn = 6-9 despawn = 1-5
//***************************************************************************************************************************************
// Inicialización
//***************************************************************************************************************************************
void setup() {
  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  Serial.begin(9600);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  Serial.println("Inicio");
  LCD_Init();

  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  
  //LCD_Bitmap(0, 0, 320, 240, fondo);

  //FillRect(0, 0, 319, 206, 0x421b);
  //String text1 = "Super Mario World!";
  //LCD_Print(text1, 20, 100, 2, 0xffff, 0x421b);
//LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);
    
  //LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
  //LCD_Bitmap(0, 0, 320, 240, fondo);
  
  //for(int x = 0; x <319; x++){
    //LCD_Bitmap(x, 52, 16, 16, tile2);
    //LCD_Bitmap(x, 68, 16, 16, tile);
    
    //LCD_Bitmap(x, 207, 16, 16, tile);
    //LCD_Bitmap(x, 223, 16, 16, tile);
    //x += 15;
 //}
  
}
//***************************************************************************************************************************************
// Loop Infinito
//***************************************************************************************************************************************
void loop() {
  //DESPLIEGUE PANTALLA DE CARGA
  LCD_Bitmap(0, 0, 320, 240, fondo);
  while(digitalRead(PUSH2)== 1 && digitalRead(PUSH1)== 1){
  LCD_Bitmap(60, 182, 200, 13, text1);
  delay(100);
  LCD_Bitmap(60, 182, 200, 13, text2);
  delay(100);
  }

  //DESPLIEGUE INSTRUCCIONES
  LCD_Clear(0x605F);
  LCD_Print("How to play?" , 60, 30, 2,   0xFFFF, 0x605F);
  LCD_Bitmap(60, 70, 186, 43, btns);
  LCD_Print("Move to the left with SW1" , 20, 130, 1,   0xFFFF, 0x605F);
  LCD_Print("Move to the right with SW2" , 20, 150, 1,   0xFFFF, 0x605F);
  LCD_Print("Have Fun :)" , 60, 190, 2,   0xFFFF, 0x605F);
  delay(3000);

  LCD_Clear(0x605F);

  posy = 0;
  posx = 0;
//while(1){
//  i = 0;
//  while(i != 7){
//     LCD_Sprite(150, 20, 9, 48, middle, 7, i, 0, 0);
//     delay(1000);
//     i = i + 1;
//   }
//}

//Generar escenario de juego
LCD_Bitmap(0, 0, 320, 240, fondo);
FillRect(170, 0, 320-170, 240, 0x6B4D);
FillRect(140, 35, 20, 20, 0x1C59);

//Posiciones del jugador
//LCD_Bitmap(182, 170, 18, 25, player);
//LCD_Bitmap(230, 170, 18, 25, player);
//LCD_Bitmap(280, 170, 18, 25, player);

int posplayer = 3;
int coin = 1;
check1 = 0;
check2 = 0;
while(coin){

  if (check1 != 0 && digitalRead(PUSH1) == 1){
           check1 = 0;
          }
                
  if (check2 != 0 && digitalRead(PUSH2) == 1){
            check2 = 0;
          }
                
  if (check1 == 0 && digitalRead(PUSH1) == 0 && posplayer != 1){
        posplayer = posplayer - 1;
        check1 = 1;
        changepos = 1; //bandera de cambio de posicion               
       }
                
  if (check2 == 0 && digitalRead(PUSH2) == 0 && posplayer != 3){
        posplayer = posplayer + 1;
        check2 = 1;
        changepos = 1; //bandera de cambio de posicion              
       }


  //Animacion, posicion del jugador
  if (changepos = 1){
   switch(posplayer){
    case 1:
      LCD_Bitmap(182, 170, 18, 25, player);
      FillRect(230, 170, 18, 25, 0x6B4D);
      FillRect(280, 170, 18, 25, 0x6B4D);
    break;

    case 2:
      LCD_Bitmap(230, 170, 18, 25, player);
      FillRect(182, 170, 18, 25, 0x6B4D);
      FillRect(280, 170, 18, 25, 0x6B4D);
    break;

    case 3:
      LCD_Bitmap(280, 170, 18, 25, player);
      FillRect(182, 170, 18, 25, 0x6B4D);
      FillRect(230, 170, 18, 25, 0x6B4D);
    break;
   }
   changepos = 0;
  }

  //animacion de la carretera
  i = 0;
  while (i != 11){
    j = 0;
    posy = 0;
    while (j != 5){
      LCD_Sprite(210, posy, 9, 48, middle, 11, i, 0, 0);
      LCD_Sprite(260, posy, 9, 48, middle, 11, i, 0, 0);
      if (i < 8){
        LCD_Sprite(160, posy, 14, 48, borde, 8, i, 0, 0);
        LCD_Sprite(320-14, posy, 14, 48, borde, 8, i, 1, 0);
      }
      else{    
        LCD_Sprite(160, posy, 14, 48, borde, 8, i-8, 0, 0);
        LCD_Sprite(320-14, posy, 14, 48, borde, 8, i-8, 1, 0);
      }
      
      posy = posy + 48;
      j = j + 1;
    }
    i = i + 1;
  }

  while (i != 11){
    j = 0;
    posy = 0;
    while (j != 5){
      LCD_Sprite(210, posy, 9, 48, middle, 11, i, 0, 0);
      LCD_Sprite(260, posy, 9, 48, middle, 11, i, 0, 0);
      if (i < 8){
        LCD_Sprite(160, posy, 14, 48, borde, 8, i, 0, 0);
        LCD_Sprite(320-14, posy, 14, 48, borde, 8, i, 1, 0);
      }
      else{    
        LCD_Sprite(160, posy, 14, 48, borde, 8, i-8, 0, 0);
        LCD_Sprite(320-14, posy, 14, 48, borde, 8, i-8, 1, 0);
      }
      
      posy = posy + 48;
      j = j + 1;
    }
    i = i + 1;
  }

  
}
  
 /* for(int x = 0; x <320-32; x++){
    delay(15);
    int anim2 = (x/35)%2;
    
    LCD_Sprite(x,100,16,24,planta,2,anim2,0,1);
    V_line( x -1, 100, 24, 0x421b);
    
    //LCD_Bitmap(x, 100, 32, 32, prueba);
    
    int anim = (x/11)%8;
    

    int anim3 = (x/11)%4;
    
    LCD_Sprite(x, 20, 16, 32, mario,8, anim,1, 0);
    V_line( x -1, 20, 32, 0x421b);
 
    //LCD_Sprite(x,100,32,32,bowser,4,anim3,0,1);
    //V_line( x -1, 100, 32, 0x421b);
 
 
    LCD_Sprite(x, 140, 16, 16, enemy,2, anim2,1, 0);
    V_line( x -1, 140, 16, 0x421b);
  
    LCD_Sprite(x, 175, 16, 32, luigi,8, anim,1, 0);
    V_line( x -1, 175, 32, 0x421b);
  }
  for(int x = 320-32; x >0; x--){
    delay(5);
    int anim = (x/11)%8;
    int anim2 = (x/11)%2;
    
    LCD_Sprite(x,100,16,24,planta,2,anim2,0,0);
    V_line( x + 16, 100, 24, 0x421b);
    
    //LCD_Bitmap(x, 100, 32, 32, prueba);
    
    //LCD_Sprite(x, 140, 16, 16, enemy,2, anim2,0, 0);
    //V_line( x + 16, 140, 16, 0x421b);
    
    //LCD_Sprite(x, 175, 16, 32, luigi,8, anim,0, 0);
    //V_line( x + 16, 175, 32, 0x421b);

    //LCD_Sprite(x, 20, 16, 32, mario,8, anim,0, 0);
    //V_line( x + 16, 20, 32, 0x421b);
  } 
*/
};
//***************************************************************************************************************************************
// Función para inicializar LCD
//***************************************************************************************************************************************
void LCD_Init(void) {
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_WR, OUTPUT);
  pinMode(LCD_RD, OUTPUT);
  for (uint8_t i = 0; i < 8; i++){
    pinMode(DPINS[i], OUTPUT);
  }
  //****************************************
  // Secuencia de Inicialización
  //****************************************
  digitalWrite(LCD_CS, HIGH);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_RST, HIGH);
  delay(5);
  digitalWrite(LCD_RST, LOW);
  delay(20);
  digitalWrite(LCD_RST, HIGH);
  delay(150);
  digitalWrite(LCD_CS, LOW);
  //****************************************
  LCD_CMD(0xE9);  // SETPANELRELATED
  LCD_DATA(0x20);
  //****************************************
  LCD_CMD(0x11); // Exit Sleep SLEEP OUT (SLPOUT)
  delay(100);
  //****************************************
  LCD_CMD(0xD1);    // (SETVCOM)
  LCD_DATA(0x00);
  LCD_DATA(0x71);
  LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0xD0);   // (SETPOWER) 
  LCD_DATA(0x07);
  LCD_DATA(0x01);
  LCD_DATA(0x08);
  //****************************************
  LCD_CMD(0x36);  // (MEMORYACCESS)
  LCD_DATA(0x40|0x80|0x20|0x08); // LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0x3A); // Set_pixel_format (PIXELFORMAT)
  LCD_DATA(0x05); // color setings, 05h - 16bit pixel, 11h - 3bit pixel
  //****************************************
  LCD_CMD(0xC1);    // (POWERCONTROL2)
  LCD_DATA(0x10);
  LCD_DATA(0x10);
  LCD_DATA(0x02);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC0); // Set Default Gamma (POWERCONTROL1)
  LCD_DATA(0x00);
  LCD_DATA(0x35);
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC5); // Set Frame Rate (VCOMCONTROL1)
  LCD_DATA(0x04); // 72Hz
  //****************************************
  LCD_CMD(0xD2); // Power Settings  (SETPWRNORMAL)
  LCD_DATA(0x01);
  LCD_DATA(0x44);
  //****************************************
  LCD_CMD(0xC8); //Set Gamma  (GAMMASET)
  LCD_DATA(0x04);
  LCD_DATA(0x67);
  LCD_DATA(0x35);
  LCD_DATA(0x04);
  LCD_DATA(0x08);
  LCD_DATA(0x06);
  LCD_DATA(0x24);
  LCD_DATA(0x01);
  LCD_DATA(0x37);
  LCD_DATA(0x40);
  LCD_DATA(0x03);
  LCD_DATA(0x10);
  LCD_DATA(0x08);
  LCD_DATA(0x80);
  LCD_DATA(0x00);
  //****************************************
  LCD_CMD(0x2A); // Set_column_address 320px (CASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x3F);
  //****************************************
  LCD_CMD(0x2B); // Set_page_address 480px (PASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0xE0);
//  LCD_DATA(0x8F);
  LCD_CMD(0x29); //display on 
  LCD_CMD(0x2C); //display on

  LCD_CMD(ILI9341_INVOFF); //Invert Off
  delay(120);
  LCD_CMD(ILI9341_SLPOUT);    //Exit Sleep
  delay(120);
  LCD_CMD(ILI9341_DISPON);    //Display on
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar comandos a la LCD - parámetro (comando)
//***************************************************************************************************************************************
void LCD_CMD(uint8_t cmd) {
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = cmd;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar datos a la LCD - parámetro (dato)
//***************************************************************************************************************************************
void LCD_DATA(uint8_t data) {
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = data;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para definir rango de direcciones de memoria con las cuales se trabajara (se define una ventana)
//***************************************************************************************************************************************
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  LCD_CMD(0x2a); // Set_column_address 4 parameters
  LCD_DATA(x1 >> 8);
  LCD_DATA(x1);   
  LCD_DATA(x2 >> 8);
  LCD_DATA(x2);   
  LCD_CMD(0x2b); // Set_page_address 4 parameters
  LCD_DATA(y1 >> 8);
  LCD_DATA(y1);   
  LCD_DATA(y2 >> 8);
  LCD_DATA(y2);   
  LCD_CMD(0x2c); // Write_memory_start
}
//***************************************************************************************************************************************
// Función para borrar la pantalla - parámetros (color)
//***************************************************************************************************************************************
void LCD_Clear(unsigned int c){  
  unsigned int x, y;
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);   
  SetWindows(0, 0, 319, 239); // 479, 319);
  for (x = 0; x < 320; x++)
    for (y = 0; y < 240; y++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
    }
  digitalWrite(LCD_CS, HIGH);
} 
//***************************************************************************************************************************************
// Función para dibujar una línea horizontal - parámetros ( coordenada x, cordenada y, longitud, color)
//*************************************************************************************************************************************** 
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + x;
  SetWindows(x, y, l, y);
  j = l;// * 2;
  for (i = 0; i < l; i++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea vertical - parámetros ( coordenada x, cordenada y, longitud, color)
//*************************************************************************************************************************************** 
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i,j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + y;
  SetWindows(x, y, x, l);
  j = l; //* 2;
  for (i = 1; i <= j; i++) {
    LCD_DATA(c >> 8); 
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);  
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
/*void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  unsigned int i;
  for (i = 0; i < h; i++) {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
}
*/

void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 
  
  unsigned int x2, y2;
  x2 = x+w;
  y2 = y+h;
  SetWindows(x, y, x2-1, y2-1);
  unsigned int k = w*h*2-1;
  unsigned int i, j;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      LCD_DATA(c >> 8);
      LCD_DATA(c);
      
      //LCD_DATA(bitmap[k]);    
      k = k - 2;
     } 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar texto - parámetros ( texto, coordenada x, cordenada y, color, background) 
//***************************************************************************************************************************************
void LCD_Print(String text, int x, int y, int fontSize, int color, int background) {
  int fontXSize ;
  int fontYSize ;
  
  if(fontSize == 1){
    fontXSize = fontXSizeSmal ;
    fontYSize = fontYSizeSmal ;
  }
  if(fontSize == 2){
    fontXSize = fontXSizeBig ;
    fontYSize = fontYSizeBig ;
  }
  
  char charInput ;
  int cLength = text.length();
  Serial.println(cLength,DEC);
  int charDec ;
  int c ;
  int charHex ;
  char char_array[cLength+1];
  text.toCharArray(char_array, cLength+1) ;
  for (int i = 0; i < cLength ; i++) {
    charInput = char_array[i];
    Serial.println(char_array[i]);
    charDec = int(charInput);
    digitalWrite(LCD_CS, LOW);
    SetWindows(x + (i * fontXSize), y, x + (i * fontXSize) + fontXSize - 1, y + fontYSize );
    long charHex1 ;
    for ( int n = 0 ; n < fontYSize ; n++ ) {
      if (fontSize == 1){
        charHex1 = pgm_read_word_near(smallFont + ((charDec - 32) * fontYSize) + n);
      }
      if (fontSize == 2){
        charHex1 = pgm_read_word_near(bigFont + ((charDec - 32) * fontYSize) + n);
      }
      for (int t = 1; t < fontXSize + 1 ; t++) {
        if (( charHex1 & (1 << (fontXSize - t))) > 0 ) {
          c = color ;
        } else {
          c = background ;
        }
        LCD_DATA(c >> 8);
        LCD_DATA(c);
      }
    }
    digitalWrite(LCD_CS, HIGH);
  }
}
//***************************************************************************************************************************************
// Función para dibujar una imagen a partir de un arreglo de colores (Bitmap) Formato (Color 16bit R 5bits G 6bits B 5bits)
//***************************************************************************************************************************************
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]){  
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 
  
  unsigned int x2, y2;
  x2 = x+width;
  y2 = y+height;
  SetWindows(x, y, x2-1, y2-1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      //LCD_DATA(bitmap[k]);    
      k = k + 2;
     } 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una imagen sprite - los parámetros columns = número de imagenes en el sprite, index = cual desplegar, flip = darle vuelta
//***************************************************************************************************************************************
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset){
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 

  unsigned int x2, y2;
  x2 =   x+width;
  y2=    y+height;
  SetWindows(x, y, x2-1, y2-1);
  int k = 0;
  int ancho = ((width*columns));
  if(flip){
  for (int j = 0; j < height; j++){
      k = (j*(ancho) + index*width -1 - offset)*2;
      k = k+width*2;
     for (int i = 0; i < width; i++){
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      k = k - 2;
     } 
  }
  }else{
     for (int j = 0; j < height; j++){
      k = (j*(ancho) + index*width + 1 + offset)*2;
     for (int i = 0; i < width; i++){
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      k = k + 2;
     } 
  }
    
    
    }
  digitalWrite(LCD_CS, HIGH);
}
