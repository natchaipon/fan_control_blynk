// 23/8/2562
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "83b7d0b48b384520a16a2daaf68ddc6d";
char ssid[] = "P";
char pass[] = "12345678";
char host[] = "blynk.honey.co.th";

const int output_mode = D2;
const int switch_1 = D3;
const int switch_2 = D4;
const int switch_3 = D5;
const int switch_4 = D6;

int mode_switch;
int switch_1_read;
int switch_2_read;
int switch_3_read;
int switch_swing;

BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  //  Blynk.begin(auth, ssid, pass);
  Blynk.begin(auth , ssid , pass , host , 8080);
  pinMode(output_mode , OUTPUT);
  pinMode(switch_1 , OUTPUT);
  pinMode(switch_2 , OUTPUT);
  pinMode(switch_3 , OUTPUT);
  pinMode(switch_4 , OUTPUT);
  timer.setInterval(100L, sendUptime);
}

BLYNK_WRITE(V1) {
  switch_1_read = param.asInt();
}
BLYNK_WRITE(V2) {
  switch_2_read = param.asInt();
}
BLYNK_WRITE(V3) {
  switch_3_read = param.asInt();
}
BLYNK_WRITE(V4) {
  switch_swing = param.asInt();
}
BLYNK_WRITE(V0) {
  mode_switch = param.asInt();
}


void sendUptime() {
  if (mode_switch == 1) {
    digitalWrite(output_mode , 1);
    delay(20);
    if (switch_swing == 1) {
      Serial.println("swing");
      digitalWrite(switch_4 , 0);
    }
    else {
      digitalWrite(switch_4 , 1);
    }

    if (switch_1_read == 1) {
      Serial.println("sw1");
      digitalWrite(switch_2 , 1);
      digitalWrite(switch_3 , 1);
      delay(20);
      digitalWrite(switch_1 , 0);
    }
    else if (switch_2_read == 1) {
      Serial.println("sw2");
      digitalWrite(switch_1 , 1);
      digitalWrite(switch_3 , 1);
      delay(20);
      digitalWrite(switch_2 , 0);
    }
    else if (switch_3_read == 1) {
      Serial.println("sw3");
      digitalWrite(switch_1 , 1);
      digitalWrite(switch_2 , 1);
      delay(20);
      digitalWrite(switch_3 , 0);
    }
    else {
      Serial.println("off");
      digitalWrite(switch_1 , 1);
      digitalWrite(switch_2 , 1);
      digitalWrite(switch_3 , 1);
    }
  }
  else {
    Serial.println("manual mode");
    digitalWrite(switch_1 , 1);
    digitalWrite(switch_2 , 1);
    digitalWrite(switch_3 , 1);
    digitalWrite(switch_4 , 1);
    
    delay(20);
    digitalWrite(output_mode , 0);
  }
}


void loop() {
  Blynk.run();
  timer.run();
}
