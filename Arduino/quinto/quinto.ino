// Duas formas de definir os pinos:
// Pela numeração do NodeMCU:
//#define LED_1   D0
//#define LED_2   D1
//#define BOTAO_1 D2
//#define BOTAO_2 D3

// Pela numeração do GPIO:
#define LED_1   16
#define LED_2   5
#define BOTAO_1 4
#define BOTAO_2 0

void setup()
{
  // Configura LEDs como saída
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);

  // Configura botões como entrada
  pinMode(BOTAO_1, INPUT_PULLUP);
  pinMode(BOTAO_2, INPUT_PULLUP);
}

void loop()
{
  // Leitura do botão 1
  if(digitalRead(BOTAO_1) == 0)
  {
    digitalWrite(LED_1, HIGH);
    delay(200); // debounce do botão
  }
  else // Se não está pressionado
  {
    digitalWrite(LED_1, LOW);
  }

  // Leitura do botão 2
  if(digitalRead(BOTAO_2) == 0)
  {
    digitalWrite(LED_2, HIGH);
    delay(200); // debounce do botão
  }
  else // Se não está pressionado
  {
    digitalWrite(LED_2, LOW);
  }
}