#include "HomeSpan.h"
#include "DHT.h"

// Pin Assignments
#define DHTPIN 23       // Data wire on GPIO 23
#define DHTTYPE DHT11   // Blue sensor
#define STATUS_LED 2    // Built-in LED on GPIO 2

DHT dht(DHTPIN, DHTTYPE);

// Temperature Sensor Logic
struct TempSensor : Service::TemperatureSensor {
  SpanCharacteristic *temp;
  
  TempSensor() : Service::TemperatureSensor() {
    temp = new Characteristic::CurrentTemperature(22); // Default 22°C
    temp->setRange(-40, 100); 
  }

  void loop() {
    if (temp->timeVal() > 5000) { // Update HomeKit every 5 seconds
      float t = dht.readTemperature();
      if (!isnan(t)) {
        temp->setVal(t);
      }
    }
  }
};

// Humidity Sensor Logic
struct HumSensor : Service::HumiditySensor {
  SpanCharacteristic *hum;
  
  HumSensor() : Service::HumiditySensor() {
    hum = new Characteristic::CurrentRelativeHumidity(50);
  }

  void loop() {
    if (hum->timeVal() > 5000) {
      float h = dht.readHumidity();
      if (!isnan(h)) {
        hum->setVal(h);
      }
    }
  }
};

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(STATUS_LED, OUTPUT);

  // Initialize HomeSpan
  homeSpan.begin(Category::Bridges, "HomeSpan Weather Station");

  // Define the Accessory
  new SpanAccessory();  
    new Service::AccessoryInformation();
      new Characteristic::Name("Desk Weather");
      new Characteristic::Manufacturer("DIY-Gemini");
      new Characteristic::SerialNumber("ESP32-001");
      new Characteristic::Identify();
    
    // Add the sensor services to this accessory
    new TempSensor();
    new HumSensor();
}

void loop() {
  homeSpan.poll(); // Keeps HomeKit connection alive
  
  // Your 1-second blink heartbeat
  static uint32_t lastBlink = 0;
  if (millis() - lastBlink > 1000) {
    digitalWrite(STATUS_LED, !digitalRead(STATUS_LED));
    lastBlink = millis();
  }
}