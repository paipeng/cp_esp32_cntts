#include <Arduino.h>

#define CN_TTS_TX_PIN 16  // TX pin of CN_TTS
#define CN_TTS_RX_PIN 17  // RX pin of CN_TTS



// hardware serial
// 0: 3, 1
// 1: 9, 10
// 2: 16, 17
HardwareSerial cntts(2);  //Serial port 2



void cntts_init() {
  Serial.println("cntts_init");

  Serial.println("设置音效 0-7， 默认0");
  cntts.println("<Z>0");
  updateSerial();

  Serial.println("设置音量 1-4， 默认4");
  cntts.println("<V>3");
  updateSerial();

  Serial.println("设置语速 1-3， 默认2");
  cntts.println("<S>2");
  updateSerial();
  //Serial.println("设置上电提示 0-1， 默认1");
  //cntts.println("<I>1");
  //updateSerial();

  Serial.println("测试");
  cntts.println("CPIOT大家好");
  updateSerial();
}

void setup() {
  delay(1000);

  Serial.begin(115200);
  Serial.println("");
  delay(3000);
  Serial.println("Serial inited");

  cntts.begin(9600, SERIAL_8N1, CN_TTS_TX_PIN, CN_TTS_RX_PIN);
  Serial.println("\nCN-TTS to ESP32 Serial port 2");
  Serial.println("cntts inited");
  delay(1000);

  cntts_init();
  Serial.println("setup done");
}


void loop() {
  updateSerial();
}

void updateSerial() {
  delay(500);
  while (Serial.available()) {
    //Serial.println("input received");
    cntts.write(Serial.read());
  }
  while (cntts.available()) {
    //Serial.println("output received");
    Serial.write(cntts.read());
  }
}