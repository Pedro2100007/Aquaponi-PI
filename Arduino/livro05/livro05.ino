
//Placa: "NodeMCU1.0(ESP-12EModule)"
#define L8 15 //led ligando no pino GPIO15
void setup() {
pinMode(L8,OUTPUT);
}
void loop(){
for(int a=0;a<1023;a++){
analogWrite(L8,a);
delay(10);
}
for(int a=1023;a>0;a--){
analogWrite(L8,a);
delay(10);
}
}
