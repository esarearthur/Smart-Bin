#define TINY_GSM_MODEM_SIM800

#include <TinyGsmClient.h>
#include <PubSubClient.h>

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Use Hardware Serial on Mega, Leonardo, Micro
//#define SerialAT Serial1

// or Software Serial on Uno, Nano
#include <SoftwareSerial.h>
SoftwareSerial SerialAT(2, 3); // RX, TX

//#include <StreamDebugger.h>
//StreamDebugger debugger(SerialAT, SerialMon);
//TinyGsm modem(debugger);

TinyGsm modem(SerialAT);

#define LED_PIN 13
int ledStatus = LOW;

int unreadSMSLocs[20];
int unreadSMSNum;
struct SMSmessage sms;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);

  // Set console baud rate
  SerialMon.begin(9600);
  delay(10);

  // Set GSM module baud rate
  SerialAT.begin(9600);
  delay(3000);

  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  modem.restart();

  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem: ");
  SerialMon.println(modemInfo);

  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");

  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" fail");
    while (true);
  }
  SerialMon.println(" OK");

  if(modem.sendSMS("+233267766253", "HELLO"))
    Serial.println("Sent SMS");
   else
    Serial.println("Failed");

  unreadSMSNum = modem.getUnreadSMSLocs(unreadSMSLocs);
        
  for(int j = 0; j < unreadSMSNum; ++j){
    sms = modem.readSMS(unreadSMSLocs[j]);
    Serial.println(sms.message);
  }
}

long pdt = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() - pdt > 5000){
    memset(unreadSMSLocs, 0x00, sizeof(unreadSMSLocs));
    unreadSMSNum = modem.getUnreadSMSLocs(unreadSMSLocs);
    if(unreadSMSNum > 0){
      for(int j = 0; j < unreadSMSNum; ++j){
        sms = modem.readSMS(unreadSMSLocs[j]);
        Serial.print("New message: ");
        Serial.println(sms.message);
  
        if(!strcmp("open", sms.message){
          
        }
      }
    }
  }
}
