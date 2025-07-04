// Motor functions for left and right motors
void botleft() {
  motor1.drive(-1 * turnspeed);
  motor2.drive(turnspeed);
  delay(150);
  while (analogRead(3) < threshold) { // Check if sensor detects black line
    motor1.drive(-1 * turnspeed);
    motor2.drive(turnspeed);
  }
  motor1.drive(0);
  motor2.drive(0);
  delay(50);
}

void botright() {
  motor1.drive(turnspeed);
  motor2.drive(-1 * turnspeed);
  delay(150);
  while (analogRead(3) < threshold) { // Check if sensor detects black line
    motor1.drive(turnspeed);
    motor2.drive(-1 * turnspeed);
  }
  motor1.drive(0);
  motor2.drive(0);
  delay(50);
}

void botstraight() {
  if (analogRead(2) < threshold && analogRead(3) < threshold) { // Center sensors on black line
    motor1.drive(lfspeed);
    motor2.drive(lfspeed);
  } else if (analogRead(1) < threshold) { // Left sensor detects black, slight left
    botleft();
  } else if (analogRead(4) < threshold) { // Right sensor detects black, slight right
    botright();
  } else {
    botstop(); // Stop if no black line is detected
  }
}

void botinchforward() {
  motor1.drive(turnspeed);
  motor2.drive(turnspeed);
  delay(10);
}

void botstop() {
  motor1.drive(0);
  motor2.drive(0);
}

void botuturn() {
  motor1.drive(-1 * turnspeed);
  motor2.drive(turnspeed);
  delay(300);
  while (analogRead(3) < threshold) { // Check if sensor detects black line
    motor1.drive(-1 * turnspeed);
    motor2.drive(turnspeed);
  }
  motor1.drive(0);
  motor2.drive(0);
  delay(50);
}

void forwardstep() {
  int battV = analogRead(7) - 770;
  // Add actions if you want to utilize battery voltage in control logic
}
