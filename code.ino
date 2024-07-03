// pin sensor ultrasonik
const int trigPin = 2;
const int echoPin = 3;

// pin sensor PIR
const int pirPin = 6;

// pin Relay
const int relayPin = 5;
const int relayPin2 = 4; // Additional relay pin

// Variable untuk mengukur jarak
long duration;
int distance;

// Variable untuk kondisi PIR
int pirState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(relayPin2, OUTPUT); // Additional relay pin as output
  digitalWrite(relayPin, LOW); // Make sure relay is off initially
  digitalWrite(relayPin2, LOW); // Make sure additional relay is off initially
}

void loop() {
  // Membaca jarak dari sensor ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Membaca kondisi sensor PIR
  pirState = digitalRead(pirPin);

  // Print hasil ke serial monitor
  Serial.print("Jarak : ");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.print(" | Kondisi PIR : ");
  Serial.println(pirState == HIGH ? "Terdapat gerakan" : "Tidak ada gerakan");

  // Kontrol relay menuju solenoid valve berdasar jarak
  if (distance < 5) {
    digitalWrite(relayPin, HIGH); // Turn relay on
  } else {
    digitalWrite(relayPin, LOW); // Turn relay off
  }

  // Kontrol relay menuju lampu berdasar kondisi PIR
  if (pirState == LOW) {
    digitalWrite(relayPin2, HIGH); // Turn additional relay on
  } else {
    digitalWrite(relayPin2, LOW); // Turn additional relay off
  }

  // Delay sebelum loop lagi
  delay(500);
}
