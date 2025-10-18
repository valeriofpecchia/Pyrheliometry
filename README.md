# Pyrheliometer

This project was developed for the *Museo degli Strumenti di Fisica* in collaboration with the University of Pisa.  
It focuses on measuring solar irradiance at the Earth's surface using custom-built instrumentation and Arduino-based data acquisition.

---

## 📡 Project Overview
The system consists of two main components:

1. **Microcontroller firmware (Arduino sketches)**  
   - Implemented on the **Heltec WiFi Kit 32 (V3)**.  
   - Responsible for temperature measurements, serial data transmission, and real-time plotting on the integrated OLED display.  
   - Two different sketches are provided:
     - `ds18b20_Display_Graph.ino` — for DS18B20 temperature sensor.  
     - `max31865_Display_Graph.ino` — for PT100/PT1000 sensors using the MAX31865 interface.

2. **Data visualization and analysis (Python notebooks)**  
   - `Serial_reading.ipynb`: acquires data from the serial port, visualizes it, and saves it into `.txt` files.  
   - `Data_analysis.ipynb`: performs post-processing and visualization of the recorded data, including experiments with an **iron blackbody** as a reference source.  
   - Each notebook contains detailed explanations in Markdown cells.

---

## ⚙️ Hardware
- Heltec WiFi Kit 32 (V3) microcontroller  
- MAX31865 temperature sensor amplifier (for PT100/PT1000)  
- DS18B20 digital temperature sensor  
- OLED display (integrated on the Heltec board)  
- Custom-built pyrheliometer for solar irradiance measurements  

---

## 🧠 How It Works
1. Upload the appropriate Arduino sketch to your Heltec board.  
2. Connect the sensors and start data acquisition.  
3. Run the `Serial_reading.ipynb` notebook to collect and visualize live data.  
4. Analyze the saved data with `Data_analysis.ipynb` for deeper interpretation.

---



![Immagine WhatsApp 2025-10-18 ore 18 18 16_f1a97c9b](https://github.com/user-attachments/assets/2b150ca0-6d71-46d2-ba0a-b83c2dd9d8bd)


