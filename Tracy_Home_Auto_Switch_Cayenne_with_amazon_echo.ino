

//#define CAYENNE_DEBUG         // Uncomment to show debug messages
#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space

#include "CayenneDefines.h"
#include "BlynkSimpleEsp8266.h"
#include "CayenneWiFiClient.h"

#include "fauxmoESP.h"


// Cayenne authentication token. This should be obtained from the Cayenne Dashboard.
char token[] = “——“;
// Your network name and password.
char ssid[] = “——“;
char password[] = “————“;


//-------- rcswitch------
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();


int ConnectionCount = 0;

int stanley_bit_size = 32;
int wood_chA_bit_size = 15;

unsigned long stanley_switch_on[3] = {2585788855, 2585789111, 2585789367};  
unsigned long stanley_switch_off[3] = {2585788823, 2585789079, 2585789335};

unsigned long wood_chA_switch_on[3] = {13380, 13332, 13444};  
unsigned long wood_chA_switch_off[3] = {13348, 13324, 13572};


char *switch_name[] = {"MySwitch",
                       "Fireplace Light",
                       "Master Bedroom Light",
                       "Front Door Lamp",                  
                       "Family Room Lamp",
                       "Office Heater"
                       };

int stanley_pulse = 350;
int wood_chA_pulse = 181;


//int stanley_pulse = 325;
//int wood_chA_pulse = 151;

int stanley_switch_state[3] = {1,1,1};
int wood_chA_switch_state[3] = {1,1,1};

// This flag is used so the sync only happens on the first connection.
bool isFirstConnect = true;


// Initialize here for Amazon Echo's emulation with WEMO.
fauxmoESP fauxmo;
int num_devices = 8;
char *device[] = { "beadroom heater one",
                   "fireplace",
                   "master bedroom",
                   "front door",
                   "family room",
                   "bedroom heater two",
                   "all heater",
                   "all lights"
                   };

                   


void setup()
{
	Serial.begin(9600);
	Serial.println("Cayenne starting ...");
	Cayenne.begin(token, ssid, password);
  Serial.println("Cayenne finished connecting to Internet.");

  ConnectionCount++;
  
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);
  
  mySwitch.enableTransmit(16); // pin GP013
  mySwitch.setRepeatTransmit(20);

  // Configure Fauxmo here
  for(int i=0; i<num_devices; i++ ) {
      Serial.print("Adding device ");
      Serial.print(device[i]);
      Serial.println(" to WeMo network");
      fauxmo.addDevice( device[i] );
      delay(100);
  }
  fauxmo.onMessage(callback);
  Serial.println("All Devices added to WeMo network, start Echo discovery now.");


  digitalWrite(5, HIGH);
  digitalWrite(0, HIGH);
}

void loop()
{
       
	Cayenne.run();
}



BLYNK_WRITE(V0) {

  digitalWrite(4, HIGH);
  int pinData = param.asInt();

  Serial.print ("Switch pressed on V0 - "); 
  Serial.print (switch_name[0]);
  Serial.print (" to "); 
  Serial.println (pinData);

  stanley_switch_state[0] = pinData;

  mySwitch.setPulseLength(stanley_pulse);
  if( pinData == 1 ){
    mySwitch.send(stanley_switch_on[0], stanley_bit_size );
    Blynk.virtualWrite(V0, HIGH);
  }
  else {
    mySwitch.send(stanley_switch_off[0], stanley_bit_size );
    Blynk.virtualWrite(V0, LOW);
  }
  delay(100);
  digitalWrite(4, LOW);
}

//For Stanley Switch #2
BLYNK_WRITE(V1) {

  digitalWrite(4, HIGH);
  int pinData = param.asInt();

  Serial.print ("Switch pressed on V1 - "); 
  Serial.print (switch_name[1]);
  Serial.print (" to "); 
  Serial.println (pinData);

  stanley_switch_state[1] = pinData;

  mySwitch.setPulseLength(stanley_pulse);
  if( pinData == 1 ){
    mySwitch.send(stanley_switch_on[1], stanley_bit_size );
    Blynk.virtualWrite(V1, HIGH);
  }
  else {
    mySwitch.send(stanley_switch_off[1], stanley_bit_size );
    Blynk.virtualWrite(V1, LOW);
  }
  delay(100);
  digitalWrite(4, LOW);
}

//For Stanley Switch #3
BLYNK_WRITE(V2) { 

  digitalWrite(4, HIGH);
  int pinData = param.asInt();

  Serial.print ("Switch pressed on V2 - "); 
  Serial.print (switch_name[2]);
  Serial.print (" to "); 
  Serial.println (pinData);

  stanley_switch_state[2] = pinData;

  mySwitch.setPulseLength(stanley_pulse);
  if( pinData == 1 ){
    mySwitch.send(stanley_switch_on[2], stanley_bit_size );
    Blynk.virtualWrite(V2, HIGH);
  }
  else {
    mySwitch.send(stanley_switch_off[2], stanley_bit_size );
    Blynk.virtualWrite(V2, LOW);
  }
  delay(100);
  digitalWrite(4, LOW);
}

