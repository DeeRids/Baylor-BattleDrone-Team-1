
#define RED 12  // D4                                                                                                      
#define GRN 11  // D12
#define BLU 10  // D8
#define INTRPT 2

////INTERRUPT SERVICE ROUTINE
///////////////////////////////////////////////////////////////////////////////////////////
volatile int n = 1;
volatile int i = 0;
//void interrupt1(){
//  if((i % 100) == 0){
//    Lights(n);    // Call Switch Case
//    n = (n + 1) % 5;        // Loops Through Each Case
//  }
//  i++;
//}

void setup()
{
  Serial.begin(9600);
  pinMode(12,OUTPUT);                       // Set RED As Output
  pinMode(11,OUTPUT);                       // Set GRN As Output 
  pinMode(10,OUTPUT);                       // Set BLU As Output
  Lights(n);
  //digitalWrite(11,HIGH);
  //attachInterrupt(digitalPinToInterrupt(2),interrupt1,FALLING); // Set Pin 3 As Interrupt
 }

//HIT FUNCTION
/////////////////////////////////////////////////////////////////////////////////////////
void Lights(int n){
  Serial.println("Interrupt");
  switch (n) {
      case 1:                   // Case: Full Health
        digitalWrite(12,LOW);
        digitalWrite(11,HIGH);
        digitalWrite(10,LOW);
        break;
      case 2:                   // Case: One Hit
        digitalWrite(12,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,HIGH);
        break;
      case 3:                   // Case: Two Hits
        digitalWrite(12,HIGH);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
        break;
      default:                   // Case: Three Hits
        digitalWrite(12,LOW);
        digitalWrite(11,LOW);
        digitalWrite(10,LOW);
    }           
}

int BPin = 6;
bool buttonState = false;
bool Firing = false;
int irSensorValue;
  void loop() 
  {
    if (digitalRead(BPin) == HIGH) 
    {
      if(buttonState == false)
      {
        if(Firing == true) 
        {
          Serial.println("Tone");
          tone(9, 38000, 1);
          Firing = false; 
        }
        else 
        {
          noTone(9);
          Firing = true;
        }
      }
      buttonState = false;
    }
    else
    {
      buttonState = true;
    }
     
       irSensorValue = digitalRead(2);                     //Read Sensor Value
      //Serial.print(irSensorValue);                        //Print Out Sensor Value
      //Serial.print("\n");                        //Print Out Sensor Value
      if(irSensorValue == 0){
      if(i%300 == 0){
        Serial.print("HIT");                        //Print Out Sensor Value
        Serial.print(n);      
        Serial.print("\n");      
        Lights(n);
        //digitalWrite(26,LED_STATE);
        n++;
      }
      i++;
      if (n == 5)
      {
        n=0;
      }
  }
  }
