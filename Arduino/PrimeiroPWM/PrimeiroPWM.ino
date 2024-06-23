
// Pela numeração do GPIO:
#define LED_1   5
#define LED_2   4

void setup()
{
  // Configura pinos como saída
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
}


void loop()
{
  // Aumenta o brilho gradualmente primeiro led
  digitalWrite(LED_2, LOW);
  for(uint16_t i = 0; i < 1023; i++)
  {
    analogWrite(LED_1, i);
    delay(10);
  }
  delay(200);
// Aumenta o brilho gradualmente segundo led
  digitalWrite(LED_1, LOW);
  for(uint16_t i = 0; i < 1023; i++)
  {
    analogWrite(LED_2, i);
    delay(10);
  }
  delay(200);
}
