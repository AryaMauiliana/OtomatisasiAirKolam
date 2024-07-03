# Automasi Air Kolam dan Kontrol Lampu

Proyek ini menggunakan sensor ultrasonik untuk mengontrol level air dalam kolam dengan bantuan solenoid valve. Selain itu, sistem ini juga dapat mengontrol lampu menggunakan sensor PIR (Passive Infrared) untuk mendeteksi gerakan. 

## Fitur
- **Pengaturan level air kolam**: Menggunakan sensor ultrasonik untuk mendeteksi level air dan mengontrol solenoid valve untuk mengisi atau mengosongkan kolam secara otomatis.
- **Kontrol lampu**: Menggunakan sensor PIR untuk mendeteksi gerakan dan mengontrol lampu secara otomatis.

## Hardware yang Diperlukan
- Arduino Nano
- Sensor Ultrasonik HC-SR04
- Solenoid Valve
- Sensor PIR
- Relay Module
- PCB
- Lampu

## Wiring Diagram
### Sensor Ultrasonik dan Solenoid Valve
```
HC-SR04          Arduino
VCC              5V
GND              GND
Trig             Digital Pin 2
Echo             Digital Pin 3

Solenoid Valve   Arduino
+                12V Power Supply
-                Relay NO (Normally Open)
Relay COM        GND
Relay Signal     Digital Pin 5
```

### Sensor PIR dan Kontrol Lampu
```
PIR            Arduino
VCC            5V
GND            GND
OUT            Digital Pin 6

Lamp           Relay NO (Normally Open)
Relay COM      AC Live (L)
Relay Signal   Digital Pin 4
```

## Software
Code Arduino untuk mengontrol sensor ultrasonik dan PIR serta mengaktifkan solenoid valve dan relay untuk lampu:

```cpp
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
```

## Instalasi
1. Rangkai semua komponen sesuai diagram wiring di atas.
2. Unggah kode Arduino ke papan Arduino Nano.

---

Jika ada pertanyaan atau saran, silakan buka issue atau pull request di repository ini.
