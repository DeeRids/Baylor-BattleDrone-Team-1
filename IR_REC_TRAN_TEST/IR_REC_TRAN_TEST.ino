#define IR_TRANS 9
#define BUTTON 5
#define RED 6
#define GRN 7
#define BLU 8
#define IR_REC A2

#define RED_SET   pinMode(RED,OUTPUT)
#define RED_ON    digitalWrite(RED,HIGH)
#define RED_OFF   digitalWrite(RED,LOW)

#define GRN_SET   pinMode(GRN,OUTPUT)
#define GRN_ON    digitalWrite(GRN,HIGH)
#define GRN_OFF   digitalWrite(GRN,LOW)

#define BLU_SET   pinMode(BLU,OUTPUT)
#define BLU_ON    digitalWrite(BLU,HIGH)
#define BLU_OFF   digitalWrite(BLU,LOW)

bool BUTTON_STATE = false;
bool IR_STATE = false;
bool LED_STATE = false;
bool isFiring = false;
int i = 0;
int n = 1;
int Analog_Val;
unsigned long interval = 800;
unsigned long previousMillis = 0;
unsigned long currentMillis;

void Lights(int n){
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
        RED_OFF;;
        
    }           
}

void setup() {
  RED_SET;
  GRN_SET;
  BLU_SET;
  GRN_ON;
  //BLU_ON;
  //RED_ON;
  pinMode(IR_REC,INPUT);
  pinMode(IR_TRANS,OUTPUT);  
  pinMode(BUTTON,INPUT);
  Serial.begin(9600);
}

void loop() {
   
////SEND CODE
  if(digitalRead(BUTTON) == HIGH){
    if(BUTTON_STATE == false){
      isFiring = true;
      tone(IR_TRANS,37000,400);
      Serial.print("Tone\n");
      BUTTON_STATE = true;
    }
  }
  else{
    BUTTON_STATE = false;
  }

   currentMillis =  millis();

   if((currentMillis - previousMillis) >= interval){
    previousMillis = currentMillis; 
    isFiring = false;
   }
  
  ////RECEIVE CODE
  Analog_Val = analogRead(IR_REC);
  Serial.println(Analog_Val);
  if(isFiring == false){
    if(Analog_Val == 0){
      if(IR_STATE == false){
        i = i + 1;
        if((i%30) == 0){
          //Serial.println(i);
          Lights(n);
          n = n + 1;
          Serial.println("Hit");
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
