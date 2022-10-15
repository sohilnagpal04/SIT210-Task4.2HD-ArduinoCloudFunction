#include <Arduino.h>
#include <WiFiNINA.h>
#include <ArduinoJson.h>
#include <Firebase_Arduino_WiFiNINA.h>

#define FIREBASE_HOST "sit210task-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "5Ovjb2cSEMiYZDYxHLqFi9Z8XRe9Xfi69iHqNmOY"

char ssid[] = "Sohil\342\200\231s iPhone";
char pass[] = "9996665842";

FirebaseData object;
String path = "/status/status";

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.print("You're connected to the ");
  Serial.println(ssid);
  Serial.print("WiFi localIP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, ssid, pass);
  Firebase.reconnectWiFi(true);

  if (Firebase.setString(object, path, "OFF"))
  {
    Serial.println("OK");
  }
  else
  {
    Serial.println("Error: " + object.errorReason());
  }
}

void loop()
{
  if (Firebase.getString(object, path))
  {
    if (object.stringData() == "RED")
    {
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      Serial.println("RED LED ON");  
    }
    else if (object.stringData() == "YELLOW")
    {
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      Serial.println("YELLOW LED on");
    }
    else if (object.stringData() == "GREEN")
    {
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
      digitalWrite(4, HIGH);
      Serial.println("Green LED on");
    }
     else if (object.stringData() == "OFF")
    {
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
      digitalWrite(4, LOW);
      Serial.println("OFF");
    }
   
  }
  else
  {
    Serial.println("Error");
  }
}