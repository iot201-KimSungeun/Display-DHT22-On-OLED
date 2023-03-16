#include <Arduino.h>
#include <SSD1306.h>
#include <DHTesp.h>

SSD1306             display(0x3c, 4, 5, GEOMETRY_128_32);
DHTesp              dht;
int                 interval = 2000;
unsigned long       lastDHTReadMillis = 0;
float               humidity = 0;
float               temperature = 0;

void setup() {
  // put your setup code here, to run once:
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  dht.setup(14, DHTesp::DHT22); // Connect DHT sensor to GPIO 14
  delay(1000);
}

void readDHT22() {
    unsigned long currentMillis = millis();

    if(currentMillis - lastDHTReadMillis >= interval) {
        lastDHTReadMillis = currentMillis;

        humidity = dht.getHumidity();              // Read humidity (percent)
        temperature = dht.getTemperature();        // Read temperature as Fahrenheit
    }
}

void loop() {
  readDHT22();
  char buf[10];
  sprintf(buf, "temp:  %.1f", temperature);
  display.drawString(10, 2, buf);
  sprintf(buf, "hum: %.1f", humidity);
  display.drawString(10, 15, buf);
  display.display();

  delay(1000);
  display.resetDisplay();
}