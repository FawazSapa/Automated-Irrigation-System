#define BLYNK_TEMPLATE_ID "TMPL2rlw-Q4H3"
#define BLYNK_TEMPLATE_NAME "SmartIrrigationSystem"
#define BLYNK_AUTH_TOKEN "ScXLICVkMuKYYaCYhzmQnF9O5T9z5hs-"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <HardwareSerial.h>

// Your WiFi credentials.
char ssid[] = "Mahendra";
char pass[] = "Mahendra@123$";

// Your Blynk Auth Token
char auth[] = "ScXLICVkMuKYYaCYhzmQnF9O5T9z5hs-";

HardwareSerial mbedSerial(1); // Use the second serial port of ESP32

bool notifiedForMoisture = false; // Flags to control the notification flow
bool notifiedForWater = false;

BLYNK_WRITE(V2) {
  int pinValue = param.asInt(); // assigning incoming value from pin V2 to a variable
  // Now send this value to the MBED device over serial
  if(pinValue == 1) {
      mbedSerial.write("1"); // Assuming that your MBED program expects "1" to start the pump
  } else {
      mbedSerial.write("0"); // And "0" to stop the pump
  }
}

void setup() {
  // Start the ESP32 Serial for debugging at the same baud rate as the MBED serial connection
  Serial.begin(9600);

  // Initialize the Blynk connection
  Blynk.begin(auth, ssid, pass);
  
  // Start communication with the MBED device
  mbedSerial.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  Blynk.run(); // Run Blynk
  
  if (mbedSerial.available()) {
    String data = mbedSerial.readStringUntil('\n'); // Read the incoming data until newline
    int light, moisture, water;
    
    // Assuming the data format is "light,moisture,water"
    sscanf(data.c_str(), "%d,%d,%d", &light, &moisture, &water);

    // Now send these values to the Blynk app.
    Blynk.virtualWrite(V0, light);
    Blynk.virtualWrite(V1, moisture);
    Blynk.virtualWrite(V3, water);

    // Check for critical levels and send an email if necessary
    if (moisture < 40 && !notifiedForMoisture) {
      Blynk.logEvent("low_moisture_level","Alert: Moisture level is below 40!");
      notifiedForMoisture = true;
    } else if (moisture >= 40 && notifiedForMoisture) {
      notifiedForMoisture = false;
    }

    if (water < 40 && !notifiedForWater) {
      Blynk.logEvent("low_water_level","Alert: Water level is below 40!");
      notifiedForWater = true;
    } else if (water >= 40 && notifiedForWater) {
      notifiedForWater = false;
    }

    // Print the received values to the Serial Monitor for debugging
    Serial.print("Light: ");
    Serial.print(light);
    Serial.print(", Moisture: ");
    Serial.print(moisture);
    Serial.print(", Water: ");
    Serial.println(water);
  }
}
