#define PIN_MOTOR 6

int numCharsReceived = 0;
const int maxChars = 18;
char receivedStr[maxChars];
int incomingByte = 0;
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  // // put your setup code here, to run once:
  // pinMode(19, INPUT);
  // pinMode(18, OUTPUT);
  // pinMode(LED_BUILTIN, OUTPUT);
  // // mySerial.begin(9600);
  // servo.attach(PIN_MOTOR,1148,1832);
  // servo.writeMicroseconds(1100);
  // delay(2000);
  // servo.writeMicroseconds(1000);
}


void loop() {
  // mySerial.listen();
  // Serial.println(Serial1.peek(), HEX);

  Serial1.write('w');
  
  if (Serial1.available() > 0) {
        char c = Serial1.read();
        // Serial.println(c);
        if (receivedStr[strlen(receivedStr) - 1] == '\r') { //if '\r' found
                receivedStr[strlen(receivedStr) - 1] = '\0'; // remove by overwriting with null terminator
        }
        if (c == '\n' || numCharsReceived == maxChars){
          Serial.println(receivedStr);
          receivedStr[0] = '\0';
          numCharsReceived = 0;
        } else {
          receivedStr[numCharsReceived] = c;
          receivedStr[numCharsReceived + 1] = '\0';
          numCharsReceived++;
        }
  }
  
  // Serial.println(mySerial.isListening());

}
