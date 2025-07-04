void calibrate() {
  // Initialize min and max values for each sensor
  for (int i = 0; i < 7; i++) {
    minValues[i] = analogRead(i);
    maxValues[i] = analogRead(i);
  }

  // Rotate the motors slightly to capture readings from different positions
  for (int i = 0; i < 1500; i++) {
    motor1.drive(50);  // Rotate left motor forward
    motor2.drive(-50); // Rotate right motor backward

    // Update min and max values for each sensor
    for (int j = 0; j < 7; j++) {
      int sensorValue = analogRead(j);
      if (sensorValue < minValues[j]) {
        minValues[j] = sensorValue;
      }
      if (sensorValue > maxValues[j]) {
        maxValues[j] = sensorValue;
      }
    }
  }

  // Calculate the threshold for each sensor based on min and max values
  for (int i = 0; i < 7; i++) {
    threshold[i] = (minValues[i] + maxValues[i]) / 2;
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" Threshold: ");
    Serial.println(threshold[i]);
  }

  // Stop the motors after calibration
  motor1.drive(0);
  motor2.drive(0);
}
