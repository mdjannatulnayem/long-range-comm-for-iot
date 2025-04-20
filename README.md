# 📡 Long-Range Communication for IoT using LoRa (SX1278)

This project demonstrates a reliable **long-range IoT communication system** using **LoRa technology**. It uses two Arduino Uno boards, each connected to an **Ai-Thinker Ra-02 LoRa module** (based on the **SX1278 transceiver**). The goal is to establish duplex communication between the two nodes, enabling data transmission and remote control over several kilometers.

---

## 🚀 Features

- Long-range wireless communication using LoRa (tested up to 2 km line-of-sight)
- Duplex communication:
  - TX Node: Sends **temperature readings** using a **BMP280 sensor**
  - RX Node: Receives sensor data and can send control commands (e.g., LED ON/OFF)
- Based on **Arduino Uno**
- Uses **Sandeep Mistry’s LoRa library**

---

## 🧰 Hardware Used

| Component             | Quantity | Description                                      |
|----------------------|----------|--------------------------------------------------|
| Arduino Uno          | 2        | Microcontroller board for TX and RX nodes       |
| Ai-Thinker Ra-02     | 2        | LoRa module using SX1278                        |
| BMP280 Sensor        | 1        | For measuring temperature (TX node)             |
| LED + Resistor       | 1        | For visual indication (TX node)                 |
| Breadboard & Jumpers | -        | For prototyping                                 |
| Power Supply         | -        | 5V for Arduino, 3.3V for Ra-02 (with regulator) |

> ⚠️ **Important:** SX1278 operates at 3.3V logic. Be careful not to connect it directly to Arduino's 5V I/O pins.

---

## 🗂️ Repository Structure

```text
long-range-comm-for-iot/
│
├── LoRa_RX/           # Code for receiver node (RX)
├── LoRa_TX/           # Code for transmitter node (TX)
└── README.md          # You're here
```

---

## 🛠️ How It Works

### Transmitter (TX Node):
- Reads temperature data from the **BMP280 sensor**
- Sends this data over LoRa to the RX node
- Listens for incoming commands from RX node (e.g., toggle LED)

### Receiver (RX Node):
- Receives sensor data and prints it to Serial Monitor
- Sends a command back (e.g., to turn LED on/off on TX node)

---

## 📦 Dependencies

Make sure you install the following Arduino libraries:

- [`LoRa`](https://github.com/sandeepmistry/arduino-LoRa) by Sandeep Mistry
- [`Adafruit BMP280`](https://github.com/adafruit/Adafruit_BMP280_Library)
- [`Adafruit Sensor`](https://github.com/adafruit/Adafruit_Sensor)

You can install them from the Arduino Library Manager.

---

## 🧪 Testing

- Upload the **LoRa_TX** sketch to one Arduino (TX Node)
- Upload the **LoRa_RX** sketch to the second Arduino (RX Node)
- Open the Serial Monitor at 9600 baud on both Arduinos
- Observe data received and LED response to RX commands

---

## 📷 Project Setup

<p align="center">
  <img src="https://user-images.githubusercontent.com/your_image_link_here" width="600" alt="Setup side view">
  <br>
  <em>Transmitter and Receiver setup on breadboard</em>
</p>

---

## 📡 Range & Performance

- Successfully tested up to **2 km** with **line-of-sight**
- May vary depending on antenna type, terrain, and weather conditions
- Signal diagnostics available via `LoRa.packetRssi()` and `LoRa.packetSnr()`

---

## 🙌 Acknowledgments

Huge thanks to **Sandeep Mistry** for his amazing [LoRa library](https://github.com/sandeepmistry/arduino-LoRa) that made this possible.

---

## 📝 License

This project is open-source and available under the [MIT License](LICENSE).

---

## 💬 Feedback

Feel free to open issues or contribute via pull requests. We'd love to hear your feedback or improvements!

