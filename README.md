# Smart-Parking-System

# Vehicle Parking System

This project is an automated vehicle parking system using an ESP8266, sensors, and servo motors. It integrates with Firebase to track parking slot availability in real-time.

## Features
- Automatically opens and closes entry and exit gates based on parking slot availability.
- Tracks the number of vehicles in the parking area.
- Sends real-time parking slot data to Firebase.

## Hardware Requirements
- ESP8266
- IR Sensors (2 for parking slots, 1 for entry gate, 1 for exit gate)
- Servo Motors (2 for entry and exit gates)
- Power supply and connecting wires

## Software Requirements
- Arduino IDE
- ESP8266WiFi library
- FirebaseArduino library
- Servo library

## Setup
1. Connect the hardware components as per the pin configuration in the code.
2. Install the required libraries from the Arduino Library Manager.
3. Update the Wi-Fi credentials and Firebase details in the code.
4. Upload the code to your ESP8266.

## Firebase Setup
1. Create a Firebase Realtime Database project.
2. Get your `FIREBASE_HOST` and `FIREBASE_AUTH` keys from the Firebase console.
3. Replace the placeholders in the code with your actual Firebase credentials.

## Usage
- Once the code is uploaded, the system will start monitoring the parking slots.
- The entry gate opens automatically if a slot is available and closes after the vehicle enters.
- The exit gate opens automatically when a vehicle is detected at the exit and closes afterward.
- Firebase will update the slot status in real-time.

## License
This project is licensed under the MIT License.
