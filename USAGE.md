# Usage and wiring (Object Avoidance Robot)

This file summarizes the wiring/pin mapping and behavior implemented in `car.ino` so you can reproduce and tune the robot.

## Pin mapping (from `car.ino`)

- Ultrasonic sensor (HC-SR04):
  - TRIG -> D4 (`trigPin`)
  - ECHO -> D3 (`echoPin`)

- IR line sensors:
  - Left IR -> D11 (`leftIR`)
  - Right IR -> D12 (`rightIR`)

- LDR and headlight:
  - LDR -> A0 (`ldrPin`)
  - LED (headlight) -> D13 (`ledPin`)
  - Behavior: when analogRead(ldrPin) < 100 the LED is turned on; adjust threshold as required for your ambient light.

- Motor driver pins (example L298N style mapping):
  - Left motor IN1 -> D6 (`HighL`)
  - Left motor IN2 -> D7 (`LowL`)
  - Left motor EN (PWM) -> D5 (`enableL`)

  - Right motor IN1 -> D8 (`HighR`)
  - Right motor IN2 -> D9 (`LowR`)
  - Right motor EN (PWM) -> D10 (`enableR`)

Make sure motor driver power (12V or battery) shares a common ground with the Arduino.

## Behavior summary

- Line following (IR sensors):
  - The sketch reads the two IR sensors as digital inputs.
  - Logic in `loop()`:
    - left LOW & right HIGH -> turn Right()
    - left HIGH & right LOW -> turn Left()
    - left LOW & right LOW -> Forward()
    - otherwise -> stopCar()
  - If your IR sensors produce reversed polarity (HIGH/LOW swapped), invert the logic or swap sensor wiring.

- Obstacle avoidance (ultrasonic):
  - The sketch measures distance every ~200 ms (see `obstacleInterval`).
  - If a valid distance is returned and it's under 25 cm the car stops, waits, randomly turns left or right briefly, then resumes forward movement.
  - Adjust the avoidance distance by changing the comparison value (currently 25).

- Automatic headlight (LDR):
  - The sketch reads the LDR on A0; if the reading is below 100 the LED on D13 turns on.
  - Tune the `100` threshold depending on your LDR and ambient light.

## Tuning and debugging tips

- Open Serial Monitor (Serial.begin(9600) is enabled) and add `Serial.println()` statements in `loop()` to print sensor values if you need to tune thresholds.
- If motors don't move, check `enable` pins and supply voltage to motor driver. Some motor driver EN pins need PWM (analogWrite) rather than digital HIGH/LOW.
- If ultrasonic `pulseIn()` times out often, ensure wiring and sensor power are correct; try increasing the `pulseIn` timeout (currently 20000 us).

## Files (images)

- `Object_Avoidance_Robot.png` — project photo
- `circuit_diagram.jpg` — wiring diagram

