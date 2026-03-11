/****************************************************************************
**
** Arduino Ghostbusters Proton Pack Project
** Electronics Kit Shop   2025
** you may use this file freely and without restriction
*/

/****************************************************************************
**
** LED output drive port pins. You can change these if you want
*/

#define POWER_CELL_LED_1_OUTPUT_PIN  2  
#define POWER_CELL_LED_2_OUTPUT_PIN  3
#define POWER_CELL_LED_3_OUTPUT_PIN  4
#define POWER_CELL_LED_4_OUTPUT_PIN  5
#define POWER_CELL_LED_5_OUTPUT_PIN  6
#define POWER_CELL_LED_6_OUTPUT_PIN  7
#define POWER_CELL_LED_7_OUTPUT_PIN  8
#define POWER_CELL_LED_8_OUTPUT_PIN  9
#define POWER_CELL_LED_9_OUTPUT_PIN  10
#define POWER_CELL_LED_10_OUTPUT_PIN 11

#define CYCLOTRON_LED_1_OUTPUT_PIN   14
#define CYCLOTRON_LED_2_OUTPUT_PIN   15
#define CYCLOTRON_LED_3_OUTPUT_PIN   16
#define CYCLOTRON_LED_4_OUTPUT_PIN   17

#define WAND_ORANGE_LED_OUTPUT_PIN  18
#define WAND_RED_LED_OUTPUT_PIN  12
#define WAND_WHITE_LED_OUTPUT_PIN 13


/****************************************************************************
**
** LED output control
*/
#define LED_OFF   0 // writing 0 to the LED turns it OFF
#define LED_ON    1 // writing 1 to the LED turns it ON

/****************************************************************************
**
** LED sequence control
*/
static uint8_t PowerCell_LED_SequenceCounter;
static uint8_t Cyclotron_LED_SequenceCounter;

#define POWER_CELL_LED_TIME_INTERVAL_MS  100  // the time between steps of the Power Cell sequence
#define POWER_CELL_LED_TIME_INTERVAL_MS_FIRING 30

/****************************************************************************/
// communication values
// when a rx pin on the light control board recieves these values they
// equivalate to a status of the pack and should begin a certain light
// sequence to reflect that
// 0 - OFF
// 1 - power
// 2 - firing




bool POWER = false;
bool FIRING = false;


char incomingByte = '0';
char lastByte = '0';


//the setup function runs once when you press reset or power the board

void setup() {
  Serial.begin(9600);
  /* initialise sequence counters */
  PowerCell_LED_SequenceCounter = 1;
  Cyclotron_LED_SequenceCounter = 1;

  /* initialise all LED outputs to be OFF */
  digitalWrite(POWER_CELL_LED_1_OUTPUT_PIN, LED_OFF);
  digitalWrite(POWER_CELL_LED_2_OUTPUT_PIN, LED_OFF);
  digitalWrite(POWER_CELL_LED_3_OUTPUT_PIN, LED_OFF);
  digitalWrite(POWER_CELL_LED_4_OUTPUT_PIN, LED_OFF);
  digitalWrite(POWER_CELL_LED_5_OUTPUT_PIN, LED_OFF);
  digitalWrite(POWER_CELL_LED_6_OUTPUT_PIN, LED_OFF);
  digitalWrite(POWER_CELL_LED_7_OUTPUT_PIN, LED_OFF);
  digitalWrite(POWER_CELL_LED_8_OUTPUT_PIN, LED_OFF);
  digitalWrite(POWER_CELL_LED_9_OUTPUT_PIN, LED_OFF);
  digitalWrite(POWER_CELL_LED_10_OUTPUT_PIN, LED_OFF);

  digitalWrite(CYCLOTRON_LED_1_OUTPUT_PIN, LED_OFF);
  digitalWrite(CYCLOTRON_LED_2_OUTPUT_PIN, LED_OFF);
  digitalWrite(CYCLOTRON_LED_3_OUTPUT_PIN, LED_OFF);
  digitalWrite(CYCLOTRON_LED_4_OUTPUT_PIN, LED_OFF);
  
  digitalWrite(WAND_ORANGE_LED_OUTPUT_PIN, LED_OFF);
  digitalWrite(WAND_RED_LED_OUTPUT_PIN, LED_OFF);
  digitalWrite(WAND_WHITE_LED_OUTPUT_PIN, LED_OFF);

  /* make the LED drives as outputs */
  pinMode(POWER_CELL_LED_1_OUTPUT_PIN, OUTPUT);
  pinMode(POWER_CELL_LED_2_OUTPUT_PIN, OUTPUT);
  pinMode(POWER_CELL_LED_3_OUTPUT_PIN, OUTPUT);
  pinMode(POWER_CELL_LED_4_OUTPUT_PIN, OUTPUT);
  pinMode(POWER_CELL_LED_5_OUTPUT_PIN, OUTPUT);
  pinMode(POWER_CELL_LED_6_OUTPUT_PIN, OUTPUT);
  pinMode(POWER_CELL_LED_7_OUTPUT_PIN, OUTPUT);
  pinMode(POWER_CELL_LED_8_OUTPUT_PIN, OUTPUT);
  pinMode(POWER_CELL_LED_9_OUTPUT_PIN, OUTPUT);
  pinMode(POWER_CELL_LED_10_OUTPUT_PIN, OUTPUT);

  pinMode(CYCLOTRON_LED_1_OUTPUT_PIN, OUTPUT);
  pinMode(CYCLOTRON_LED_2_OUTPUT_PIN, OUTPUT);
  pinMode(CYCLOTRON_LED_3_OUTPUT_PIN, OUTPUT);
  pinMode(CYCLOTRON_LED_4_OUTPUT_PIN, OUTPUT);

  pinMode(WAND_ORANGE_LED_OUTPUT_PIN, OUTPUT);
  pinMode(WAND_RED_LED_OUTPUT_PIN, OUTPUT);
  pinMode(WAND_WHITE_LED_OUTPUT_PIN, OUTPUT);
}