//For Wood Channel A switch #1
BLYNK_WRITE(V3) {

  digitalWrite(4, HIGH);
  int pinData = param.asInt();

  Serial.print ("Switch pressed on V3 - "); 
  Serial.print (switch_name[3]);
  Serial.print (" to "); 
  Serial.println (pinData);

  wood_chA_switch_state[0] = pinData;

  mySwitch.setPulseLength(wood_chA_pulse);
  if( pinData == 1 ){
    mySwitch.send(wood_chA_switch_on[0], wood_chA_bit_size );
    Blynk.virtualWrite(V3, HIGH);
  }
  else {
    mySwitch.send(wood_chA_switch_off[0], wood_chA_bit_size );
    Blynk.virtualWrite(V3, LOW);
  }
  delay(100);
  digitalWrite(4, LOW);
}

//For Wood Channel A switch #2
BLYNK_WRITE(V4) {

  digitalWrite(4, HIGH);
  int pinData = param.asInt();

  Serial.print ("Switch pressed on V4 - "); 
  Serial.print (switch_name[4]);
  Serial.print (" to "); 
  Serial.println (pinData);

  wood_chA_switch_state[1] = pinData;

  mySwitch.setPulseLength(wood_chA_pulse);
  if( pinData == 1 ){
    mySwitch.send(wood_chA_switch_on[1], wood_chA_bit_size );
    Blynk.virtualWrite(V4, HIGH);
  }
  else {
    mySwitch.send(wood_chA_switch_off[1], wood_chA_bit_size );
    Blynk.virtualWrite(V4, LOW);
  }
  delay(100);
  digitalWrite(4, LOW);
}

//For Wood Channel A switch #3
BLYNK_WRITE(V5) {

  digitalWrite(4, HIGH);
  int pinData = param.asInt();

  Serial.print ("Switch pressed on V5 - "); 
  Serial.print (switch_name[5]);
  Serial.print (" to "); 
  Serial.println (pinData);

  wood_chA_switch_state[2] = pinData;

  mySwitch.setPulseLength(wood_chA_pulse);
  if( pinData == 1 ){
    mySwitch.send(wood_chA_switch_on[2], wood_chA_bit_size );
    Blynk.virtualWrite(V5, HIGH);
  }
  else {
    mySwitch.send(wood_chA_switch_off[2], wood_chA_bit_size );
    Blynk.virtualWrite(V5, LOW);
  }
  delay(100);
  digitalWrite(4, LOW);
}

CAYENNE_OUT(V20)
{
  Cayenne.virtualWrite(V20, ConnectionCount, UNDEFINED, UNDEFINED);
}


// This function will run every time the Cayenne connection is established.
CAYENNE_CONNECTED()
{
  digitalWrite(5, LOW);  
  digitalWrite(0, LOW); 
  delay(1000);
  digitalWrite(5, HIGH); 
  digitalWrite(0, HIGH); 
  delay(1500);
  digitalWrite(5, LOW);  
  digitalWrite(0, LOW); 
  delay(1000);

  CAYENNE_LOG("Connection established");
  Serial.println("Connection established to Cayenne.");
  if (isFirstConnect)
  {
    // This causes Cayenne to resend data for any virtual pins.
//    Cayenne.syncAll();
    isFirstConnect = false;
    Serial.println("Connected to Cayenne for the first time!" );
    digitalWrite(5, HIGH);  
    digitalWrite(0, HIGH);  
    delay(500);
    digitalWrite(5, LOW);  
    digitalWrite(0, LOW);   
    delay(500);
    digitalWrite(5, HIGH);  
    digitalWrite(0, HIGH); 
    delay(500);
    digitalWrite(5, LOW);    
    digitalWrite(0, LOW);
    delay(500);
  }
  digitalWrite(5, HIGH);
  digitalWrite(0, HIGH);

  ConnectionCount++;
}




