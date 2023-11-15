//#include <SoftwareSerial.h>


#define FS800E_TX_PIN 16 // TX pin of BT FS800E
#define FS800E_RX_PIN 17 // RX pin of BT FS800E


//SoftwareSerial serial4g(FS800E_RX_PIN, FS800E_TX_PIN);

// hardware serial
// 0: 3, 1
// 1: 9, 10
// 2: 16, 17
HardwareSerial serial4g(2);//Serial port 2


void send_SMS() {
  serial4g.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  serial4g.println("AT+CMGS=\"+8613230000000\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  serial4g.print("Circuit Digest"); //text content
  updateSerial();
  serial4g.write(26);
}

void lte4g_mqtt_init() {
  Serial.println("lte4g_mqtt_init");

  Serial.println("设置MQTT网络模式");
  serial4g.println("AT+WKMOD=MQTT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  

  Serial.println("设置MQTT服务器参数");
  serial4g.println("AT+MQTTSV=broker-cn.emqx.io,1883"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  Serial.println("设置MQTT服务器连接参数");
  serial4g.println("AT+MQTTCONN=cpiot4g,,,60,1"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  Serial.println("设置MQTT订阅参数");
  serial4g.println("AT+MQTTSUB=CPIOT,0"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  Serial.println("设置MQTT发布参数");
  serial4g.println("AT+MQTTPUB=CPIOT,0,0"); //Once the handshake test is successful, it will back to OK
  updateSerial();
}

void lte4g_init() {
  Serial.println("lte4g_init");
  Serial.println("command mode +++");
  serial4g.print("+++");
  updateSerial();

  Serial.println("AT");
  serial4g.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  serial4g.println("AT+VER"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  Serial.println("AT+CSQ");
  serial4g.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();

  serial4g.println("AT+IMEI"); 
  updateSerial();
  serial4g.println("AT+ICCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();

  Serial.println("AT+CREG?");
  serial4g.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();

  Serial.println("AT+LBS");
  serial4g.println("AT+LBS"); //Check whether it has registered in the network
  updateSerial();
  Serial.println("AT+CIP");
  serial4g.println("AT+CIP"); //Check whether it has registered in the network
  updateSerial();

  lte4g_mqtt_init();


  Serial.println("保存设置并重启");
  serial4g.println("AT+S"); //Check whether it has registered in the network
  updateSerial();
  

  Serial.println("Transparent transmission mode");
  serial4g.println("AT+ENTM"); //Check whether it has registered in the network
  updateSerial();
}

void setup() {
  delay(1000);

  Serial.begin(115200);
  Serial.println("");
  delay(3000);
  Serial.println("Serial inited");
  
  //serial4g.begin(115200);
  //Begin serial communication with Arduino and SIM800L
  serial4g.begin(115200, SERIAL_8N1, FS800E_TX_PIN, FS800E_RX_PIN);
  //serial4g.begin(115200);
  Serial.println("\nEZDTU 4G to ESP32 Serial port 2");


  Serial.println("4G inited");

  delay(1000);

  lte4g_init();
  
  Serial.println("setup done");
}


void loop() {
  delay(500);
  updateSerial();
}

void updateSerial() {
  delay(1000);
  while (Serial.available()) {
    //Serial.println("input received");
    serial4g.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(serial4g.available()) {
    //Serial.println("output received");
    Serial.write(serial4g.read());//Forward what Software Serial received to Serial Port
  }
}