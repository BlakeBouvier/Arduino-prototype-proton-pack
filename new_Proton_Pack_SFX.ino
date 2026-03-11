#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>



int DFPrx = 9;
int DFPtx = 8;

SoftwareSerial mySerial(DFPtx, DFPrx);
DFRobotDFPlayerMini myDFP;


int onPin = 5;
int firePin = 6;

int lastOnState = 1;
int lastFireState = 1;

int lastDelay = 0;

// #define ON true;
// #define OFF false;

bool POWER = false;
bool FIRING = false;


void setup() {

  pinMode(onPin, INPUT_PULLUP);
  pinMode(firePin, INPUT_PULLUP);

  Serial.begin(9600);
  mySerial.begin(9600);

  
  delay(1500);


  if(!myDFP.begin(mySerial)){
      Serial.println("DFP not initalized");
      while(true);
  }

  delay(1600);
  myDFP.volume(25);
}


void loop() {
  
  int onState = digitalRead(onPin);
  
  if(onState != lastOnState && millis() - lastDelay > 300) {
    if(onState < 1) {
      Serial.println('1');

      myDFP.play(1);
    
      POWER = true;

    } else {
      Serial.println('0');

      myDFP.play(2);

      POWER = false;
    }
    lastOnState = digitalRead(onPin);
    delay(300);
    lastDelay = millis();
  }

  if(POWER == true) {
    int fireState = digitalRead(firePin);
    
    if (fireState != lastFireState && millis() - lastDelay > 1000) {
      if(fireState < 1){
        Serial.println('2');

        myDFP.play(3);
        delay(1200);

        FIRING = true;
        if(fireState<1){
          myDFP.loop(4);
        }
      }
      if(fireState>0){
        Serial.println('1');

        myDFP.play(5);

        FIRING = false;
      }
      lastFireState = digitalRead(firePin);
      delay(1000);
      lastDelay = millis();
    }
  }
}


