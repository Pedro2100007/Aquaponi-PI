
//Liga/desliga led c/ 2 botões

#define L3 2  // Led no pino D4, GPIO-0
#define B6 12  // Btn6 no pino D6, GPIO-12
#define B7 15  // Btn7 no pino D8, GPIO-15


void setup() {
  pinMode(L3,OUTPUT);
  pinMode(B6,INPUT);
  pinMode(B7,INPUT);
}

void loop() {
//  if (digitalRead(B6)){
      //delay(1000);
      digitalWrite(L3,HIGH);
//   }
//  if (digitalRead(B7)){
      //delay1000);
      digitalWrite(L3,LOW);
//  }

}
