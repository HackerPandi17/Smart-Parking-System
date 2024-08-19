#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Servo.h>

#define FIREBASE_HOST "https://vehicle-parking-e9806-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Hm0VeDQBsTfSyyxGuYEBTMEXwdlBxsJFEOaiV5ri"
#define WIFI_SSID "vivo 1938"
#define WIFI_PASSWORD "12345678"

#define Sensor1 D1
#define Sensor2 D2
#define openSensor D4
#define ExitSensor D5

Servo myservoE;   // Exit Gate Servo
Servo myservoO;   // Entry Gate Servo

int count;

void setup() {
   pinMode(Sensor1, INPUT); 
   pinMode(Sensor2, INPUT);
   pinMode(ExitSensor, INPUT);
   pinMode(openSensor, INPUT);

   myservoO.attach(D2);
   myservoE.attach(D6);
   count = 0;

   Serial.begin(9600);

   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
   Serial.print("connecting");
   while (WiFi.status() != WL_CONNECTED) {
     Serial.print(".");
     delay(500);
   }
   Serial.println();
   Serial.print("connected: ");
   Serial.println(WiFi.localIP());
  
   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
   int pos = 90;
   int pos1 = 90;  // Initial Position Of the Gates

   if(count < 2) {  // Allow cars only if slots are available
      if(digitalRead(openSensor) == 0) { 
         count++;  // Increase the count
         myservoO.write(0);  // Open the gate
         delay(1500);                    
         myservoO.write(pos);  // Close the gate after delay
      }
   } else if(count >= 2) {  // If parking is full
      if(digitalRead(openSensor) == 0) {
         myservoO.write(pos);  // Keep the gate closed
      }
   }

   if(digitalRead(ExitSensor) == 0) { 
      count--;  // Decrease the count when a car exits
      myservoE.write(0);  // Open the exit gate
      delay(1500);        
      myservoE.write(pos);  // Close the exit gate after delay
   }

   Serial.print(count);

   if (Firebase.failed()) {  // Check Firebase connection
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
   }

   delay(1000);

   // Update Firebase with slot availability
   Serial.println("Sensor1");
   Serial.println(digitalRead(Sensor1));
   if(digitalRead(Sensor1) == 0) {
      Firebase.setString("Slot/IR:", "Slot1 Not Available");
      Firebase.setInt("Slot1/IR", 0);
   } else {
      Firebase.setString("Slot/IR:", "Slot1 Available");
      Firebase.setInt("Slot1/IR", 1);
   }

   Serial.println("Sensor2");
   Serial.println(digitalRead(Sensor2));
   if(digitalRead(Sensor2) == 0) {
      Firebase.setString("Slot/IR2:", "Slot2 Not Available");
      Firebase.setInt("Slot1/IR2", 0);
   } else {
      Firebase.setString("Slot/IR2:", "Slot2 Available");
      Firebase.setInt("Slot1/IR2", 1);
   }
}
