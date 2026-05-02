// ===== 5 Sensor Line Follower Robot (Optimized) =====

// -------- Sensor Pins --------
#define S1 A0   // Leftmost
#define S2 A1
#define S3 A2   // Center
#define S4 A3
#define S5 A4   // Rightmost

// -------- Motor Pins --------
#define LM1 7
#define LM2 8
#define LPWM 5

#define RM1 9
#define RM2 10
#define RPWM 6

// -------- Parameters --------
int threshold = 500;
int baseSpeed = 120;
int turnSpeed = 90;

// -------- Setup --------
void setup() {
  pinMode(S1, INPUT); pinMode(S2, INPUT); pinMode(S3, INPUT);
  pinMode(S4, INPUT); pinMode(S5, INPUT);

  pinMode(LM1, OUTPUT); pinMode(LM2, OUTPUT); pinMode(LPWM, OUTPUT);
  pinMode(RM1, OUTPUT); pinMode(RM2, OUTPUT); pinMode(RPWM, OUTPUT);

  Serial.begin(9600);
}

// -------- Loop --------
void loop() {

  // Read sensors
  int v1 = analogRead(S1);
  int v2 = analogRead(S2);
  int v3 = analogRead(S3);
  int v4 = analogRead(S4);
  int v5 = analogRead(S5);

  // Convert to digital (black = 1)
  int L1 = (v1 < threshold);
  int L2 = (v2 < threshold);
  int L3 = (v3 < threshold);
  int L4 = (v4 < threshold);
  int L5 = (v5 < threshold);

  // Debug (optional)
  Serial.print(L1); Serial.print(" ");
  Serial.print(L2); Serial.print(" ");
  Serial.print(L3); Serial.print(" ");
  Serial.print(L4); Serial.print(" ");
  Serial.println(L5);

  // -------- Control Logic --------
  if (L3) {
    moveForward();
  }
  else if (L2) {
    softLeft();
  }
  else if (L4) {
    softRight();
  }
  else if (L1) {
    hardLeft();
  }
  else if (L5) {
    hardRight();
  }
  else {
    stopRobot();
  }
}

// -------- Movement Functions --------
void moveForward() {
  setMotor(baseSpeed, baseSpeed);
}

void softLeft() {
  setMotor(turnSpeed, baseSpeed);
}

void softRight() {
  setMotor(baseSpeed, turnSpeed);
}

void hardLeft() {
  setMotor(-turnSpeed, turnSpeed);
}

void hardRight() {
  setMotor(turnSpeed, -turnSpeed);
}

void stopRobot() {
  setMotor(0, 0);
}

// -------- Motor Control Function --------
void setMotor(int leftSpeed, int rightSpeed) {

  // Left Motor
  if (leftSpeed >= 0) {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
  } else {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    leftSpeed = -leftSpeed;
  }

  // Right Motor
  if (rightSpeed >= 0) {
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
  } else {
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    rightSpeed = -rightSpeed;
  }

  analogWrite(LPWM, constrain(leftSpeed, 0, 255));
  analogWrite(RPWM, constrain(rightSpeed, 0, 255));
}
