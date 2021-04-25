#include "registers_definition.h"

#define STEP 13
#define DIRECTION 12          // If HIGH angle decrease, if LOW angle increase
#define SPEED 10

#define ANGLE_PER_STEP 1.8
#define MICROSTEPPING_RATIO 16.0
#define STEPS_PER_TURN 360/ANGLE_PER_STEP*MICROSTEPPING_RATIO

long current_steps_offset = 0;


/*
  void reach_position (long step_positions, float speed, float acceleration) {    // speed in steps/s, acceleration in steps/s^2
  int n_steps = (step_positions - current_steps_offset);
  if (n_steps < 0) {
    GET_PORT(DIRECTION) |= GET_BIT_MASK(DIRECTION);
  } else {
    GET_PORT(DIRECTION) &= ~GET_BIT_MASK(DIRECTION);
  }

  int time_acceleration = speed/acceleration*1000000;     // ms that takes to reach speed "speed" with acceleration "acceleration" (dv = a*dt)
  float current_speed = 1000;
  unsigned long micros_offset = micros();
  unsigned long micros_current;
  unsigned long dt = 0;
  bool in_acceleration_time = true, in_deceleration_time;
  for (int microsteps = 0; microsteps < abs(n_steps)*MICROSTEPPING_RATIO; microsteps++) {
    /*
    do {
      millis_current = millis();
  //      in_acceleration_time = (millis_current-millis_offset) < time_acceleration;


    } while ((in_acceleration_time && (((millis_current - millis_offset)/1000.0)*((millis_current - millis_offset)/1000.0)*acceleration < MICROSTEPPING_RATIO*microsteps)) || (!in_acceleration_time && (millis_current - millis_offset)*speed < 1000.0/MICROSTEPPING_RATIO*microsteps));
*//*
  dt = 1000000 / (current_speed);

  do {
  micros_current = micros();
  } while (micros_current - micros_offset < dt);
  micros_offset = micros_current;
  GET_PORT(STEP) |= GET_BIT_MASK(STEP);
  delayMicroseconds(2);                 // Pulse must be at least 1us (from A4988 datasheet)
  GET_PORT(STEP) &= ~GET_BIT_MASK(STEP);
  delayMicroseconds(2);                 // Pulse must be at least 1us (from A4988 datasheet)
  Serial.println(dt);
  micros_current = micros();
  current_speed += acceleration / 1000000.0 * (micros_current - micros_offset);
  }
  current_steps_offset = step_positions;
  }* /

  /*
  void calibrate_zero() {
  char c = -1;
  while (c != 'k') {
    if (c == '+') {
      reach_position(current_steps_offset + 1, 0);
    } else if (c == '-') {
      reach_position(current_steps_offset - 1, 0);
    }
    c = Serial.read();
  }
  current_steps_offset = 0;
  }*/

int i = 0;
void setup() {
  Serial.begin(115200);
  GET_DDR(STEP) |= GET_BIT_MASK(STEP);
  GET_DDR(DIRECTION) |= GET_BIT_MASK(DIRECTION);
  //calibrate_zero();
  delay(1000);

  unsigned long t = millis();
  reach_position(2000, 500, 400);
  Serial.println(millis() - t);
  delay(2000);
  t = millis();
  reach_position(0, 100, 25);
  Serial.println(millis() - t);

}

void reach_position (long step_positions, float speed, float acceleration) {    // speed in steps/s, acceleration in steps/s^2
  long n_steps = (step_positions - current_steps_offset);
  if (n_steps < 0) {
    GET_PORT(DIRECTION) |= GET_BIT_MASK(DIRECTION);
  } else {
    GET_PORT(DIRECTION) &= ~GET_BIT_MASK(DIRECTION);
  }

  unsigned long t_offset = micros();
  unsigned long t;
  unsigned long acceleration_limit_steps = 0.5 * speed * speed / acceleration + 0.5;
  bool acceleration_phase = true;                                                     // Bool flags to deterimine current status
  bool constant_phase = false;
  bool deceleration_phase = false;
  bool condition;
  for (long microsteps = 0; microsteps < abs(n_steps)*MICROSTEPPING_RATIO; microsteps++) {
    do {
      t = micros();
      if (constant_phase) {
        condition = ((microsteps/MICROSTEPPING_RATIO - acceleration_limit_steps)*1000 > speed * (t - t_offset) / 1000.0);
      } else if (acceleration_phase) {
        condition = (microsteps * 1000000.0 / MICROSTEPPING_RATIO > 0.5 * acceleration * ((t - t_offset) / 1000.0) * ((t - t_offset) / 1000.0));
      } else if (deceleration_phase) {
        condition = (((microsteps/MICROSTEPPING_RATIO - (abs(n_steps) - acceleration_limit_steps))*1000000) > (speed * (t - t_offset) - 0.5 * acceleration * ((t - t_offset) / 1000.0) * ((t - t_offset) / 1000.0)));
/*        Serial.print(((microsteps/MICROSTEPPING_RATIO - (abs(n_steps) - acceleration_limit_steps))*1000000));
        Serial.print(" ");
        Serial.println((speed * (t - t_offset) - 0.5 * acceleration * ((t - t_offset) / 1000.0) * ((t - t_offset) / 1000.0)));*/
        if (condition) {
          if (microsteps == abs(n_steps)*MICROSTEPPING_RATIO - 1) {
            condition = false;
          }
        }
      }
    } while (condition);
    GET_PORT(STEP) |= GET_BIT_MASK(STEP);
    delayMicroseconds(2);                 // Pulse must be at least 1us (from A4988 datasheet)
    GET_PORT(STEP) &= ~GET_BIT_MASK(STEP);
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
  current_steps_offset = step_positions;
}


void loop() {
  /*
    for (int i = 0; i < 40; i++) {
      reach_position(current_steps_offset + 50, 0);
      Serial.println(current_steps_offset);
      delay(1000);
    }
    for (int i = 0; i < 40; i++) {
      reach_position(current_steps_offset - 50, 0);
      Serial.println(current_steps_offset);
      delay(1000);
    }*/
}
