const int trigPin = 4;
const int echoPin = 3;

const int leftIR = 11;
const int rightIR = 12;

const int HighL = 6;
const int LowL = 7;

const int enableR = 10;
const int enableL = 5;

const int HighR = 8;
const int LowR = 9;

const int ldrPin = A0;
const int ledPin = 13;

long obstacleCheckTime = 0;
long obstacleInterval = 200;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(HighL, OUTPUT);
  pinMode(LowL, OUTPUT);
  pinMode(HighR, OUTPUT);
  pinMode(LowR, OUTPUT);

  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);

  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);

  pinMode(enableL, OUTPUT);
  pinMode(enableR, OUTPUT);

  Serial.begin(9600);
}

void Forward() {
  digitalWrite(HighL, LOW);
  digitalWrite(LowL, HIGH);
  digitalWrite(enableL, HIGH);

  digitalWrite(HighR, LOW);
  digitalWrite(LowR, HIGH);
  digitalWrite(enableR, HIGH);
}

void Left() {
  digitalWrite(HighL, LOW);
  digitalWrite(LowL, LOW);
  digitalWrite(enableL, HIGH);

  digitalWrite(HighR, LOW);
  digitalWrite(LowR, HIGH);
  digitalWrite(enableR, HIGH);
}

void Right() {
  digitalWrite(HighL, LOW);
  digitalWrite(LowL, HIGH);
  digitalWrite(enableL, HIGH);

  digitalWrite(HighR, LOW);
  digitalWrite(LowR, LOW);
  digitalWrite(enableR, HIGH);
}

void Backward() {
  digitalWrite(HighL, HIGH);
  digitalWrite(LowL, LOW);
  digitalWrite(enableL, HIGH);

  digitalWrite(HighR, HIGH);
  digitalWrite(LowR, LOW);
  digitalWrite(enableR, HIGH);
}

void stopCar() {
  digitalWrite(HighL, LOW);
  digitalWrite(LowL, LOW);
  digitalWrite(enableL, LOW);

  digitalWrite(HighR, LOW);
  digitalWrite(LowR, LOW);
  digitalWrite(enableR, LOW);
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 20000);
  if (duration == 0) {
    return -1; 
  }
  return (duration / 2) * 0.0343;  
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  int leftStatus = digitalRead(leftIR);
  int rightStatus = digitalRead(rightIR);

  if (ldrValue < 100) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  if (leftStatus == LOW && rightStatus == HIGH) {
    Right();
  } else if (leftStatus == HIGH && rightStatus == LOW) {
    Left();
  } else if (leftStatus == LOW && rightStatus == LOW) {
    Forward();
  } else {
    stopCar();
  }

  if (millis() - obstacleCheckTime >= obstacleInterval) {
    obstacleCheckTime = millis();
    long distance = getDistance();

    if (distance != -1 && distance < 25) {
      stopCar();
      delay(500);
      if (random(2) == 0) {
        Left();
      } else {
        Right();
      }
      delay(1000);
      Forward();
    }
  }
  delay(50); 
}
