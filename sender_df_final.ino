#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>
#include "DFRobot_DF2301Q.h"

#define camera 14  // d5
#define speaker 12  // d6

//I2C communication
DFRobot_DF2301Q_I2C DF2301Q;

int btn1State = 0; // LIGHT  
int btn2State = 0; // OSCILLOSCOPE (2PIN) 
int btn3State = 0; // SOLDER
int btn4State = 0; // POWER  

//int btn5State = 0; // SPEAKER (LOCAL)
//int btn6State = 0; // CAMERA  (LOCAL)


// REPLACE WITH RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xA8, 0x48, 0xFA, 0xE2, 0x43, 0xC7};




// Structure to declare variables
typedef struct myStruct {
  int a;
  int b;
  int c;
  int d;
} myStruct;

// Create a myStruct object called structObj
myStruct structObj;




// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}



 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
    while( !( DF2301Q.begin() ) ) {
    Serial.println("Communication with device failed, please check connection");
    delay(3000);
  }
  
  Serial.println("Begin ok!");

  DF2301Q.setVolume(10);
  DF2301Q.setMuteMode(0);
  DF2301Q.setWakeTime(25);

  uint8_t wakeTime = 0;
  wakeTime = DF2301Q.getWakeTime();
  Serial.print("wakeTime = ");
  Serial.println(wakeTime);

  // DF2301Q.playByCMDID(1);   // Wake-up command
  DF2301Q.playByCMDID(23);   // Common word ID


  pinMode(camera, OUTPUT);
  pinMode(speaker, OUTPUT);


  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER); //set role
  esp_now_register_send_cb(OnDataSent); //set callback
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}



 
void loop() {
    delay(1000);

  uint8_t CMDID = 0;
  CMDID = DF2301Q.getCMDID();
  if(0 != CMDID) {
  Serial.print("CMDID = ");
  Serial.println(CMDID);
  }

  if(CMDID == 82) { //RESET
  btn1State = 100;
  btn2State = 100;
  btn3State = 100;
  btn4State = 100;
  }
  
  if(CMDID == 6) { //GOODBYE
  btn1State = 200;
  btn2State = 200;
  btn3State = 200;
  btn4State = 200;
  }

  if(CMDID == 103) { // TURN ON THE LIGHT
  btn1State = 100;
  }
  
  if(CMDID == 104) {  // TURN OFF THE LIGHT
  btn1State = 200;
  }

  if(CMDID == 7) { // POWER ON
  btn4State = 100;
  }
  
  if(CMDID == 8) {  // POWER OFF
  btn4State = 200;
  }

  if(CMDID == 9) { // SOLDER ON
  btn3State = 100;
  }
  
  if(CMDID == 10) {  // SOLDER OFF
  btn3State = 200;
  }

  if(CMDID == 80) { // START OSCILLATING
  btn2State = 100;
  }
  
  if(CMDID == 81) {  // STOP OSCILLATING
  btn2State = 200;
  }

  if(CMDID == 73) { // TURN ON THE CAMERA // GPIO 14
  digitalWrite(camera, HIGH);
  }
  
  if(CMDID == 74) {  // TURN OFF THE CAMERA
  digitalWrite(camera, LOW);
  }

  
  if(CMDID == 90) { // TURN ON THE SPEAKER  // GPIO 12
  digitalWrite(speaker, HIGH);
  }
  
  if(CMDID == 91) {  // TURN OFF THE SPEAKER
  digitalWrite(speaker, LOW);
  }
  
  
structObj.a = btn1State; 
structObj.b = btn2State; 
structObj.c = btn3State; 
structObj.d = btn4State; 



// Send message via ESP-NOW
esp_now_send(broadcastAddress, (uint8_t *) &structObj, sizeof(structObj));

delay(1000);

}
