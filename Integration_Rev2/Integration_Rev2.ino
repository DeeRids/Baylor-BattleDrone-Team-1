//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*****************************************BEGIN BAYLOR UNIVERSITY DRONE CODE***********************************************//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define IR_TRANS              A4                 
#define FIRE_PIN_ON               //PORTF |= (1<<0);    //Set Fire Pin On
#define FIRE_PIN_OFF              //PORTF |= ~(1<<0);   //Set Fire Pin Off

#define IR_REC                A5   //Set Sensor As Input

#define RED_PINMODE           DDRB |= (1<<4);
#define RED_OFF               PORTB &= ~(1<<4);
#define RED_ON                PORTB |= (1<<4);   
#define RED_TOGGLE            PINB |= 1<<4;     //switch LEDPIN state (Port D6)  
 
#define BLU_PINMODE           DDRD |= (1<<4);
#define BLU_OFF               PORTD &= ~(1<<4);
#define BLU_ON                PORTD |= (1<<4);   
#define BLU_TOGGLE            PIND |= 1<<4;     //switch LEDPIN state (Port D6)  

#define GRN_PINMODE           DDRD |= (1<<6);
#define GRN_OFF               PORTD &= ~(1<<6);
#define GRN_ON                PORTD |= (1<<6);   
#define GRN_TOGGLE            PIND |= 1<<6;     //switch LEDPIN state (Port D6)

bool BUTTON_STATE = false;
bool IR_STATE = false;
bool LED_STATE = false;
bool FIRE_STATE = false;
bool isFiring = false;
int i = 0;
int n = 1;
int Analog_Val;
unsigned long interval = 1200;
unsigned long fire_interval = 5000;
unsigned long fire_previousMillis = 0;
unsigned long fire_currentMillis;
unsigned long previousMillis = 0;
unsigned long currentMillis;


//                                                                                                                       Setup
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {                                        //Setup Function
  IR_REC;                                          //Initialize Sensor
  RED_PINMODE;
  BLU_PINMODE;
  GRN_PINMODE;
  Serial.begin(9600);                                 //Set Up Serial Read
  GRN_ON; //GREEN  
}


//                                                                                                                 Fire Cannon
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fire_cannon() {                                  //Fire Cannon Function 
   tone(A5,37000,1000);                               //38kHz Pulse For ----- Seconds
}

  
//                                                                                                                      Lights
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Lights(int n){
  //Serial.println("Interrupt");
  switch (n) {
      case 1:                   // Case: Full Health
        GRN_OFF;
        BLU_ON;
        RED_OFF;
        break;
      case 2:                   // Case: One Hit
        GRN_OFF;
        BLU_OFF; 
        RED_ON;
        break;
      case 3:                   // Case: Two Hits
        GRN_OFF;
        BLU_OFF;
        RED_OFF;
        break;
      default:                   // Case: Three Hits
        GRN_OFF;
        BLU_OFF;
        RED_OFF;
        
    }           
}


//                                                                                                                        Loop
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {                                         //Loop Function
//  if(digitalRead(BUTTON) == HIGH){
//    if(BUTTON_STATE == false){
//      if(FIRE_STATE == false){
//        isFiring = true;
//        tone(IR_TRANS,37000,400);
//        //Serial.print("Tone\n");
//        BUTTON_STATE = true;
//        FIRE_STATE = true;
//      }
//    }
//  }
//  else{
//    BUTTON_STATE = false;
//  }

   currentMillis = millis();
   fire_currentMillis = millis();

   if((fire_currentMillis - fire_previousMillis) >= fire_interval){
    fire_previousMillis = fire_currentMillis; 
    FIRE_STATE = false;
   }

   if((currentMillis - previousMillis) >= interval){
    previousMillis = currentMillis; 
    isFiring = false;
   }
  
  ////RECEIVE CODE
  Analog_Val = analogRead(IR_REC);
  //Serial.println(Analog_Val);
  if(isFiring == false){
    if(Analog_Val == 0){
      if(IR_STATE == false){
        i = i + 1;
        if((i%180) == 0){
          //Serial.println(i);
          Lights(n);
          n = n + 1;
          //Serial.println("Hit");
          //LED_STATE = !LED_STATE;
          //digitalWrite(RED,LED_STATE);
          IR_STATE = true;
        }
      }
    }
    else{
      IR_STATE = false;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************END BAYLOR UNIVERSITY DRONE CODE***********************************************//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
