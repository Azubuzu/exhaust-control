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
        String s = BTserial.readStringUntil('\r\n');
        s.trim();
        Serial.println(s);

        if(s == "valve_open") {
          BTserial.println("valve_open reveived");
          Serial.println("valve_open reveived");
        }
    } 
}
