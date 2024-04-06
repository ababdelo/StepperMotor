/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   STEPMTR_CNTRL.ino                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdelo <ababdelo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 15:00:34 by ababdelo          #+#    #+#             */
/*   Updated: 2024/04/05 23:17:49 by ababdelo         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <StepperMotor.hpp>

// Define the pins connected to your stepper motor coils
#define STEPPER_PINS {9, 10, 11, 12} // You may need to change these values according to your setup

// Define the number of steps per revolution for your stepper motor
# define STEPS_PER_REVOLUTION 200 // You may need to change this value according to your motor revolution

// Create an instance of the StepperMotor class
StepperMotor myStepper(STEPPER_PINS, STEPS_PER_REVOLUTION);

void setup() {
  // Set up the serial monitor
  Serial.begin(9600);
  
  // Set up the motor acceleration and deceleration
  myStepper.setAcceleration(500); // You may need to change these values according to your motor specifications
  myStepper.setDeceleration(500); // You may need to change these values according to your motor specifications
}

void loop() {
  // Move forward at slow speed for 5 seconds
  Serial.println("Moving forward at slow speed...");
  myStepper.moveForward(5000, 20); // Duration: 5000 milliseconds, Speed: 20 RPM
  delay(1000); // Wait for 1 second
  
  // Move backward at medium speed for 5 seconds
  Serial.println("Moving backward at medium speed...");
  myStepper.moveBackward(5000, 60); // Duration: 5000 milliseconds, Speed: 60 RPM
  delay(1000); // Wait for 1 second
  
  // Move forward at fast speed for 5 seconds
  Serial.println("Moving forward at fast speed...");
  myStepper.moveForward(5000, 120); // Duration: 5000 milliseconds, Speed: 120 RPM
  delay(1000); // Wait for 1 second
}
