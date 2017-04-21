#define RED 6
#define GRN 7
#define BLU 8
#define IR_REC A2

#define RED_SET pinMode(RED,OUTPUT)
#define RED_ON digitalWrite(RED,HIGH)
#define RED_OFF digitalWrite(RED,LOW)

#define GRN_SET pinMode(GRN,OUTPUT)
#define GRN_ON digitalWrite(GRN,HIGH)
#define GRN_OFF digitalWrite(GRN,LOW)

#define BLU_SET pinMode(BLU,OUTPUT)
#define BLU_ON digitalWrite(BLU,HIGH)
#define BLU_OFF digitalWrite(BLU,LOW)

bool IR_STATE = false;
bool LED_STATE = false;
int i = 0;
int n = 1;
int Analog_Val;

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
  Serial.begin(9600);
}

void loop() {
  Analog_Val = analogRead(IR_REC);
  Serial.println(Analog_Val);
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
