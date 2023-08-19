#include <SPI.h>
#include <LoRa.h>

byte localAddress = 0xAA;
byte destinationAddress = 0xBB;
long lastSendTime = 0;
long int interval = 2000;

String data;
char cmd;
bool launched;
long count = 0;

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
  data = incoming;


  if (incomingLength != incoming.length()) {
    // Serial.println("Error: Message length does not match length");
    return;
  }

  if (recipient != localAddress) {
    // Serial.println("Error: Recipient address does not match local address");
    return;
  }

  // Serial.print("Received data " + incoming);
  // Serial.print(" from 0x" + String(sender, HEX));
  // Serial.println(" to 0x" + String(recipient, HEX));
}

void setup() {
  Serial.begin(9600);
  //  Serial.println("Start LoRa duplex");
  if (!LoRa.begin(433E6)) {
    //    Serial.println("LoRa init failed. Check your connections.");
    while (true) {}
  }
  launched = false;
  pinMode(6, OUTPUT);
}

void loop() {

  cmd = Serial.read();
  if (cmd == 'L' && launched == false) {
    launched = true;
  }
  if (cmd == 'P' && launched == true) {
    launched = false;
  }

  if (millis() - lastSendTime > interval) {
    sendMessage(String(launched));

    //    Serial.print("Sending data " + sensorData);
    //    Serial.print(" from 0x" + String(localAddress, HEX));
    //    Serial.println(" to 0x" + String(destinationAddress, HEX));

    lastSendTime = millis();
    interval = random(500) + 1000;
  }

  receiveMessage(LoRa.parsePacket());

  //Preplanned delay!
  if (count >= 5000) {
    Serial.println(data);
    count = 0;
  }

  count += 1; //Iterate on each loop!
}
