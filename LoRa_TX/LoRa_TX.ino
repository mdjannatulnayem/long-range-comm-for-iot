#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_BMP280.h>
#define relay_pin 4

Adafruit_BMP280 bmp;

byte localAddress = 0xBB;
byte destinationAddress = 0xAA;
long lastSendTime = 0;
long int interval = 2000;

double reading;
int relay = 0;

void sendMessage(String outgoing) {
  LoRa.beginPacket();
  LoRa.write(destinationAddress);
  LoRa.write(localAddress);
  LoRa.write(outgoing.length());
  LoRa.print(outgoing);
  LoRa.endPacket();
}

void receiveMessage(long int packetSize) {
  if (packetSize == 0) return;
  long int recipient = LoRa.read();
  byte sender = LoRa.read();
  byte incomingLength = LoRa.read();
  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  if (incomingLength != incoming.length()) {
    Serial.println("Error: Message length does not match length");
    return;
  }

  if (recipient != localAddress) {
    Serial.println("Error: Recipient address does not match local address");
    return;
  }
  
  if(incoming == "0"){
    relay = 0;
  }
  if(incoming == "1"){
    relay = 1;
  }

  Serial.print("Received data " + incoming);
  Serial.print(" from 0x" + String(sender, HEX));
  Serial.println(" to 0x" + String(recipient, HEX));
}

void setup() {
  Serial.begin(9600);
  Serial.println("BMP280 test!");
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring or try a different address!");
    Serial.print("SensorID was: 0x");
    Serial.println(bmp.sensorID(),16);
    Serial.print("ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("ID of 0x60 represents a BME 280.\n");
    Serial.print("ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
                  
  ////---------------LoRa---------------////
  Serial.println("Start LoRa duplex");
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (true) {}
  }
  pinMode(relay_pin,OUTPUT);
}

void loop() {
  Serial.print("BMP reading: ");
  reading = bmp.readTemperature();
  Serial.println(reading);

  receiveMessage(LoRa.parsePacket());
  digitalWrite(relay_pin,relay);

  
  if (millis() - lastSendTime > interval) {
    
    String sensorData = String(reading);
    sendMessage(sensorData);

    Serial.print("Sending data " + sensorData);
    Serial.print(" from source 0x" + String(localAddress, HEX));
    Serial.println(" to destination 0x" + String(destinationAddress, HEX));

    lastSendTime = millis();
    interval = random(500) + 1000;
  }
}
