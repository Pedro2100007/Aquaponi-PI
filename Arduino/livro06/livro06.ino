// Placa NodeMCU 1.0 (ESP12E-Module)
#define L3 0 //Pino D3 - GPIO-0
#define B0 16 //Pino D0 - GPIO-16
char rxChar=0; //caracter entrada
void setup(){
Serial.begin(9600);
pinMode(L3, OUTPUT);
pinMode(B0, INPUT);
Serial.flush(); // zera o buffer de entrada.
Serial.println(" - COMANDOS SERIAIS - ");
Serial.println("L= liga LED - D= desliga LED - B= monitora Botao");
}
void loop(){
if (Serial.available() >0){ // testa se chegou caracter.
  rxChar = Serial.read(); // lê caracter que chegou.
  Serial.flush(); // zera o buffer de entrada.
switch (rxChar){
  case 'L': // recebeu 'L':
    digitalWrite(L3,HIGH); // Liga o LED
    Serial.println("LED LIGADO");
  break;
  case 'D': // recebeu 'D':
    digitalWrite(L3,LOW); // Desliga o LED
    Serial.println("LED DESLIGADO");
  break;
  case 'B': // recebeu 'B':
    if(digitalRead(B0) == HIGH){
     Serial.println("Botao B0 pressionado");
     digitalWrite(L3,HIGH); // Liga o LED
    }
    else{
     Serial.println("Botao B0 nao pressionado");
     digitalWrite(L3,LOW); // desLiga o LED
    }
  break;
default:
Serial.print((char)rxChar);
Serial.println(" comando invalido!");
}
}
}
