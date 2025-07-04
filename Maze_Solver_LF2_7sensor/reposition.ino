void reposition() {
  blue();  // Indicate repositioning mode with blue LED

  if (e == 3) {  // If end condition is met (detected as an endpoint)
    str += 'E';
    endFound = 1;
    red();      // Indicate endpoint with red LED
    botstop();  // Stop at endpoint
    delay(2000);
  }
  else if (l == 1) {  // Left path available (left sensor detects black line)
    if (paths > 1) str += 'L';
    botleft();  // Take left turn
  }
  else if (s == 1) {  // Straight path available (center sensor detects black line)
    if (paths > 1) str += 'S';
  }
  else if (r == 1) {  // Right path available (right sensor detects black line)
    if (paths > 1) str += 'R';
    botright();  // Take right turn
  }
  else if (u == 1) {  // U-turn needed (no path forward)
    magenta();  // Indicate U-turn with magenta LED
    str += 'U';
    botuturn();  // Perform U-turn
  }

  lightsoff();  // Turn off all indicator lights after repositioning
}
