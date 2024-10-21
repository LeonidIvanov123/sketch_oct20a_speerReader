/*
  We read half the signal period from the speed sensor (bypassing the dashboard)
  and then convert the signal to digital for ECU.
*/

const int analogPin = A0;
const int digitalPin = 9;

void setup() {
  pinMode(digitalPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  static bool state = LOW;
  static int lastAnalogValue = 0;
  const int threshold = 5; // Минимальный уровень сигнала для учета прохода через ноль

  int analogValue = analogRead(analogPin);

  Serial.println(analogValue);

  // Проверка на переход через ноль с гистерезисом
  if ((lastAnalogValue < threshold && analogValue >= threshold) || 
      (lastAnalogValue > threshold && analogValue <= threshold)) {
    state = !state;
    digitalWrite(digitalPin, state); // Переключаем состояние
   // delay(20); // Задержка для уменьшения частоты импульсов
  }
  lastAnalogValue = analogValue;
}
