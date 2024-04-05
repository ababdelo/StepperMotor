/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   STEPMTR_CNTRL.ino                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdelo <ababdelo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:00:34 by ababdelo          #+#    #+#             */
/*   Updated: 2024/04/05 18:27:26 by ababdelo         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../Includes/StepperMotor.h"

// Define the pins connected to the stepper motor
const int STEPPER_PINS[] = {12, 11, 10, 9};

// Define the number of steps per revolution of the stepper motor
const int STEPS_PER_REVOLUTION = 200;

// Create an instance of the StepperMotor class
StepperMotor myStepper(STEPPER_PINS, STEPS_PER_REVOLUTION);

void setup() {
  // Set up Serial communication
  Serial.begin(9600);
}

void loop() {
  // Move the stepper motor forward for 2 seconds at slow speed
  Serial.println("Moving forward at slow speed...");
  myStepper.moveForwardForTime(2000, 60); // Speed in RPM

  delay(1000); // Delay for 1 second

  // Move the stepper motor backward for 1 second at medium speed
  Serial.println("Moving backward at medium speed...");
  myStepper.moveBackwardForTime(1000, 120); // Speed in RPM

  delay(1000); // Delay for 1 second
}
