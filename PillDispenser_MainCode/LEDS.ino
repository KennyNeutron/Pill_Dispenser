#define LED1 14
#define LED2 27
#define LED3 26
#define LED4 25
#define LED5 23


void LEDS_setup(){
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
}




void LEDS_test(){
  digitalWrite(LED1, LOW);
  delay(300);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(300);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  delay(300);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, LOW);
  delay(300);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, LOW);
  delay(300);
  digitalWrite(LED5, HIGH);
}