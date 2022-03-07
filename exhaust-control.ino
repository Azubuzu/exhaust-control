#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // SRX | STX
// D2 pin of NANO is SRX-pin of NANO; it will have connection with TX-pin of HC-05 
// D3 pin of NANO is STX-pin of NANO; it will have connection with RX-pin of HC-05 via voltage divider.
 
char c = ' '; //initializes to a space
 
void setup() 
{
    Serial.begin(9600);
    Serial.println("Arduino is ready");
 
    // HC-05 default serial speed for communication mode is 9600
    BTserial.begin(9600);  
    Serial.println("BTserial started at 9600");
}
 
void loop()
{
   // Keep reading from HC-05 and send to Arduino Serial Monitor


    if (BTserial.available())
    {  
        c = BTserial.read();
        Serial.write(c);
    }
 
   // Keep reading from Arduino Serial Monitor and send to HC-05
    if (Serial.available())
    {
        c =  Serial.read();
 
        // Copy the serial data back to to the serial monitor. 
        // This makes it easy to follow the commands and replies
        Serial.write(c);
        BTserial.write(c);  
    }
 
}
