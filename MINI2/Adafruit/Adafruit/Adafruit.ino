// Adafruit IO Digital Output Example
// Tutorial Link: https://learn.adafruit.com/adafruit-io-basics-digital-output
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
#include "config.h"

/************************ Example Starts Here *******************************/
int count = 0;
int dat = 0;
int humedad = 0;

// digital pin 5
#define LED_PIN 2

// set up the 'digital' feed
AdafruitIO_Feed *LED1Feed = io.feed("LED1");
AdafruitIO_Feed *humedadfeed = io.feed("counter");

void setup() {
  
  pinMode(LED_PIN, OUTPUT);
  
  // start the serial connection
  Serial.begin(9600);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'digital' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  LED1Feed->onMessage(handleMessage);

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  LED1Feed->get();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  humedad = random(0,100);
  Serial.print("sending -> ");
  Serial.println(humedad);
  humedadfeed->save(humedad);
  delay(3000);

  

}

// this function is called whenever an 'digital' feed message
// is received from Adafruit IO. it was attached to
// the 'digital' feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->toString());

  if(data->toString() == "ON")
    digitalWrite(LED_PIN, HIGH);
  else
    digitalWrite(LED_PIN, LOW);;


  digitalWrite(LED_PIN, data->toPinLevel());
}
