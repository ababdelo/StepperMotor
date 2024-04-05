/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StepperMotor.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdelo <ababdelo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:22:36 by ababdelo          #+#    #+#             */
/*   Updated: 2024/04/05 17:55:51 by ababdelo         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../Includes/StepperMotor.h"

/*Default Constructor*/
StepperMotor::StepperMotor(int *pins, int stepsPerRevolution) {
  Initialize();
  this->stepsPerRevolution = stepsPerRevolution;
  stepPins = new int[4];
  for (int i = 0; i < 4; i++) {
    stepPins[i] = pins[i];
    pinMode(stepPins[i], OUTPUT);
  }
}

// Destructor
StepperMotor::~StepperMotor() {
  delete[] stepPins; // Free memory allocated for stepPins array
}

void  StepperMotor::Initialize(){
  stepNumber = 0;
  forward = true;
  slowSpeed = 2000; // Default slow speed (microseconds)
  mediumSpeed = 1000; // Default medium speed (microseconds)
  fastSpeed = 500; // Default fast speed (microseconds)
  minDelayMicros = 50; // Minimum delay between steps (microseconds)
  acceleration = 500; // Default acceleration rate (RPM/s)
  deceleration = 500; // Default deceleration rate (RPM/s)
}

// Set the acceleration rate (RPM/s)
void StepperMotor::setAcceleration(float acceleration) {
  this->acceleration = acceleration;
}

// Set the deceleration rate (RPM/s)
void StepperMotor::setDeceleration(float deceleration) {
  this->deceleration = deceleration;
}

// Move forward for a specified duration at a given speed
void StepperMotor::moveForwardForTime(unsigned long duration, float speedRPM) {
  calculateSpeeds(speedRPM); // Calculate delays based on speed
  unsigned long startTime = millis(); // Record start time
  unsigned long elapsed = 0; // Elapsed time
  
  // Loop until the specified duration is reached
  while (elapsed < duration) {
    unsigned long stepDelay = map(elapsed, 0, duration, max(slowSpeed, minDelayMicros), min(fastSpeed, minDelayMicros + acceleration * (duration - elapsed)));
    OneStep(true); // Move one step forward
    delayMicroseconds(stepDelay); // Delay between steps
    elapsed = millis() - startTime; // Update elapsed time
  }
}

// Move backward for a specified duration at a given speed
void StepperMotor::moveBackwardForTime(unsigned long duration, float speedRPM) {
  calculateSpeeds(speedRPM); // Calculate delays based on speed
  unsigned long startTime = millis(); // Record start time
  unsigned long elapsed = 0; // Elapsed time
  
  // Loop until the specified duration is reached
  while (elapsed < duration) {
    unsigned long stepDelay = map(elapsed, 0, duration, max(slowSpeed, minDelayMicros), min(fastSpeed, minDelayMicros + acceleration * (duration - elapsed)));
    OneStep(false); // Move one step backward
    delayMicroseconds(stepDelay); // Delay between steps
    elapsed = millis() - startTime; // Update elapsed time
  }
}

// Move one step in the specified direction
void StepperMotor::OneStep(bool dir) {
  if (dir) {
    moveForward(); // Move forward
  } else {
    moveBackward(); // Move backward
  }

  // Update step number based on direction
  if (forward) {
    stepNumber++;
    if (stepNumber > 3) {
      stepNumber = 0; // Reset step number
    }
  } else {
    stepNumber--;
    if (stepNumber < 0) {
      stepNumber = 3; // Reset step number
    }
  }
}

// Move forward one step
void StepperMotor::moveForward() {
  switch (stepNumber) {
    case 0:
      Control(1, 0, 0, 0);
      break;
    case 1:
      Control(0, 1, 0, 0);
      break;
    case 2:
      Control(0, 0, 1, 0);
      break;
    case 3:
      Control(0, 0, 0, 1);
      break;
  }
}

// Move backward one step
void StepperMotor::moveBackward(void) {
  switch (stepNumber) {
    case 0:
      Control(0, 0, 0, 1);
      break;
    case 1:
      Control(0, 0, 1, 0);
      break;
    case 2:
      Control(0, 1, 0, 0);
      break;
    case 3:
      Control(1, 0, 0, 0);
      break;
  }
}

void StepperMotor::Control(int val_1, int val_2, int val_3, int val_4){
      digitalWrite(stepPins[0], val_1);
      digitalWrite(stepPins[1], val_2);
      digitalWrite(stepPins[2], val_3);
      digitalWrite(stepPins[3], val_4);
}

// Calculate delays for slow, medium, and fast speeds based on the target speed (RPM)
void StepperMotor::calculateSpeeds(float speedRPM) {
  float stepsPerSecond = speedRPM / 60 * stepsPerRevolution;
  
  // Calculate time per step (in microseconds) for slow, medium, and fast speeds
  slowSpeed = 1000000 / (stepsPerSecond * 1.2); // Add some margin for smoother motion
  mediumSpeed = 1000000 / stepsPerSecond;
  fastSpeed = 1000000 / (stepsPerSecond * 0.8); // Add some margin for smoother motion
}