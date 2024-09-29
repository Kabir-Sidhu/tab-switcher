#include <WiFi.h>
#include <HTTPClient.h>
#define SOUND_SPEED 0.034

const char* ssid = "ssid";
const char* password =  "password";

const int led = 5;
const int trig = 2;
const int echo = 18;

const char *host = "http://192.168.250.93:5000/switch";

long duration;
float distance;

void setup() {
  Serial.begin(9600);
  delay(4000);

  pinMode(led, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
 
 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Connected");
}

void loop() {
  digitalWrite(trig, LOW);
  
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);

  delayMicroseconds(10);
  
  digitalWrite(trig, LOW);

  digitalWrite(led, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * (SOUND_SPEED/2);

  Serial.println(distance);

  if (WiFi.status() == WL_CONNECTED && distance < 50) {
    digitalWrite(led, HIGH);
    HTTPClient http;

    http.begin(host);

    int r = http.GET();

    if (r > 0) {
      Serial.println(r);
      String payload = http.getString();
    }
    
    else {
      Serial.print("Error code: ");
      Serial.println(r);
    }

    delay(10000);
    
    digitalWrite(led, LOW);
  }
  
}