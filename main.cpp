#include "DHT.h"
#include "LCDi2c.h"
#include "mbed.h"

//Pinouts Config
BufferedSerial pc(PTC17, PTC16);
LCDi2c lcd(PTE25, PTE24, LCD16x2, 0x27);
DHT sensor(PTA1, DHT11);
AnalogIn photoresistor(PTB11);
DigitalOut pumpRelay(PTA2);
AnalogIn soilMoistureSensor(PTB10);
AnalogIn waterLevelSensor(PTB3);

int main() {
  // Wait for the sensor to stabilize
  ThisThread::sleep_for(2s);
  pc.set_baud(9600);
  char buffer[32];
  char buf[10];
  bool systemActive = false;

  while (true) {
    if (pc.readable()) {
      char buf[2];
      ssize_t num =
          pc.read(buf, sizeof(buf) - 1); // Ensure space for null-terminator
      if (num > 0) {
        buf[num] = '\0'; // Null-terminate the string
        systemActive = (buf[0] == '1');
        // if the code receives a 0 then the system will remain off
        if (!systemActive) {
          // Display system off message if it's not active in the LCD display
          pumpRelay = 0;
          lcd.cls();
          lcd.locate(0, 0);
          lcd.printf("System Off!");
        }
      }
    }
    // if the code receives 1 from the Blunk application the automated irrigation system will turn on
    if (systemActive) {
      float temperature = 0.0f;
      float humidity = 0.0f;
      eError err = sensor.readData();
      // Read the photoresistor value (0.0 to 100.0)
      float lightLevel = photoresistor.read() * 100;
      float moistureLevel = soilMoistureSensor.read() * 100;
      float waterLevel = waterLevelSensor.read() * 100;

      //Convert light, water and photoresistor values for Blynk Iot application
      int light = lightLevel;
      int moisture = moistureLevel;
      int water = waterLevel;

      if (err == ERROR_NONE) {
        temperature = sensor.ReadTemperature(CELCIUS);
        humidity = sensor.ReadHumidity();

        // Clear the LCD
        lcd.cls();

        // Set cursor to first row, first column
        lcd.locate(0, 0);
        lcd.printf("Temp: %.2f C", temperature);

        // Set cursor to second row, first column
        lcd.locate(0, 1);
        lcd.printf("Humid: %.2f %%", humidity);
      } else {
        // If there's an error, display it on the LCD
        lcd.cls();
        lcd.locate(0, 0);
        lcd.printf("DHT Error: %d", err);
      }

      int length = sprintf(buffer, "%d,%d,%d\n", light, moisture, water);

      // Send the values over BufferedSerial
      if (length > 0) {
        pc.write(buffer, length);
      }
      // if the value from photoresistor and water level sensor is greater than 50 and moisture level senor is less than 50 turn on the water pump
      bool pumpCondition = (lightLevel > 50) && waterLevel > 50 && moistureLevel<50;

      if (pumpCondition) {
        pumpRelay = 1; // Turn on the pump
        lcd.cls();
        lcd.locate(0, 1);
        lcd.printf("Pumping water ");
      } else {
        pumpRelay = 0; // Turn off the pump
      }

      // Print sensor values to the console for debugging
      printf("Light: %.2f, Moisture: %.2f, Water: %.2f\n", lightLevel, moistureLevel, waterLevel);
      // Update every 2 seconds
      ThisThread::sleep_for(2s);
    }
  }
}

