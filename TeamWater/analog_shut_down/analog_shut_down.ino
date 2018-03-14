void setup()
{
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0)
    if (Serial.read() == 'A')
      count(0);
}

void count(int i)
{
  while (i < 5) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(700);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
    i++;
  }
  Serial.print('1');
}

