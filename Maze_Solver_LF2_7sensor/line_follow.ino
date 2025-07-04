void linefollow() {
  green();  // Indicate line-following mode with green LED
  paths = 0;
  
  // Continue following the line as long as the center sensor detects black
  while ((analogRead(0) < threshold[0]) && (analogRead(6) < threshold[6]) && (analogRead(3) > threshold[3])) {
    PID();
  }
  
  lightsoff(); // Turn off all indicator lights when line-following ends
}

void PID() {
  // Calculate the error based on left and right sensors
  int error = analogRead(2) - analogRead(4);

  P = error;
  I += error;
  D = error - previousError;

  // Calculate PID correction
  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
  previousError = error;

  // Adjust motor speeds based on PID values
  lsp = lfspeed - PIDvalue;
  rsp = lfspeed + PIDvalue;

  // Constrain motor speeds within allowed limits
  lsp = constrain(lsp, 0, 200);
  rsp = constrain(rsp, 0, 200);

  // Adjust based on sensor readings to follow the black line
  if (analogRead(0) < threshold[0]) {  // Left sensor on black
    motor1.drive(rsp * 0.8);  // Slight right turn
    motor2.drive(lsp);
  }
  else if (analogRead(6) < threshold[6]) {  // Right sensor on black
    motor1.drive(rsp);
    motor2.drive(lsp * 0.8);  // Slight left turn
  }
  else {  // Center sensor on black (balanced)
    motor1.drive(rsp);
    motor2.drive(lsp);
  }
}
