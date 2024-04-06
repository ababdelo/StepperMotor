/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StepperMotor.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdelo <ababdelo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:22:36 by ababdelo          #+#    #+#             */
/*   Updated: 2024/04/05 23:32:36 by ababdelo         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../Includes/StepperMotor.hpp"

/*Default Constructor*/
StepperMotor::StepperMotor(int *pins, int stepsPerRevolution) :
  stepNumber(0),
  forward(true),
  acceleration(500),
  deceleration(500),
  slowSpeed(2000),
  mediumSpeed(1000),
  fastSpeed(500),
  minDelayMicros(50),
  stepsPerRevolution(stepsPerRevolution)
{
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

// Set the acceleration rate (RPM/s)
void  StepperMotor::setAcceleration(double acceleration) {
  this->acceleration = acceleration;
}

// Set the deceleration rate (RPM/s)
void  StepperMotor::setDeceleration(double deceleration) {
  this->deceleration = deceleration;
}

// Move forward for a specified duration at a given speed
void  StepperMotor::moveForward(unsigned long duration, double speedRPM) {
  setSpeeds(speedRPM); // Calculate delays based on speed
  unsigned long startTime = millis(); // Record start time
  unsigned long elapsed = 0; // Elapsed time

  // Loop until the specified duration is reached
  while (elapsed < duration) {
    unsigned long stepDelay = map(elapsed, 0, duration, max(slowSpeed, minDelayMicros), min(fastSpeed, minDelayMicros + acceleration * (duration - elapsed)));
    oneStep(true); // Move one step forward
    delayMicroseconds(stepDelay); // Delay between steps
    elapsed = millis() - startTime; // Update elapsed time
  }
}

// Move backward for a specified duration at a given speed
void  StepperMotor::moveBackward(unsigned long duration, double speedRPM) {
  setSpeeds(speedRPM); // Calculate delays based on speed
  unsigned long  startTime = millis(); // Record start time
  unsigned long elapsed = 0; // Elapsed time

  // Loop until the specified duration is reached
  while (elapsed < duration) {
    unsigned long stepDelay = map(elapsed, 0, duration, max(slowSpeed, minDelayMicros), min(fastSpeed, minDelayMicros + acceleration * (duration - elapsed)));
    oneStep(false); // Move one step backward
    delayMicroseconds(stepDelay); // Delay between steps
    elapsed = millis() - startTime; // Update elapsed time
  }
}

// Move one step in the specified direction
void  StepperMotor::oneStep(bool dir) {
  if (dir) {
    MVFRWRD(); // Move forward
  } else {
    MVBCKWRD(); // Move backward
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
void  StepperMotor::MVFRWRD() {
  switch (stepNumber) {
    case 0:
      setCoilState(1, 0, 0, 0);
      break;
    case 1:
      setCoilState(0, 1, 0, 0);
      break;
    case 2:
      setCoilState(0, 0, 1, 0);
      break;
    case 3:
      setCoilState(0, 0, 0, 1);
      break;
  }
}

// Move backward one step
void  StepperMotor::MVBCKWRD(void) {
  switch (stepNumber) {
    case 0:
      setCoilState(0, 0, 0, 1);
      break;
    case 1:
      setCoilState(0, 0, 1, 0);
      break;
    case 2:
      setCoilState(0, 1, 0, 0);
      break;
    case 3:
      setCoilState(1, 0, 0, 0);
      break;
  }
}

// Set the coil state based on the values of the four pins
void  StepperMotor::setCoilState(int val_1, int val_2, int val_3, int val_4) {
  digitalWrite(stepPins[0], val_1);
  digitalWrite(stepPins[1], val_2);
  digitalWrite(stepPins[2], val_3);
  digitalWrite(stepPins[3], val_4);
}

// Calculate delays for slow, medium, and fast speeds based on the target speed (RPM)
void  StepperMotor::setSpeeds(double speedRPM) {
  double  stepsPerSecond = speedRPM / 60 * stepsPerRevolution;

  // Calculate time per step (in microseconds) for slow, medium, and fast speeds
  slowSpeed = 1000000 / (stepsPerSecond * 1.2); // Add some margin for smoother motion
  mediumSpeed = 1000000 / stepsPerSecond;
  fastSpeed = 1000000 / (stepsPerSecond * 0.6); // Add some margin for smoother motion
}
