//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*****************************************BEGIN BAYLOR UNIVERSITY DRONE CODE***********************************************//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FIRE_PIN_ON               PORTF |= (1<<0);    //Set Fire Pin On
#define FIRE_PIN_OFF              PORTF |= ~(1<<0);   //Set Fire Pin Off

#define IR_SENSOR                 pinMode(1,INPUT);   //Set Sensor As Input

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

volatile int n = 1;                                   //Hit Counter
volatile int i = 0;    

int irSensorValue;                                    //Sensor As Int
int BPin = 6;
bool irSensorState = false;
bool Firing = false;


//                                                                                                                       Setup
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {                                        //Setup Function
  IR_SENSOR;                                          //Initialize Sensor
  RED_PINMODE;
  BLU_PINMODE;
  GRN_PINMODE;
  Serial.begin(9600);                                 //Set Up Serial Read
  GRN_ON; //GREEN
}


//                                                                                                                 Fire Cannon
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void fire_cannon() {                                  //Fire Cannon Function 
  //tone();                                           //38kHz Pulse For ----- Seconds
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
        BLU_ON;
        RED_OFF;
        break;
      default:                   // Case: Three Hits
        GRN_OFF;
        BLU_OFF;
        RED_OFF;;
        
    }           
}


//                                                                                                                        Loop
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {                                         //Loop Function
      //Serial.print("Time: ");
      //time = millis();
      //Serial.println(time);
      
      irSensorValue = digitalRead(A2);                     //Read Sensor Value
      //Serial.print(irSensorValue);                        //Print Out Sensor Value
      //Serial.print("\n");                        //Print Out Sensor Value
      if(irSensorValue == 0){
        if(irSensorState == false){
          i = i + 1;
          Serial.print(i);      
          Serial.print("\n");
          if(i%20 == 0){
            n = n + 1;
            Lights(n);
            Serial.print("HIT");                              //Print Out Sensor Value
            Serial.print("\n"); 
            irSensorState = true;     
        }
       }
       else{
        irSensorState = false;
       }
       
      }

//********************** TEST CODE ******************************
//    if (digitalRead(BPin) == HIGH) 
//    {
//      if(buttonState == false)
//      {
//        if(Firing == true) 
//        {
//          Serial.println("Tone");
//          tone(9, 38000, 1);
//          Firing = false; 
//        }
//        else 
//        {
//          noTone(9);
//          Firing = true;
//        }
//      }
//      buttonState = false;
//    }
//    else
//    {
//      buttonState = true;
//    }
//***************************************************************
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//*******************************************END BAYLOR UNIVERSITY DRONE CODE***********************************************//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
