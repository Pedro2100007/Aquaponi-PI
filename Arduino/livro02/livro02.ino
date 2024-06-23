// Led no pino D3, GPIO-0
#define L3 0

void setup() {


  pinMode(L3,OUTPUT);

}

void loop() {
  digitalWrite(L3,HIGH);

  delay(500);
  digitalWrite(L3,LOW);

  delay(500);
 
}
