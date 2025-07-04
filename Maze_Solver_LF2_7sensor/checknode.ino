void checknode() {
  yellow();
  l = 0;
  r = 0;
  s = 0;
  u = 0;
  e = 0;
  paths = 0;

  // Check if the bot is at a node and identify the possible exits

  if (analogRead(6) < threshold[6]) r = 1; // Right side on black line
  if (analogRead(0) < threshold[0]) l = 1; // Left side on black line
  if ((analogRead(0) > threshold[0]) && (analogRead(6) > threshold[6]) && (analogRead(3) > threshold[3])) {
    u = 1; // No black lines on left, right, or center
  }
  if ((analogRead(3) < threshold[3]) && (analogRead(5) < threshold[5]) && (analogRead(6) < threshold[6])) {
    e = 1; // All sensors detect black, indicating a potential end
  }

  // If 'u' (no black lines in all directions) is not detected
  if (u == 0) {
    for (int i = 0; i < FT; i++) {
      magenta();
      // botinchforward(); // Uncomment and implement if required
      PID(); // Line-following PID control
      if (analogRead(6) < threshold[6]) r = 1; // Re-check right sensor
      if (analogRead(0) < threshold[0]) l = 1; // Re-check left sensor
    }

    for (int i = 0; i < FT; i++) {
      cyan();
      // botinchforward(); // Uncomment if incremental forward motion is needed
      PID();
      if (analogRead(3) < threshold[3]) s = 1; // Center sensor detects line
      if ((e == 1) && (analogRead(5) < threshold[5]) && (analogRead(6) < threshold[6]) && (analogRead(3) < threshold[3])) e = 2; // Check end condition
    }

    if (e == 2) {
      for (int i = 0; i < FT; i++) {
        // botinchforward(); // Uncomment if needed
        PID();
      }
      if ((analogRead(5) < threshold[5]) && (analogRead(6) < threshold[6]) && (analogRead(3) < threshold[3])) e = 3; // Confirm end position
    }
  }

  // If 'u' (no black lines) is detected, move forward slightly to reassess
  if (u == 1) {
    for (int i = 0; i < 5; i++) {
      botinchforward(); // Incrementally move forward
    }
  }

  // Calculate number of possible paths (left, straight, right)
  paths = l + s + r;
}
