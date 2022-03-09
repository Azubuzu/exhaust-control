#include <SoftwareSerial.h>
// Configurations ///////////////////////////////////////////////////////////////
#define BT_TX 2
#define BT_RX 3
#define MOSFET_ALIM 4
#define MOSFET_CONTROL 5
/////////////////////////////////////////////////////////////////////////////////
SoftwareSerial BTserial(BT_TX, BT_RX); // (Nano RX , Nano TX)
/**
 * Init setup
 */
void setup() {
    // Setting up COM terminal for debugging
    Serial.begin(9600);
    Serial.println("Arduino is ready");
 
    // HC-05 default serial speed for communication mode is 9600
    BTserial.begin(9600);  
    Serial.println("BTserial started at 9600");
}

/**
 * Main loop
 */
void loop() {
   // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available()) {  
        String code = btReadStringAndClean();
        log(code + " reveived");

        if (code.equals("valve_open")) {
          BTserial.println("valve_open OK");
          log("Valve opened");
        }

        if (code.equals("valve_close")) {
          BTserial.println("valve_close OK");
          log("Valve closed");
        }

        if (code.startsWith("valve_open_ms")) {
          BTserial.println("valve_open_ms " + code.substring(14) + " OK");
          log("Valve opened for " + code.substring(14) + " ms");
        }
    } 
}

/**
* Read string from bluetooth, stop reading when '\n' is detected
* Return trimmed received string
*/
String btReadStringAndClean() {
  String s = BTserial.readStringUntil('\n');
  s.trim();
  return s;
}

/**
* Log a message to the serial port of the arduino
*/
void log(String msg) {
  Serial.println(msg);
}
