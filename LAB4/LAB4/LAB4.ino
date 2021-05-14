//Marco Trujillo
//18069
//Digital 2, LAB 4


//Definir variables y pines
const char GREEN = 39;
const char RED = 30;
const char BLUE = 40;

char player1 = 0;
char player2 = 0;

char check1 = 0;
char check2 = 0;
char i = 0;

//Leds player1
int led1 = PB_5;
int led2 = PB_0;
int led3 = PB_1;
int led4 = PE_4;
int led5 = PE_5;
int led6 = PB_4;
int led7 = PA_5;
int led8 = PA_6;

// Leds player 2
int led9 = 38;
int led10 = 37;
int led11 = 36;
int led12 = 35;
int led13 = 34;
int led14 = 33;
int led15 = 32;
int led16 = 11;


void setup() {
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);

  //definir pines como salida
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(led10, OUTPUT);
  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led13, OUTPUT);
  pinMode(led14, OUTPUT);
  pinMode(led15, OUTPUT);
  pinMode(led16, OUTPUT);

  //botones como pull ups
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);

}

void loop() {
  i = 0;
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  //Secuencia del semaforo
  while(i != 1){
    if (digitalRead(PUSH1) == 0 || digitalRead(PUSH2) == 0 ){
      digitalWrite(RED, HIGH);
      delay(1000);
      digitalWrite(GREEN, HIGH);
      delay(1000);
      digitalWrite(RED, LOW);

      i = 1;
    }
  }

//Juego
  i = 0;
  player1 = 0;
  player2 = 0;
  while (i != 1){

   if (check1 != 0 && digitalRead(PUSH1) == 1){
           check1 = 0;
          }
                
   else if (check2 != 0 && digitalRead(PUSH2) == 1){
            check2 = 0;
          }
                
   else if (check1 == 0 && digitalRead(PUSH1) == 0){
        player1 = player1 + 1;
        check1 = 1;
        player1leds();               
       }
                
   else if (check2 == 0 && digitalRead(PUSH2) == 0){
        player2 = player2 + 1;
        check2 = 1;
        player2leds();             
       }

   if (player1 == 8 || player2 == 8){
    i = 1;
   }
  }
  if(player1 == 8){
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
    delay(3000);
  }

  else if(player2 == 8){
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
    digitalWrite(RED, HIGH);
    delay(3000);
  }
  player1 = 0;
  player2 = 0;
  player1leds();
  player2leds();
}

void player1leds(void){
  switch (player1) {
  case 0:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    break;
  case 1:
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    break;
  case 2:
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    break;
  case 3:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    break;
  case 4:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    break;
  case 5:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    break;
  case 6:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, HIGH);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    break;
  case 7:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, HIGH);
    digitalWrite(led8, LOW);
    break;
  case 8:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, HIGH);
    break;
  }
}

void player2leds(void){
  switch(player2) {
  case 0:
    digitalWrite(led9, LOW);
    digitalWrite(led10, LOW);
    digitalWrite(led11, LOW);
    digitalWrite(led12, LOW);
    digitalWrite(led13, LOW);
    digitalWrite(led14, LOW);
    digitalWrite(led15, LOW);
    digitalWrite(led16, LOW);
    break;
  case 1:
    digitalWrite(led9, HIGH);
    digitalWrite(led10, LOW);
    digitalWrite(led11, LOW);
    digitalWrite(led12, LOW);
    digitalWrite(led13, LOW);
    digitalWrite(led14, LOW);
    digitalWrite(led15, LOW);
    digitalWrite(led16, LOW);
    break;
  case 2:
    digitalWrite(led9, LOW);
    digitalWrite(led10, HIGH);
    digitalWrite(led11, LOW);
    digitalWrite(led12, LOW);
    digitalWrite(led13, LOW);
    digitalWrite(led14, LOW);
    digitalWrite(led15, LOW);
    digitalWrite(led16, LOW);
    break;
  case 3:
    digitalWrite(led9, LOW);
    digitalWrite(led10, LOW);
    digitalWrite(led11, HIGH);
    digitalWrite(led12, LOW);
    digitalWrite(led13, LOW);
    digitalWrite(led14, LOW);
    digitalWrite(led15, LOW);
    digitalWrite(led16, LOW);
    break;
  case 4:
    digitalWrite(led9, LOW);
    digitalWrite(led10, LOW);
    digitalWrite(led11, LOW);
    digitalWrite(led12, HIGH);
    digitalWrite(led13, LOW);
    digitalWrite(led14, LOW);
    digitalWrite(led15, LOW);
    digitalWrite(led16, LOW);
    break;
  case 5:
    digitalWrite(led9, LOW);
    digitalWrite(led10, LOW);
    digitalWrite(led11, LOW);
    digitalWrite(led12, LOW);
    digitalWrite(led13, HIGH);
    digitalWrite(led14, LOW);
    digitalWrite(led15, LOW);
    digitalWrite(led16, LOW);
    break;
  case 6:
    digitalWrite(led9, LOW);
    digitalWrite(led10, LOW);
    digitalWrite(led11, LOW);
    digitalWrite(led12, LOW);
    digitalWrite(led13, LOW);
    digitalWrite(led14, HIGH);
    digitalWrite(led15, LOW);
    digitalWrite(led16, LOW);
    break;
  case 7:
    digitalWrite(led9, LOW);
    digitalWrite(led10, LOW);
    digitalWrite(led11, LOW);
    digitalWrite(led12, LOW);
    digitalWrite(led13, LOW);
    digitalWrite(led14, LOW);
    digitalWrite(led15, HIGH);
    digitalWrite(led16, LOW);
    break;
  case 8:
    digitalWrite(led9, LOW);
    digitalWrite(led10, LOW);
    digitalWrite(led11, LOW);
    digitalWrite(led12, LOW);
    digitalWrite(led13, LOW);
    digitalWrite(led14, LOW);
    digitalWrite(led15, LOW);
    digitalWrite(led16, HIGH);
    break;
  }
}