void callback(const char * device_name, bool state) {
  Serial.print("Device "); Serial.print(device_name); 
  Serial.print(" state: ");
  if (state) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  if( strcmp( device_name , device[0]) == 0  ) {
    Serial.print("Sending signal to ..." );
    Serial.println(device[0]); 
    mySwitch.setPulseLength(stanley_pulse);
    if( !state ) {
      mySwitch.send(stanley_switch_off[0], stanley_bit_size );
      Blynk.virtualWrite(V0, LOW);
    }
    else {
      mySwitch.send(stanley_switch_on[0], stanley_bit_size );
      Blynk.virtualWrite(V0, HIGH);
    }
  }
  else if( strcmp( device_name, device[1] ) == 0 ) {
    Serial.print("Sending signal to ..." );
    Serial.println(device[1]);
    mySwitch.setPulseLength(stanley_pulse);
    if( !state ) {
      mySwitch.send(stanley_switch_off[1], stanley_bit_size );
      Blynk.virtualWrite(V1, LOW);
    }
    else {
      mySwitch.send(stanley_switch_on[1], stanley_bit_size );
      Blynk.virtualWrite(V1, HIGH);
    }
  }
  else if( strcmp( device_name, device[2] ) == 0 ) {
    Serial.print("Sending signal to ..." );
    Serial.println(device[2]);
    mySwitch.setPulseLength(stanley_pulse);
    if( !state ) {
      mySwitch.send(stanley_switch_off[2], stanley_bit_size );
      Blynk.virtualWrite(V2, LOW);
    }
    else {
      mySwitch.send(stanley_switch_on[2], stanley_bit_size );
      Blynk.virtualWrite(V2, HIGH);
    }    
  }
  else if( strcmp( device_name, device[3] ) == 0 ) {
    Serial.print("Sending signal to ..." );
    Serial.println(device[3]);
    mySwitch.setPulseLength(wood_chA_pulse);;
    if( !state ) {
      mySwitch.send(wood_chA_switch_off[0], wood_chA_bit_size );
      Blynk.virtualWrite(V3, LOW);
    }
    else {
      mySwitch.send(wood_chA_switch_on[0], wood_chA_bit_size );
      Blynk.virtualWrite(V3, HIGH);
    }
  }  
  else if( strcmp( device_name, device[4] ) == 0 ) {
    Serial.print("Sending signal to ..." );
    Serial.println(device[4]);
    mySwitch.setPulseLength(wood_chA_pulse);;
    if( !state ) {
      mySwitch.send(wood_chA_switch_off[1], wood_chA_bit_size );
      Blynk.virtualWrite(V4, LOW);
    }
    else {
      mySwitch.send(wood_chA_switch_on[1], wood_chA_bit_size );
      Blynk.virtualWrite(V4, HIGH);
    }
  }
  else if( strcmp( device_name, device[5] ) == 0 ) {
    Serial.print("Sending signal to ..." );
    Serial.println(device[5]);
    mySwitch.setPulseLength(wood_chA_pulse);;
    if( !state ) {
      mySwitch.send(wood_chA_switch_off[2], wood_chA_bit_size );
      Blynk.virtualWrite(V5, LOW);
    }
    else {
      mySwitch.send(wood_chA_switch_on[2], wood_chA_bit_size );
      Blynk.virtualWrite(V5, HIGH);
    }
  }
  // "all heater"
  else if( strcmp( device_name, device[6] ) == 0 ) {
    Serial.print("Sending signal to all heater" );
    //Serial.println(device[5]);
    mySwitch.setPulseLength(wood_chA_pulse);;
    if( !state ) {
      mySwitch.send(wood_chA_switch_off[2], wood_chA_bit_size );
      Blynk.virtualWrite(V5, LOW);
    }
    else {
      mySwitch.send(wood_chA_switch_on[2], wood_chA_bit_size );
      Blynk.virtualWrite(V5, HIGH);
    }
    delay(500);
    mySwitch.setPulseLength(stanley_pulse);
    if( !state ) {
      mySwitch.send(stanley_switch_off[0], stanley_bit_size );
      Blynk.virtualWrite(V0, LOW);
    }
    else {
      mySwitch.send(stanley_switch_on[0], stanley_bit_size );
      Blynk.virtualWrite(V0, HIGH);
    }

  }
  //"all lights"
  else if( strcmp( device_name, device[7] ) == 0 ) {
    Serial.println("Sending signal to all lights" );
    mySwitch.setPulseLength(stanley_pulse);
    if( !state ) {
      mySwitch.send(stanley_switch_off[1], stanley_bit_size );
      Blynk.virtualWrite(V1, LOW);
    }
    else {
      mySwitch.send(stanley_switch_on[1], stanley_bit_size );
      Blynk.virtualWrite(V1, HIGH);
    }
    delay(100);
    if( !state ) {
      mySwitch.send(stanley_switch_off[2], stanley_bit_size );
      Blynk.virtualWrite(V2, LOW);
    }
    else {
      mySwitch.send(stanley_switch_on[2], stanley_bit_size );
      Blynk.virtualWrite(V2, HIGH);
    }    
    delay(100);
    mySwitch.setPulseLength(wood_chA_pulse);;
    if( !state ) {
      mySwitch.send(wood_chA_switch_off[0], wood_chA_bit_size );
      Blynk.virtualWrite(V3, LOW);
    }
    else {
      mySwitch.send(wood_chA_switch_on[0], wood_chA_bit_size );
      Blynk.virtualWrite(V3, HIGH);
    }
    delay(100);
    if( !state ) {
      mySwitch.send(wood_chA_switch_off[1], wood_chA_bit_size );
      Blynk.virtualWrite(V4, LOW);
    }
    else {
      mySwitch.send(wood_chA_switch_on[1], wood_chA_bit_size );
      Blynk.virtualWrite(V4, HIGH);
    }    
  }
  else {
    Serial.print("Unrecognized command ");
    Serial.println(device_name);
  }
  
}

