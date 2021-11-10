#include "MICS-VZ-89TE.h"

MICS_VZ_89TE CO2SENSOR;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  CO2SENSOR.begin();

  Serial.println("MICS-VZ-89TE Example");

}

void loop() { // run over and over

  CO2SENSOR.readSensor();

  float co2 = CO2SENSOR.getCO2();
  float voc = CO2SENSOR.getVOC();

  Serial.print("CO2: ");
  Serial.println(co2, 3);

  Serial.print("VOC: ");
  Serial.println(voc, 3);

  delay(1000);
}
