
#define RED 28  // D4                                                                                                      
#define GRN 26  // D12
#define YLQ 25  // D8
#define INTRPT 1

//INTERRUPT SERVICE ROUTINE
/////////////////////////////////////////////////////////////////////////////////////////
volatile int n = 0;
volatile int i = 0;
void interrupt1(){
//  if((i % 110) == 0){
//    Lights(n);    // Call Switch Case
//    n = (n + 1) % 5;        // Loops Through Each Case
//  }
//  i++;
  Lights(n);
}

void setup()
{
  Serial.begin(9600);
  pinMode(28,OUTPUT);                       // Set RED As Output
  pinMode(26,OUTPUT);                       // Set GRN As Output 
  pinMode(25,OUTPUT);                       // Set BLU As Output
  pinMode(1,INPUT);
  //digitalWrite(PORTB |= 1<<4,HIGH);
  digitalWrite(PORTD |= 1<<6,HIGH);
  //digitalWrite(PORTD |= 1<<4,HIGH);
  attachInterrupt(digitalPinToInterrupt(PORTE |= 1<<1),interrupt1,FALLING); // Set Pin 3 As Interrupt
 }

//HIT FUNCTION
/////////////////////////////////////////////////////////////////////////////////////////
void Lights(int n){
  Serial.println("Interrupt");
  switch (n) {
      case 1:                   // Case: Full Health
        digitalWrite(PORTB |= 1<<4,LOW);
        digitalWrite(PORTD |= 1<<6,LOW);
        digitalWrite(PORTD |= 1<<4,HIGH);
        break;
      case 2:                   // Case: One Hit
        digitalWrite(PORTB |= 1<<4,HIGH);
        digitalWrite(PORTD |= 1<<6,LOW);
        digitalWrite(PORTD |= 1<<4,LOW);
        break;
      case 3:                   // Case: Two Hits
        digitalWrite(PORTB |= 1<<4,LOW);
        digitalWrite(PORTD |= 1<<6,HIGH);
        digitalWrite(PORTD |= 1<<4,LOW);
        break;
      case 4:                   // Case: Three Hits
        digitalWrite(PORTB |= 1<<4,LOW);
        digitalWrite(PORTD |= 1<<6,LOW);
        digitalWrite(PORTD |= 1<<4,LOW);
        
    }           
}

int BPin = 6;
int buttonState = 0;

  void loop() 
  {
    if(digitalRead(PORTE |= 1<<1))
    {
      n = (n + 1) % 5;
      Lights();
    }
    buttonState = digitalRead(BPin);
    if (buttonState == HIGH) 
    {
      Serial.println("Tone");
      tone(9, 38000);
     
    }
    else
    {
      //Serial.println("noTone");
      noTone(9);
    }
  }
