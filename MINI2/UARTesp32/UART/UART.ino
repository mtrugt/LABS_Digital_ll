// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.

//#include "config.h"
#define RXD2 16
#define TXD2 17
/************************ Example Starts Here *******************************/

#define RXD2 16
#define TXD2 17
 void setup() {
   Serial.begin(115200);
   Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
   delay(1000);
   Serial.println("Loopback program started");
 }
 void loop() {
   if(Serial.available()){
     Serial.write("-");
     Serial2.write(Serial.read());  
   }
   if(Serial2.available()){
     Serial.write(".");
     Serial.write(Serial2.read());  
   }
 }
