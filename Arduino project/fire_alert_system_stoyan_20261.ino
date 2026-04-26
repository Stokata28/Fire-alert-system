char degree = 176;

void setup() {
  pinMode(5,  OUTPUT);  // Red LED 1
  pinMode(4,  OUTPUT);  // Red LED 2
  pinMode(2,  OUTPUT);  // Red LED 3
  pinMode(6,  OUTPUT);  // Green LED
  pinMode(11, OUTPUT);  // Piezo buzzer
  pinMode(10, OUTPUT);  // Motor / fan
  pinMode(A1, INPUT);   // TMP temperature sensor
  pinMode(A0, INPUT);   // MQ gas sensor
  Serial.begin(9600);
}

void loop() {
  // --- Read temperature ---
  int tmp = analogRead(A1);
 
  float milliVolt =((tmp * 5.0) / 1024) * 1000;
  float tmpCel    = (milliVolt - 500) / 10;

  // --- Read gas sensor ---
  float gsense = analogRead(A0);

  // --- Gas raises the temperature reading ---

  Serial.print("\nCelsius: ");
  Serial.print(tmpCel);
  Serial.println(degree);
  Serial.print("Smoke value: ");
  Serial.println(gsense);

  // --- Evaluate alert condition ---
  if (gsense >= 250|| tmp >=60) {
    digitalWrite(6, LOW);
    digitalWrite(10, HIGH);
    tone(11, 1000, 1000);
    for (int i = 0; i < 3; i++) {
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(2, LOW);
      delay(100);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(2, LOW);
      delay(100);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      digitalWrite(2, HIGH);
      delay(100);
    }
  } else {
    digitalWrite(5,  LOW);
    digitalWrite(4,  LOW);
    digitalWrite(2,  LOW);
    digitalWrite(10, LOW);
    noTone(11);
    digitalWrite(6, HIGH);
  }
  delay(100);
}