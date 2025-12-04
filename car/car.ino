// ==================== MOTOR PINS ====================
int M1_dir = 4;  // Motor 1 direction pin (Front Left) - controls which way motor spins
int M1_pwm = 3;  // Motor 1 PWM pin (Front Left) - controls motor speed (0-255)
int M2_dir = 12; // Motor 2 direction pin (Front Right)
int M2_pwm = 11; // Motor 2 PWM pin (Front Right)
int M3_dir = 8;  // Motor 3 direction pin (Rear Left)
int M3_pwm = 5;  // Motor 3 PWM pin (Rear Left)
int M4_dir = 7;  // Motor 4 direction pin (Rear Right)
int M4_pwm = 6;  // Motor 4 PWM pin (Rear Right)

// ==================== JOYSTICK PINS ====================
int joyX = A0; // Joystick X-axis (Left/Right movement) - analog pin 0
int joyY = A1; // Joystick Y-axis (Forward/Backward movement) - analog pin 1
int Switch = 9; // Button on joystick controller - digital pin 9

// ==================== SPEED VARIABLES ====================
int maxSpeed = 255; // Maximum speed value for PWM (0-255 is full range)
int deadZone = 100; // Deadzone to prevent joystick noise when idle (small movements ignored)

void setup() {
  // Start serial communication at 9600 baud for debugging
  Serial.begin(9600);

  // Set all motor direction pins as outputs (they send signals to motor driver)
  pinMode(M1_dir, OUTPUT); 
  pinMode(M1_pwm, OUTPUT); // Set M1 PWM pin as output
  
  pinMode(M2_dir, OUTPUT); 
  pinMode(M2_pwm, OUTPUT); // Set M2 PWM pin as output
  
  pinMode(M3_dir, OUTPUT); 
  pinMode(M3_pwm, OUTPUT); // Set M3 PWM pin as output
  
  pinMode(M4_dir, OUTPUT); 
  pinMode(M4_pwm, OUTPUT); // Set M4 PWM pin as output
}

void loop() {
  // Read joystick X value (0-1023) and center it around 0 (-512 to +511)
  // Left = negative, Right = positive
  int xVal = analogRead(joyX) - 512;
  
  // Read joystick Y value (0-1023) and center it around 0 (-512 to +511)
  // Forward = positive, Backward = negative
  int yVal = analogRead(joyY) - 512;

  // ==================== DEADZONE FILTER ====================
  // If X movement is less than deadzone, set it to 0 (ignore small movements)
  if (abs(xVal) < deadZone) xVal = 0;
  
  // If Y movement is less than deadzone, set it to 0 (ignore small movements)
  if (abs(yVal) < deadZone) yVal = 0;

  // ==================== SPEED CALCULATION ====================
  // Convert Y-axis to forward speed (0-255)
  // abs() makes it always positive, map converts -512 to +512 range into 0-255 range
  int speedF = map(abs(yVal), 0, 512, 0, maxSpeed);
  
  // Convert X-axis to turning speed (-255 to +255)
  // Left turn = negative, Right turn = positive
  int turn = map(xVal, -512, 512, -maxSpeed, maxSpeed);

  // ==================== MIXING ALGORITHM ====================
  // Calculate left side motor speed by subtracting half the turn value
  // This slows down left motors when turning right, speeds up when turning left
  int leftSpeed  = speedF - turn / 2;
  
  // Calculate right side motor speed by adding half the turn value
  // This speeds up right motors when turning right, slows down when turning left
  int rightSpeed = speedF + turn / 2;

  // ==================== SPEED LIMITS ====================
  // Make sure speeds don't exceed 0-255 range
  // constrain(value, min, max) keeps value between min and max
  leftSpeed = constrain(leftSpeed, 0, maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, maxSpeed);

  // ==================== SET LEFT MOTORS (M1 & M3) ====================
  // If moving forward (yVal positive or zero), set direction pins HIGH
  if (yVal >= 0) { 
    digitalWrite(M1_dir, HIGH); // Motor 1 forward
    digitalWrite(M3_dir, HIGH); // Motor 3 forward
  }
  // If moving backward (yVal negative), set direction pins LOW
  else { 
    digitalWrite(M1_dir, LOW); // Motor 1 backward
    digitalWrite(M3_dir, LOW); // Motor 3 backward
  }
  
  // Apply the left side speed (0-255) to left motors
  analogWrite(M1_pwm, leftSpeed); // Motor 1 speed
  analogWrite(M3_pwm, leftSpeed); // Motor 3 speed

  // ==================== SET RIGHT MOTORS (M2 & M4) ====================
  // If moving forward (yVal positive or zero), set direction pins HIGH
  if (yVal >= 0) { 
    digitalWrite(M2_dir, HIGH); // Motor 2 forward
    digitalWrite(M4_dir, HIGH); // Motor 4 forward
  }
  // If moving backward (yVal negative), set direction pins LOW
  else { 
    digitalWrite(M2_dir, LOW); // Motor 2 backward
    digitalWrite(M4_dir, LOW); // Motor 4 backward
  }
  
  // Apply the right side speed (0-255) to right motors
  analogWrite(M2_pwm, rightSpeed); // Motor 2 speed
  analogWrite(M4_pwm, rightSpeed); // Motor 4 speed

  // Wait 20 milliseconds before reading joystick again
  // This prevents the loop from running too fast and overwhelming the motors
  delay(20);
}