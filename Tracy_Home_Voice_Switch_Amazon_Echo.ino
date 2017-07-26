#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"

#include <RCSwitch.h>

#define WIFI_SSID “——“
#define WIFI_PASS “——————“
#define SERIAL_BAUDRATE                 115200

fauxmoESP fauxmo;


RCSwitch mySwitch = RCSwitch();

int stanley_bit_size = 32;
int wood_chA_bit_size = 15;

unsigned long stanley_switch_on[3] = {2585788855, 2585789111, 2585789367};  
unsigned long stanley_switch_off[3] = {2585788823, 2585789079, 2585789335};

unsigned long wood_chA_switch_on[3] = {13380, 13332, 13444};  
unsigned long wood_chA_switch_off[3] = {13348, 13324, 13572};

int stanley_pulse = 350;
int wood_chA_pulse = 151;

//int stanley_switch_state[3] = {1,1,1};
//int wood_chA_switch_state[3] = {1,1,1};

int num_devices = 6;
char *device[] = { "beadroom heater one",
                   "fireplace",
                   "master bedroom",
                   "front door",
                   "family room",
                   "bedroom heater two",
                   "all heater",
                   "all lights"
                   };


//char *device[] = { "office switch",
//                   "fireplace",
//                   "master bedroom",
//                   "front door",
//                   "family room",
//                   "office heater"
//                   };

// -----------------------------------------------------------------------------
// Wifi
// -----------------------------------------------------------------------------

