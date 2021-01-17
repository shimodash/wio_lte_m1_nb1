#include <WioCellLibforArduino.h>

#define APN               "soracom.io"
#define USERNAME          "sora"
#define PASSWORD          "sora"

#define WEBHOOK_EVENTNAME ""
#define WEBHOOK_KEY       ""
#define WEBHOOK_URL       "https://maker.ifttt.com/trigger/" WEBHOOK_EVENTNAME "/with/key/" WEBHOOK_KEY

#define INTERVAL          (30000)

// uncomment following line to use Temperature & Humidity sensor
#define SENSOR_PIN    (WIO_D38)

WioCellular Wio;
  
void setup() {
  delay(200);
  
  SerialUSB.begin(115200);
  SerialUSB.println("");
  SerialUSB.println("--- START ---------------------------------------------------");
  
  SerialUSB.println("### I/O Initialize.");
  Wio.Init();
  
  SerialUSB.println("### LED Power supply ON.");
  Wio.PowerSupplyLed(true);
  delay(500);
  //set red   Wio.LedSetRGB(r, g, b);
  Wio.LedSetRGB(10, 0, 0);

  
  SerialUSB.println("### Power supply ON.");
  Wio.PowerSupplyCellular(true);
  delay(500);

  SerialUSB.println("### Turn on or reset.");
#ifdef ARDUINO_WIO_LTE_M1NB1_BG96
  Wio.SetAccessTechnology(WioCellular::ACCESS_TECHNOLOGY_LTE_M1);
  Wio.SetSelectNetwork(WioCellular::SELECT_NETWORK_MODE_MANUAL_IMSI);
#endif
  if (!Wio.TurnOnOrReset()) {
    SerialUSB.println("### ERROR! ###");
    return;
  }
  //set blue  Wio.LedSetRGB(r, g, b);
  Wio.LedSetRGB(0, 0, 10);

  SerialUSB.println("### Connecting to \"" APN "\".");
  if (!Wio.Activate(APN, USERNAME, PASSWORD)) {
    SerialUSB.println("### ERROR! ###");
    return;
  }
  //set green  Wio.LedSetRGB(r, g, b);
  Wio.LedSetRGB(0, 10, 0);

#ifdef SENSOR_PIN
//  TemperatureAndHumidityBegin(SENSOR_PIN);
  pinMode(SENSOR_PIN, INPUT);
#endif // SENSOR_PIN

  SerialUSB.println("### Setup completed.");
}

void loop() {
  char data[100];
  int status;

#ifdef SENSOR_PIN
  int SENSORState = digitalRead(SENSOR_PIN);  
  sprintf(data, "{\"uptime\":%lu}", millis() / 1000);
#else
#endif // SENSOR_PIN

if(SENSORState==true){
  Wio.LedSetRGB(10, 10, 0);
  
  SerialUSB.println("### Post.");
  sprintf(data, "{\"value1\":\"uptime %lu\"}", millis() / 1000);
  SerialUSB.print("Post:");
  SerialUSB.print(data);
  SerialUSB.println("");
  if (!Wio.HttpPost(WEBHOOK_URL, data, &status)) {
    SerialUSB.println("### ERROR! ###");
    goto err;
  }
  SerialUSB.print("Status:");
  SerialUSB.println(status);

  err:
  SerialUSB.println("### Wait.");
  delay(INTERVAL);
}else{
  Wio.LedSetRGB(0, 10, 0);

}

}
