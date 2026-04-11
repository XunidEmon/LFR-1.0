# 🛠️ Line Follower Robot using Arduino (5-Sensor | L293D)

This project is a **simple 5-sensor Line Follower Robot** built with Arduino UNO, 5-channel IR sensor array, and L293D motor driver.  
**No PID** — just clean if-else logic for beginners.

---

## 🚗 Hardware Components

- Arduino UNO / Nano / Mega
- L293D Motor Driver
- 2 × 12V DC Gear Motors (100–200 RPM recommended)
- 5-Channel IR Sensor Array
- 12V Battery (for motors)
- 5V Regulator (for sensors/Arduino)
- Chassis, Wheels, Jumper Wires

---

## ⚙️ Motor Pin Configuration (L293D)

| Motor Driver Pin | Arduino Pin | Description        |
|------------------|-------------|--------------------|
| Left Motor IN1   | 7           | Left motor direction 1 |
| Left Motor IN2   | 8           | Left motor direction 2 |
| Left Motor ENA   | 5 (PWM)     | Left motor speed      |
| Right Motor IN3  | 9           | Right motor direction 1 |
| Right Motor IN4  | 10          | Right motor direction 2 |
| Right Motor ENB  | 6 (PWM)     | Right motor speed     |

---

## 🔧 Sensor Pin Configuration

| IR Sensor         | Arduino Pin |
|-------------------|-------------|
| Sensor 1 (Leftmost) | A0          |
| Sensor 2 (Left)     | A1          |
| Sensor 3 (Center)   | A2          |
| Sensor 4 (Right)    | A3          |
| Sensor 5 (Rightmost)| A4          |

---

## 📌 Calibration Code (Find Threshold)

Use this code to find the correct threshold value for your sensors.

```cpp
int s1 = A0, s2 = A1, s3 = A2, s4 = A3, s5 = A4;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int v1 = analogRead(s1);
  int v2 = analogRead(s2);
  int v3 = analogRead(s3);
  int v4 = analogRead(s4);
  int v5 = analogRead(s5);

  int avg = (v1 + v2 + v3 + v4 + v5) / 5;

  Serial.print(v1); Serial.print(" ");
  Serial.print(v2); Serial.print(" ");
  Serial.print(v3); Serial.print(" ");
  Serial.print(v4); Serial.print(" ");
  Serial.print(v5); Serial.print(" | Avg: ");
  Serial.println(avg);

  delay(500);
}





🤖 Main LFR Code (Simple If-Else Logic)

// 5-Sensor Line Follower Robot (Simple)
// Sensor pins
int s1 = A0;  // Leftmost
int s2 = A1;  // Left
int s3 = A2;  // Center
int s4 = A3;  // Right
int s5 = A4;  // Rightmost

// Motor pins
int lm1 = 7;   // Left motor pin 1
int lm2 = 8;   // Left motor pin 2
int lpwm = 5;  // Left speed (PWM)
int rm1 = 9;   // Right motor pin 1
int rm2 = 10;  // Right motor pin 2
int rpwm = 6;  // Right speed (PWM)

int th = 500;  // Threshold (below = black line)

void setup() {
  pinMode(s1, INPUT); pinMode(s2, INPUT); pinMode(s3, INPUT);
  pinMode(s4, INPUT); pinMode(s5, INPUT);

  pinMode(lm1, OUTPUT); pinMode(lm2, OUTPUT); pinMode(lpwm, OUTPUT);
  pinMode(rm1, OUTPUT); pinMode(rm2, OUTPUT); pinMode(rpwm, OUTPUT);
}

void loop() {
  int v1 = analogRead(s1);
  int v2 = analogRead(s2);
  int v3 = analogRead(s3);
  int v4 = analogRead(s4);
  int v5 = analogRead(s5);

  int L1 = (v1 < th) ? 1 : 0;
  int L2 = (v2 < th) ? 1 : 0;
  int L3 = (v3 < th) ? 1 : 0;
  int L4 = (v4 < th) ? 1 : 0;
  int L5 = (v5 < th) ? 1 : 0;

  if (L3 == 1) forward();
  else if (L2 == 1) left();
  else if (L4 == 1) right();
  else if (L1 == 1) hardLeft();
  else if (L5 == 1) hardRight();
  else stop();
}

void forward() {
  digitalWrite(lm1, HIGH); digitalWrite(lm2, LOW);
  digitalWrite(rm1, HIGH); digitalWrite(rm2, LOW);
  analogWrite(lpwm, 150); analogWrite(rpwm, 150);
}

void left() {
  digitalWrite(lm1, LOW); digitalWrite(lm2, HIGH);
  digitalWrite(rm1, HIGH); digitalWrite(rm2, LOW);
  analogWrite(lpwm, 100); analogWrite(rpwm, 100);
}

void right() {
  digitalWrite(lm1, HIGH); digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW); digitalWrite(rm2, HIGH);
  analogWrite(lpwm, 100); analogWrite(rpwm, 100);
}

void hardLeft() {
  digitalWrite(lm1, LOW); digitalWrite(lm2, HIGH);
  digitalWrite(rm1, HIGH); digitalWrite(rm2, LOW);
  analogWrite(lpwm, 120); analogWrite(rpwm, 120);
}

void hardRight() {
  digitalWrite(lm1, HIGH); digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW); digitalWrite(rm2, HIGH);
  analogWrite(lpwm, 120); analogWrite(rpwm, 120);
}

void stop() {
  digitalWrite(lm1, LOW); digitalWrite(lm2, LOW);
  digitalWrite(rm1, LOW); digitalWrite(rm2, LOW);
  analogWrite(lpwm, 0); analogWrite(rpwm, 0);
}