void wifiSetup() {

    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);

    // Connect
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Wait
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();

    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());




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
//      stanley_switch_state[0] = 0;
      mySwitch.send(stanley_switch_off[0], stanley_bit_size );
    }
    else {
//    stanley_switch_state[0] = 1;
    mySwitch.send(stanley_switch_on[0], stanley_bit_size );
    }
  }
  else if( strcmp( device_name, device[1] ) == 0 ) {
    Serial.print("Sending signal to ..." );
    Serial.println(device[1]);
    mySwitch.setPulseLength(stanley_pulse);
    if( !state ) {
//      stanley_switch_state[1] = 0;
      mySwitch.send(stanley_switch_off[1], stanley_bit_size );
    }
    else {
//      stanley_switch_state[1] = 1;
      mySwitch.send(stanley_switch_on[1], stanley_bit_size );
    }
  }
  else if( strcmp( device_name, device[2] ) == 0 ) {
    Serial.print("Sending signal to ..." );
    Serial.println(device[2]);
    mySwitch.setPulseLength(stanley_pulse);
    if( !state ) {
//      stanley_switch_state[2] = 0;
      mySwitch.send(stanley_switch_off[2], stanley_bit_size );
    }
    else {
//      stanley_switch_state[2] = 1;
      mySwitch.send(stanley_switch_on[2], stanley_bit_size );
    }    
  }
  else if( strcmp( device_name, device[3] ) == 0 ) {
    Serial.print("Sending signal to ..." );
    Serial.println(device[3]);
    mySwitch.setPulseLength(wood_chA_pulse);;
    if( !state ) {
//      wood_chA_switch_state[0] = 0;
      mySwitch.send(wood_chA_switch_off[0], wood_chA_bit_size );
    }
    else {
//      wood_chA_switch_state[0] = 1;
      mySwitch.send(wood_chA_switch_on[0], wood_chA_bit_size );
    }
  }  
  else if( strcmp( device_name, device[4] ) == 0 ) {
    Serial.print("Sending signal to ..." );
    Serial.println(device[4]);
    mySwitch.setPulseLength(wood_chA_pulse);;
    if( !state ) {
//      wood_chA_switch_state[1] = 0;
      mySwitch.send(wood_chA_switch_off[1], wood_chA_bit_size );
    }
    else {
//      wood_chA_switch_state[1] = 1;
      mySwitch.send(wood_chA_switch_on[1], wood_chA_bit_size );
    }
  }
  else if( strcmp( device_name, device[5] ) == 0 ) {
    Serial.print("Sending signal to ..." );
    Serial.println(device[5]);
    mySwitch.setPulseLength(wood_chA_pulse);;
    if( !state ) {
//      wood_chA_switch_state[2] = 0;
      mySwitch.send(wood_chA_switch_off[2], wood_chA_bit_size );
    }
    else {
//      wood_chA_switch_state[2] = 1;
      mySwitch.send(wood_chA_switch_on[2], wood_chA_bit_size );
    }
  }
  // "all heater"
  else if( strcmp( device_name, device[6] ) == 0 ) {
    Serial.print("Sending signal to all heater" );
    //Serial.println(device[5]);
    mySwitch.setPulseLength(wood_chA_pulse);;
    if( !state ) {
      mySwitch.send(wood_chA_switch_off[2], wood_chA_bit_size );
    }
    else {
      mySwitch.send(wood_chA_switch_on[2], wood_chA_bit_size );
    }
    mySwitch.setPulseLength(stanley_pulse);
    if( !state ) {
      mySwitch.send(stanley_switch_off[0], stanley_bit_size );
    }
    else {
      mySwitch.send(stanley_switch_on[0], stanley_bit_size );
    }

  }
  //"all lights"
  else if( strcmp( device_name, device[7] ) == 0 ) {
    Serial.println("Sending signal to all lights" );
    mySwitch.setPulseLength(stanley_pulse);
    if( !state ) {
      mySwitch.send(stanley_switch_off[1], stanley_bit_size );
    }
    else {
      mySwitch.send(stanley_switch_on[1], stanley_bit_size );
    }
    delay(100);
    if( !state ) {
      mySwitch.send(stanley_switch_off[2], stanley_bit_size );
    }
    else {
      mySwitch.send(stanley_switch_on[2], stanley_bit_size );
    }    
    delay(100);
    mySwitch.setPulseLength(wood_chA_pulse);;
    if( !state ) {
      mySwitch.send(wood_chA_switch_off[0], wood_chA_bit_size );
    }
    else {
      mySwitch.send(wood_chA_switch_on[0], wood_chA_bit_size );
    }
    delay(100);
    if( !state ) {
      mySwitch.send(wood_chA_switch_off[1], wood_chA_bit_size );
    }
    else {
      mySwitch.send(wood_chA_switch_on[1], wood_chA_bit_size );
    }    
  }
  else {
    Serial.print("Unrecognized command ");
    Serial.println(device_name);
  }
  
}

void setup() {

    
    mySwitch.enableTransmit(0); 
    mySwitch.setRepeatTransmit(20);
    
    

    // Init serial port and clean garbage
    Serial.begin(SERIAL_BAUDRATE);
    delay(1000);
    Serial.println("Enabled RCSwitch Transmitter ... done." );

    Serial.println("FauxMo demo sketch");
    Serial.println("After connection, ask Alexa/Echo to 'turn <devicename> on' or 'off'");

    // Wifi
    wifiSetup();

//    mySwitch.enableTransmit(0); // pin GP013
//    mySwitch.setRepeatTransmit(20);

    // Fauxmo

    for(int i=0; i<num_devices; i++ ) {
      Serial.print("Adding device ");
      Serial.print(device[i]);
      Serial.println(" to WeMo network");
      fauxmo.addDevice( device[i] );
      delay(100);
    }
    fauxmo.onMessage(callback);
    Serial.println("All Devices added to WeMo network, start Echo discovery now.");
    /*
    fauxmo.addDevice("room light");
    fauxmo.addDevice("christmas tree");
    fauxmo.addDevice("fireplace");
    fauxmo.addDevice("front door lamp");
    fauxmo.addDevice("family room");
    fauxmo.addDevice("office heater");
    fauxmo.addDevice("all light");
    */
    

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

void loop() {
}
