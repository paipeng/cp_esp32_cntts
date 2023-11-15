#include <Arduino.h>
#include "textcodec.h"

#define CN_TTS_TX_PIN 16  // TX pin of CN_TTS
#define CN_TTS_RX_PIN 17  // RX pin of CN_TTS



// hardware serial
// 0: 3, 1
// 1: 9, 10
// 2: 16, 17
HardwareSerial cntts(2);  //Serial port 2


void test() {
  const char* text = "你好CPIOT世界";            /* 注意：当前文件的编码格式为UTF-8 */
	uint32_t utf8Size, unicodeSize, gbkSize;
	uint8_t utf8[64];
	uint8_t unicode[64];
	uint8_t gbk[64];

	//
	// 打印原始数据：本文件是UTF-8编码的
	//
	Serial.printf(" ------ byte array in UTF8 format: ");
	for(int i = 0; i < strlen(text); i++)
	{
		Serial.printf("0x%02X,", text[i] & 0XFF);
	}
	Serial.printf("\n");

	//
	// UTF8转UNICODE
	//
	Serial.printf(" ------ utf8 to unicode : ");
	utf8ToUnicode((const uint8_t *)text, strlen(text), unicode, &unicodeSize);
	for(int i = 0; i < unicodeSize; i++)
	{
		Serial.printf("0x%02X,", unicode[i] & 0XFF);
	}
	Serial.printf("\n");
#if 1
	//
	// UTF8转GBK
	//
	UTF8ToGBK((const uint8_t *)text, strlen(text), gbk, &gbkSize);
	printf(" ------ utf8 to gbk     : ");
	for(int i = 0; i < gbkSize; i++)
	{
		printf("0x%02X,", gbk[i] & 0XFF);
	}
	printf("\n");

  Serial.println("测试");
  cntts.println((const char*)gbk);
  updateSerial();

	//
	// GBK转UNICODE
	//
	Serial.printf(" ------ gbk  to unicode : ");
	GBKToUnicode((const uint8_t *)gbk, gbkSize, unicode, &unicodeSize);
	for(int i = 0; i < unicodeSize; i++)
	{
		Serial.printf("0x%02X,", unicode[i] & 0XFF);
	}
	Serial.printf("\n");

	//
	// GBK转UTF8
	//
	GBKToUTF8(gbk, gbkSize, utf8, &utf8Size);
	Serial.printf(" ------ gbk  to utf8    : ");
	for(int i = 0; i < utf8Size; i++)
	{
		Serial.printf("0x%02X,", utf8[i] & 0XFF);
	}
	Serial.printf("\n");

	//
	// UNICODE转UTF8
	//
	UnicodeToUTF8(unicode, unicodeSize, utf8, &utf8Size);
	Serial.printf(" ------ unicode to utf8 : ");
	for(int i = 0; i < utf8Size; i++)
	{
		Serial.printf("0x%02X,", utf8[i] & 0XFF);
	}
	Serial.printf("\n");

	//
	// unicode转gbk
	//
	UnicodeToGBK(unicode, unicodeSize, gbk, &gbkSize);
	Serial.printf(" ------ unicode to gbk  : ");
	for(int i = 0; i < gbkSize; i++)
	{
		Serial.printf("0x%02X,", gbk[i] & 0XFF);
	}
	Serial.printf("\n");

	//
	// HEX转STR
	//
	uint8_t hex[3] = {0XAA, 0XBB, 0XCC};
	uint32_t hexSize;
	char     str[32];
	uint32_t strSize;
	HexToStr(hex, 3, str, &strSize);
	Serial.printf(" ------ HEX TO STR: %s \n", str);

	//
	// STR转HEX
	//
	StrToHex(str, strSize, hex, &hexSize);
	Serial.printf(" ------ STR TO HEX: 0x%02X,0x%02X,0x%02X \n", hex[0], hex[1], hex[2]);
#endif
}



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

  //Serial.println("测试");
  //cntts.println("CPIOT大家好");
  //updateSerial();
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

  test();
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