/****************************************************************************
**
** the loop function runs over and over again until power down or reset
*/
void loop() {
  
  incomingByte = Serial.read();
  

    
  switch(incomingByte){
    case '1':
      POWER=true;
      FIRING=false;
      break;
    case '2':
      FIRING=true;
      break;
    case '0':
      POWER=false;
      FIRING=false;
      break;
  }
  

  
  
  if(POWER == true) {
    /* to begin with, only Power Cell LED 1 is ON, the rest are OFF */
    
    
    digitalWrite(WAND_ORANGE_LED_OUTPUT_PIN, HIGH);
    digitalWrite(WAND_RED_LED_OUTPUT_PIN, HIGH);

    
    
    if (PowerCell_LED_SequenceCounter == 1){
      /* Power Cell LED 1 is ON */
      digitalWrite(POWER_CELL_LED_1_OUTPUT_PIN, LED_ON); // only LED 1 is ON
      digitalWrite(POWER_CELL_LED_2_OUTPUT_PIN, LED_OFF);
      digitalWrite(POWER_CELL_LED_3_OUTPUT_PIN, LED_OFF);
      digitalWrite(POWER_CELL_LED_4_OUTPUT_PIN, LED_OFF);
      digitalWrite(POWER_CELL_LED_5_OUTPUT_PIN, LED_OFF);
      digitalWrite(POWER_CELL_LED_6_OUTPUT_PIN, LED_OFF);
      digitalWrite(POWER_CELL_LED_7_OUTPUT_PIN, LED_OFF);
      digitalWrite(POWER_CELL_LED_8_OUTPUT_PIN, LED_OFF);
      digitalWrite(POWER_CELL_LED_9_OUTPUT_PIN, LED_OFF);
      digitalWrite(POWER_CELL_LED_10_OUTPUT_PIN, LED_OFF);

      /* at the start of the Power Cell sequence, when only LED 1 is on,
      * we move on to the next LED in the Cyclotron sequence */
      Cyclotron_LED_SequenceCounter++;

      if (Cyclotron_LED_SequenceCounter > 4) // check for reaching the end of the 4 Cyclotron LEDs
      {
        Cyclotron_LED_SequenceCounter = 1; // back to the first Cyclotron LED
      }

      /* put all Cyclotron LEDs OFF, then turn ON only the one for this value
      ** of Cyclotron_LED_SequenceCounter */
      digitalWrite(CYCLOTRON_LED_1_OUTPUT_PIN, LED_OFF);
      digitalWrite(CYCLOTRON_LED_2_OUTPUT_PIN, LED_OFF);
      digitalWrite(CYCLOTRON_LED_3_OUTPUT_PIN, LED_OFF);
      digitalWrite(CYCLOTRON_LED_4_OUTPUT_PIN, LED_OFF);

      if (Cyclotron_LED_SequenceCounter == 1)
        digitalWrite(CYCLOTRON_LED_1_OUTPUT_PIN, LED_ON);

      else if (Cyclotron_LED_SequenceCounter == 2)
        digitalWrite(CYCLOTRON_LED_2_OUTPUT_PIN, LED_ON);

      else if (Cyclotron_LED_SequenceCounter == 3)
        digitalWrite(CYCLOTRON_LED_3_OUTPUT_PIN, LED_ON);

      else if (Cyclotron_LED_SequenceCounter == 4)
        digitalWrite(CYCLOTRON_LED_4_OUTPUT_PIN, LED_ON);
    }

    /* for subsequent values of PowerCell_LED_SequenceCounter, light up the next LED */
    else if (PowerCell_LED_SequenceCounter == 2)
      digitalWrite(POWER_CELL_LED_2_OUTPUT_PIN, LED_ON);
      
    else if (PowerCell_LED_SequenceCounter == 3)
      digitalWrite(POWER_CELL_LED_3_OUTPUT_PIN, LED_ON);
      
    else if (PowerCell_LED_SequenceCounter == 4)
      digitalWrite(POWER_CELL_LED_4_OUTPUT_PIN, LED_ON);

    else if (PowerCell_LED_SequenceCounter == 5)
      digitalWrite(POWER_CELL_LED_5_OUTPUT_PIN, LED_ON);

    else if (PowerCell_LED_SequenceCounter == 6)
      digitalWrite(POWER_CELL_LED_6_OUTPUT_PIN, LED_ON);

    else if (PowerCell_LED_SequenceCounter == 7)
      digitalWrite(POWER_CELL_LED_7_OUTPUT_PIN, LED_ON);

    else if (PowerCell_LED_SequenceCounter == 8)
      digitalWrite(POWER_CELL_LED_8_OUTPUT_PIN, LED_ON);

    else if (PowerCell_LED_SequenceCounter == 9)
      digitalWrite(POWER_CELL_LED_9_OUTPUT_PIN, LED_ON);

    else // it must be 10 then
      digitalWrite(POWER_CELL_LED_10_OUTPUT_PIN, LED_ON);

    /* move on to the next in the Power Cell sequence */
    PowerCell_LED_SequenceCounter++;

    if (PowerCell_LED_SequenceCounter > 10) // check for done all 10 Power Cell LEDs
    {
      PowerCell_LED_SequenceCounter = 1; // back to the start of the LEDs
    }

    



    /* delay before doing the next sequence of Power Cell LEDs */
    if(FIRING == true){

      delay(POWER_CELL_LED_TIME_INTERVAL_MS_FIRING);
      if(Cyclotron_LED_SequenceCounter%2==0) {
        digitalWrite(WAND_WHITE_LED_OUTPUT_PIN, HIGH);
      } else {
        digitalWrite(WAND_WHITE_LED_OUTPUT_PIN, LOW);
      }
      
    } else {
      delay(POWER_CELL_LED_TIME_INTERVAL_MS);
      digitalWrite(WAND_WHITE_LED_OUTPUT_PIN, LOW);
    }
  }
  else {
    digitalWrite(CYCLOTRON_LED_1_OUTPUT_PIN,LOW);
    digitalWrite(CYCLOTRON_LED_2_OUTPUT_PIN,LOW);
    digitalWrite(CYCLOTRON_LED_3_OUTPUT_PIN,LOW);
    digitalWrite(CYCLOTRON_LED_4_OUTPUT_PIN,LOW);

    digitalWrite(POWER_CELL_LED_1_OUTPUT_PIN,LOW);
    digitalWrite(POWER_CELL_LED_2_OUTPUT_PIN,LOW);
    digitalWrite(POWER_CELL_LED_3_OUTPUT_PIN,LOW);
    digitalWrite(POWER_CELL_LED_4_OUTPUT_PIN,LOW);
    digitalWrite(POWER_CELL_LED_5_OUTPUT_PIN,LOW);
    digitalWrite(POWER_CELL_LED_6_OUTPUT_PIN,LOW);
    digitalWrite(POWER_CELL_LED_7_OUTPUT_PIN,LOW);
    digitalWrite(POWER_CELL_LED_8_OUTPUT_PIN,LOW);
    digitalWrite(POWER_CELL_LED_9_OUTPUT_PIN,LOW);
    digitalWrite(POWER_CELL_LED_10_OUTPUT_PIN,LOW);

    digitalWrite(WAND_ORANGE_LED_OUTPUT_PIN,LOW);
    digitalWrite(WAND_RED_LED_OUTPUT_PIN,LOW);
    digitalWrite(WAND_WHITE_LED_OUTPUT_PIN,LOW);
  }
}

