#define IR_TRANS 9
#define BUTTON 6
bool BUTTON_STATE = false; 

void setup() {
  pinMode(IR_TRANS,OUTPUT);  
  pinMode(BUTTON,INPUT);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(BUTTON) == HIGH){
    if(BUTTON_STATE == false){
      tone(IR_TRANS,37000,1000);
      Serial.print("Tone\n");
      BUTTON_STATE = true;
    }
  }
  else{
    BUTTON_STATE = false;
  }
}
