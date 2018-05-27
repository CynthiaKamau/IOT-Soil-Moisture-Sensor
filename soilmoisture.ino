#include <TheThingsNetwork.h>

const char *devAddr = "26011BFA";
const char *nwkSKey = "41E9134D3DFCBC5652F73A19A7BED8C1";
const char *appSKey = "5F57FEAAAC02609756BA815196C2AEF4";

#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup()
{
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  debugSerial.println("-- PERSONALIZE");
  ttn.personalize(devAddr, nwkSKey, appSKey);

  debugSerial.println("-- STATUS");
  ttn.showStatus();
}

void loop()
{
  debugSerial.println("-- LOOP");
  int soilMoisture = analogRead(A0);
 
  byte payload[2];
  payload[0] = highByte(soilMoisture);
  payload[1] = lowByte(soilMoisture);

  ttn.sendBytes(payload, sizeof(payload));

  delay(10000);
}
