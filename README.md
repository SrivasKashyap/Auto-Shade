# Auto Shade

An IoT-based smart window automation system built with **ESP32**, **Blynk IoT**, and environmental sensors.  
The system allows manual and automatic control of windows and curtains with real-time feedback.

---

### Features
- **Rain Detection:** Auto-closes window during rain.  
- **Gas Detection:** Alerts when gas levels exceed safety threshold.  
- **App Control:** Manual control via **Blynk mobile app**.  
- **Dual Motor System:** Independent window and curtain motors.  
- **Live Monitoring:** Sensor readings displayed on Serial Monitor.

---

### Components
- ESP32 (NodeMCU)  
- L298N Motor Driver  
- MQ-2 Gas Sensor  
- Rain Sensor Module  
- DC Motors (Window + Curtain)  
- Wi-Fi and Power Supply

---

### Setup
1. Clone the repository  
2. Open `AutoShade.ino` in **Arduino IDE**  
3. Add your Wi-Fi credentials and Blynk Auth Token  
4. Upload to ESP32 and monitor via **Serial Monitor**  
5. Use **Blynk App** to control window and curtain

---

### Future Enhancements
- Integrate **DHT11/DHT22** for temperature-based automation  
- Add **voice control (Alexa/Google Assistant)**  
- Push notifications via Blynk  
- Analytics dashboard for environment tracking  

---

### 🪪 License
[MIT License](./LICENSE)

---

### 🧑‍💻 Author
SrivasKashyap — Engineering Student
