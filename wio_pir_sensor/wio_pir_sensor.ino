#include <WioCellLibforArduino.h>

#define LED_VALUE (10)
//#define INTERVAL  (50)
#define BUTTON_PIN  (WIO_D38)
#define INTERVAL    (100)

WioCellular Wio;
int Hue = 0;

void setup() {
  delay(200);

  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---------------------------------------------------");

  SerialUSB.println("### I/O Initialize..");
  Wio.Init();
  
  SerialUSB.println("### Power supply ON.");
  Wio.PowerSupplyLed(true);
  delay(500);
  
  SerialUSB.println("### Setup completed.");

  pinMode(BUTTON_PIN, INPUT);
  SerialUSB.println("### PIR sensor input set.");
  
}

  int r;
  int g;
  int b;

void loop() {

/*  
  if (Hue < 60) {
    r = LED_VALUE;
    g = Hue * LED_VALUE / 60;
    b = 0;
  }
  else if (Hue < 120) {
    r = (120 - Hue) * LED_VALUE / 60;
    g = LED_VALUE;
    b = 0;
  }
  else if (Hue < 180) {
    r = 0;
    g = LED_VALUE;
    b = (Hue - 120) * LED_VALUE / 60;
  }
  else if (Hue < 240) {
    r = 0;
    g = (240 - Hue) * LED_VALUE / 60;
    b = LED_VALUE;
  }
  else if (Hue < 300) {
    r = (Hue - 240) * LED_VALUE / 60;
    g = 0;
    b = LED_VALUE;
  }
  else {
    r = LED_VALUE;
    g = 0;
    b = (360 - Hue) * LED_VALUE / 60;
  }
*/
  
  int buttonState = digitalRead(BUTTON_PIN);
//  SerialUSB.println(buttonState ? '*' : '.');

  if(buttonState==true){
    r = 0;
    g = LED_VALUE;
    b = 0;
  }else{
    r = LED_VALUE;
    g = 0;
    b = 0;
  }
    Wio.LedSetRGB(r, g, b);

/*
  Hue += 10;
  if (Hue >= 360) Hue = 0;
*/  
  delay(INTERVAL);
}
