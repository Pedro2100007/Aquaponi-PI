#include <EEPROM.h>

#define ultimaPorta 16  //Geral
//#define ultimaPorta 3   //ESP-01

byte porta;

/*       PLACA D1      PLACA NODEMCU     PLACA ESP-01
*  0  -> D8         -> D3             -> GP0
*  1  -> D1 (TX)    -> TX             -> TX0
*  2  -> D9         -> D4             -> GP2
*  3  -> D0 (RX)    -> RX             -> RX0
*  4  -> D4 e D14   -> D2
*  5  -> D3 e D15   -> D1
*  12 -> D6 e D12   -> D6
*  13 -> D7 e D11   -> D7
*  14 -> D5 e D13   -> D5
*  15 -> D10        -> D8
*  16 -> D2         -> D0
*/

//PLACA D1
/*
#define D0 3
#define D1 1
#define D2 16
#define D3 5
#define D4 4
#define D5 14
#define D6 12
#define D7 13
#define D8 0
#define D9 2
#define D10 15
#define D11 13
#define D12 12
#define D13 14
#define D14 4
#define D15 5
*/

//PLACA nodeMCU

#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15


//PLACA ESP-01
/*
#define GP0 0
#define TX0 1
#define GP2 2
#define RX0 3
*/

void setup() {

  Serial.begin(9600);
  while (!Serial) {
  }

  EEPROM.begin(512);

  porta = EEPROM.read(0);
  porta++;
  if (porta > ultimaPorta) {
     porta = 0; 
  }

  EEPROM.write(0, porta);
  EEPROM.commit();


  Serial.print("Testando Porta ");
  Serial.println(porta);
  
  pinMode(porta, OUTPUT);
}

void loop() {

  digitalWrite(porta, LOW);
  delay(200);
  digitalWrite(porta, HIGH);
  delay(200);

}
