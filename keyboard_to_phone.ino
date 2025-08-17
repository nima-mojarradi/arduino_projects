#include <SPI.h>
#include <TFT_eSPI.h>
#include <BluetoothSerial.h>

TFT_eSPI tft = TFT_eSPI();
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  SerialBT.begin("ESP32_TO_PHONE");
  Serial.println("Bluetooth device is ready to pair!");
  tft.println("Bluetooth is ON.");
  tft.println("Search for 'ESP32_TO_PHONE'");
}

void loop() {

  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');

    tft.setTextColor(TFT_YELLOW);
    tft.println("From Laptop:");
    tft.setTextColor(TFT_CYAN);
    tft.println(message);

    if (SerialBT.hasClient()) {
      SerialBT.println(message);
      tft.setTextColor(TFT_GREEN);
      tft.println("Sent to phone!");
    } else {
      tft.setTextColor(TFT_RED);
      tft.println("No phone connected!");
    }
  }


  if (SerialBT.available()) {
    String message = SerialBT.readStringUntil('\n');

    tft.setTextColor(TFT_YELLOW);
    tft.println("From Phone:");
    tft.setTextColor(TFT_CYAN);
    tft.println(message);
    

    Serial.print("Received via Bluetooth: ");
    Serial.println(message);

    if (message.indexOf("ON") != -1) {
      tft.setTextColor(TFT_GREEN);
      tft.println("Turning LED ON!");
    } else if (message.indexOf("OFF") != -1) {
      tft.setTextColor(TFT_RED);
      tft.println("Turning LED OFF!");
    }
  }

  delay(20);
}
