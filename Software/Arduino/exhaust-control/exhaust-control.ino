#include <SoftwareSerial.h>
// Configurations ///////////////////////////////////////////////////////////////
#define BT_TX 3
#define BT_RX 2
#define MOSFET_POWER 5
#define MOSFET_CONTROL 4 //Logic is inverted for this mosfet
#define FULL_CYCLE_MS 1300
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

    // Setting up the nano pin to output for the mosfet control
    pinMode(MOSFET_POWER, OUTPUT);
    pinMode(MOSFET_CONTROL, OUTPUT);
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
          BTserial.println("valve_open received");
          openValve();
          BTserial.println("valve_open OK");
          log("Valve opened");
        }

        if (code.equals("valve_close")) {
          BTserial.println("valve_close received");
          closeValve();
          BTserial.println("valve_close OK");
          log("Valve closed");
        }

        if (code.startsWith("valve_open_ms")) {
          BTserial.println("valve_open_ms " + code.substring(14) + " received");
          openValveFor(code.substring(14));
          BTserial.println("valve_open_ms " + code.substring(14) + " OK");
          log("Valve opened for " + code.substring(14) + " ms");
        }
    } 
}

/**
 * Open the valve and let it that way
 */
void openValve() {
    digitalWrite(MOSFET_CONTROL, LOW);
    digitalWrite(MOSFET_POWER, HIGH);
}

/**
 * Close the valve and let it that way
 */
void closeValve() {
    digitalWrite(MOSFET_CONTROL, HIGH);
    digitalWrite(MOSFET_POWER, HIGH);
}

/**
 * Cut the valve alimentation in order to stop the valve were it is
 */
void stopValve() {
    digitalWrite(MOSFET_POWER, LOW);
    digitalWrite(MOSFET_CONTROL, HIGH);
}

/**
 * Open the valve for the given time in ms
 */
void openValveFor(String ms) {

    int openFor = ms.toInt();

    if (openFor == 0) {
        return;
    }
    
    closeValve();
    delay(FULL_CYCLE_MS);
    openValve();
    delay(openFor);
    stopValve();
}

/**
* Open the valve then cut the alimentation in order to save power
*/
void openValveThenIdle() {
    openValve();
    delay(FULL_CYCLE_MS);
    stopValve();
}

/**
* Close the valve then cut the alimentation in order to save power
*/
void closeValveThenIdle() {
    closeValve();
    delay(FULL_CYCLE_MS);
    stopValve();
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
