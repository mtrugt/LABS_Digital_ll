//Electronica Digital
//Laboratorio 5
//Marco Trujillo ;18069

//Basado en el ejemplo de Pablo Mazariegos
//Las librerias utilizadas son las adaptadas por Pablo Mazariegos 

//Libreria
#include <SPI.h>
#include <SD.h>


//Creacion de varibles
int img;
File root;
File myFile;

//Configuracion
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  SPI.setModule(0);
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  Serial.println("La Memoria posee los siguientes archivos:");
  root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("Si desea visualizar alguno de los elementos escriba lo siguiente:");
  Serial.println("a para abrir calaca.txt");
  Serial.println("b para abrir estrella.txt");
  Serial.println("c para abrir corazon.txt");
  
}

//Loop principal
void loop(){
 //Revisar si hay un dato disponible  
if (Serial.available()>0){
  img = Serial.read();}
  
if (img == 'a'){
    myFile = SD.open("calaca.txt"); 
    if (myFile){
      while (myFile.available()){
        Serial.write(myFile.read());
      }
      myFile.close();
    }
    else{
      Serial.println("error al abrir el .txt");
    }
  }

else if (img == 'b'){
    myFile = SD.open("estrella.txt"); 
    if (myFile){
      while (myFile.available()){
        Serial.write(myFile.read());
      }
      myFile.close();
    }
    else{
      Serial.println("error al abrir el .txt");
    }
  }

  
else if (img == 'c'){
    myFile = SD.open("Corazon.txt"); 
    if (myFile){
      while (myFile.available()){
        Serial.write(myFile.read());
      }
      myFile.close();
    }
    else{
      Serial.println("error al abrir el .txt");
    }
  }
}

void printDirectory(File dir, int numTabs) {
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
