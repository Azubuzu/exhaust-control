#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // SRX | STX
// D2 pin of NANO is SRX-pin of NANO; it will have connection with TX-pin of HC-05 
// D3 pin of NANO is STX-pin of NANO; it will have connection with RX-pin of HC-05 via voltage divider.

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
          BTserial.println("valve_open_ms OK");
          log("Valve opened for " + code.substring(14) + " ms");
        }
    } 
}

/**
* Read string from bluetooth, stop reading when '\r\n' is detected
* Return trimmed received string
*/
String btReadStringAndClean() {
  String s = BTserial.readStringUntil('\r\n');
  s.trim();
  return s;
}

/**
* Log a message to the serial port of the arduino
*/
void log(String msg) {
  Serial.println(msg);
}