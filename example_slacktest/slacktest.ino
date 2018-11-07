#include "Adafruit_NeoPixel.h"
#include "config.h"
#define LEDpin D5
Adafruit_NeoPixel strip = Adafruit_NeoPixel(18, LEDpin, NEO_GRB + NEO_KHZ800); //getal = aantal LED's

// set up the 'colourpicker' feed
AdafruitIO_Feed *color = io.feed("color.analog");
AdafruitIO_Feed *slacktest = io.feed("slacktest");

void setup() {
 Serial.begin(115200);
 // set up strip and lichtsensor
 pinMode(A0, INPUT_PULLUP);
pinMode(LEDpin, OUTPUT);

 // set up led pin as an analog output
// #if defined(ARDUINO_ARCH_ESP32)
  // // ESP32 pinMode()
//   ledcAttachPin(LED_PIN, 1);
 //  ledcSetup(1, 1200, 8);
// #else
   //pinMode(D5, OUTPUT);
// #endif

 // wait for serial monitor to open
 while(! Serial);

 // connect to io.adafruit.com
 Serial.print("Connecting to Adafruit IO");
 io.connect();

 // set up a message handler for the 'analog' feed.
 // the handleMessage function (defined below)
 // will be called whenever a message is
 // received from adafruit io.
 color->onMessage(handleMessage);
 slacktest->onMessage(handleNumber);

 // wait for a connection
 while(io.status() < AIO_CONNECTED) {
   Serial.print(".");
   delay(500);
 }

 // we are connected
 Serial.println();
 Serial.println(io.statusText());
 color->get();
// slacktest->get();

 // neopixels strip
 strip.begin();
 strip.show();

}

void loop() {
 io.run();

 //licht sensor
 int sensorValue = analogRead(A0);
// Serial.println("Lichtwaarde: ");
// Serial.println(sensorValue);


 if (sensorValue <= 200 )
 {
 strip.setBrightness(3);
 strip.show();
 }
 else if (sensorValue >= 201 && sensorValue <= 400)
 {
 strip.setBrightness(6);
 strip.show();
 }
 else if (sensorValue >= 401 && sensorValue <= 600)
 {
 strip.setBrightness(12);
 strip.show();
 }
 else if (sensorValue >= 601 && sensorValue <= 800)
 {
 strip.setBrightness(18);
 strip.show();
 }
 else if (sensorValue >= 801 && sensorValue <= 1000)
 {
 strip.setBrightness(24);
 strip.show();
 }
 else
 {
 strip.setBrightness(30);
 strip.show();
 }
 delay(500);

}


// this function is called whenever an 'analog' message
// is received from Adafruit IO. it was attached to
// the analog feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

 Serial.println("Received HEX: ");
 Serial.println(data->value());

 long color = data->toNeoPixel();

   for(int i=0; i<18; ++i) {
   strip.setPixelColor(i, color);
    }
   strip.show();

 // convert the data to integer
 //int reading = data->toInt();
//Serial.println(reading);

 //Serial.print("received <- ");


 // write the current 'reading' to the led
 //#if defined(ARDUINO_ARCH_ESP32)
   //ledcWrite(1, reading); // ESP32 analogWrite()
 //#else
 // analogWrite(D5, reading);
// #endif

 //analogWrite(LEDpin, reading);
  }
  
  void handleNumber(AdafruitIO_Data *data) {
    
    Serial.println("Received Number: ");
    Serial.println(data->value());

    int slacktest = data->toInt();

    if(slacktest == 1){
      for(int i=0; i<18; ++i) {
        strip.setPixelColor(i, 0, 0, 255);
        }
      strip.show();
      delay(500);
    } else if (slacktest  == 2) {
      
        strip.setBrightness(0);
        strip.show();
    }else {
      strip.setBrightness(30);
       strip.show();
    }
    
    }

