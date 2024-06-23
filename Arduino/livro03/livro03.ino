#define L3 0  // Led no pino D3, GPIO-0
#define L8 15  // Led no pino D8, GPIO-15
long Tempo1, Tempo2;
int referenciaTempo1=1000; //1000ms
int referenciaTempo2=500; //500ms

void setup() {
  pinMode(L3,OUTPUT);
  pinMode(L8,OUTPUT);
  Tempo1=millis();
  Tempo2=millis();
}

void loop() {
  if (millis()>Tempo1+referenciaTempo1){
      Tempo1=millis();
      digitalWrite(L3,HIGH);
      delay(50);
      digitalWrite(L3,LOW);
  }
  if (millis()>Tempo2+referenciaTempo2){
      Tempo2=millis();
      digitalWrite(L8,HIGH);
      delay(50);
      digitalWrite(L8,LOW);
  }

}
