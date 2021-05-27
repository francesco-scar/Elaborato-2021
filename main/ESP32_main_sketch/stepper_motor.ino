#define ANGLE_PER_STEP 1.8
#define MICROSTEPPING_RATIO 16.0
#define STEPS_PER_TURN 360/ANGLE_PER_STEP*MICROSTEPPING_RATIO

#define MAX_H_OFFSET 100
#define MAX_V_OFFSET 20000

bool disable_motor = false;
long h_steps_offset = 0;
long v_steps_offset = 0;

void move_stepper (long n_steps, float speed, float acceleration, int dir_pin, int step_pin, int enable_pin) {    // speed in steps/s, acceleration in steps/s^2
  if (n_steps < 0) {
    digitalWrite(dir_pin, HIGH);
  } else {
    digitalWrite(dir_pin, LOW);
  }

  unsigned long t_offset = micros();
  unsigned long t;
  unsigned long acceleration_limit_steps = 0.5 * speed * speed / acceleration + 0.5;
  bool acceleration_phase = true;                                                     // Bool flags to deterimine current status
  bool constant_phase = false;
  bool deceleration_phase = false;
  bool condition;

  if (acceleration_limit_steps > abs(n_steps) / 2) {
    acceleration_limit_steps = abs(n_steps) / 2;
    speed = sqrt(2 * acceleration_limit_steps * acceleration);
  }

  digitalWrite(enable_pin, LOW);
  for (long microsteps = 0; microsteps < abs(n_steps)*MICROSTEPPING_RATIO; microsteps++) {
    do {
      t = micros();
      if (constant_phase) {
        condition = ((microsteps / MICROSTEPPING_RATIO - acceleration_limit_steps) * 1000 > speed * (t - t_offset) / 1000.0);
      } else if (acceleration_phase) {
        condition = (microsteps * 1000000.0 / MICROSTEPPING_RATIO > 0.5 * acceleration * ((t - t_offset) / 1000.0) * ((t - t_offset) / 1000.0));
      } else if (deceleration_phase) {
        condition = (((microsteps / MICROSTEPPING_RATIO - (abs(n_steps) - acceleration_limit_steps)) * 1000000) > (speed * (t - t_offset) - 0.5 * acceleration * ((t - t_offset) / 1000.0) * ((t - t_offset) / 1000.0)));
        if (condition) {
          if (t - t_offset > speed / acceleration * 1000000) {
            condition = false;
          }
        }
      }
    } while (condition);
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(2);                 // Pulse must be at least 1us (from A4988 datasheet)
    digitalWrite(step_pin, LOW);
    delayMicroseconds(1);                 // Pulse must be at least 1us (from A4988 datasheet)
    if (constant_phase) {
      if (microsteps / MICROSTEPPING_RATIO >= abs(n_steps) - acceleration_limit_steps) {
        constant_phase = false;
        deceleration_phase = true;
        t_offset = micros();
      }
    } else if (acceleration_phase) {
      if (microsteps / MICROSTEPPING_RATIO >= acceleration_limit_steps) {
        acceleration_phase = false;
        constant_phase = true;
        t_offset = micros();
      }
    }
  }
  if (disable_motor) {
    digitalWrite(enable_pin, HIGH);
  }
}


void moveStepperHandler () {
  int steps = server.arg("steps").toInt();
  int speed = server.arg("speed").toInt();
  int acceleration = server.arg("acceleration").toInt();
  String motion = server.arg("motion");

  Serial.print(motion);
  Serial.print("  ");
  Serial.print(steps);
  Serial.print("  ");
  Serial.print(speed);
  Serial.print("  ");
  Serial.println(acceleration);

  if (motion == "down" || motion == "left") {
    steps = -steps;
  }

  if (motion == "up" || motion == "down") {
    if (abs(v_steps_offset + steps) >= MAX_V_OFFSET) {
      if (steps > 0) {
        steps = MAX_V_OFFSET - v_steps_offset;
      } else if (steps < 0) {
        steps = - (MAX_V_OFFSET + v_steps_offset);
      }
    }
    move_stepper(steps, speed, acceleration, DIR_V, STEP_V, ENABLE_V);
    v_steps_offset += steps;
  } else if (motion == "right" || motion == "left") {
    if (abs(h_steps_offset + steps) >= MAX_H_OFFSET) {
      if (steps > 0) {
        steps = MAX_H_OFFSET - h_steps_offset;
      } else if (steps < 0) {
        steps = - (MAX_H_OFFSET + h_steps_offset);
      }
    }
    move_stepper(steps, speed, acceleration, DIR_H, STEP_H, ENABLE_H);
    h_steps_offset += steps;
  } else {
    server.send(400, "text/plain", "BadRequest");
    return;
  }
  server.send(200, "text/plain", "OK");
}


void disableStepperHandler () {
  disable_motor = server.arg("val").toInt();
  server.send(200, "text/plain", "OK\n" + String(disable_motor));
  
  if (disable_motor) {
    digitalWrite(ENABLE_V, HIGH);
    digitalWrite(ENABLE_H, HIGH);
  } else {
    {
    digitalWrite(ENABLE_V, LOW);
    digitalWrite(ENABLE_H, LOW);
  }
  }
}
