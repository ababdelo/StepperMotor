/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StepperMotor.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdelo <ababdelo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:21:39 by ababdelo          #+#    #+#             */
/*   Updated: 2024/04/05 23:31:32 by ababdelo         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef STEPPERMOTOR_HPP
#define STEPPERMOTOR_HPP

#include <Arduino.h>

class StepperMotor {
  public:
    StepperMotor(int *pins, int stepsPerRevolution); // Constructor
    ~StepperMotor(); // Destructor

    void  moveForward(unsigned long duration, double speedRPM); // Move forward for a specified duration at a given speed
    void  moveBackward(unsigned long duration, double speedRPM); // Move backward for a specified duration at a given speed
    void  setAcceleration(double acceleration); // Set the acceleration rate (RPM/s)
    void  setDeceleration(double deceleration); // Set the deceleration rate (RPM/s)

  private:
    int* stepPins; // Array of pins connected to the stepper motor coils
    int stepNumber; // Current step number
    bool forward; // Direction of rotation
    double acceleration; // Acceleration rate (RPM/s)
    double deceleration; // Deceleration rate (RPM/s)
    unsigned long slowSpeed; // Minimum speed (RPM)
    unsigned long mediumSpeed; // Medium speed (RPM)
    unsigned long fastSpeed; // Maximum speed (RPM)
    unsigned long minDelayMicros; // Minimum delay between steps (microseconds)
    int stepsPerRevolution; // Number of steps per revolution

    void  oneStep(bool dir); // Move one step in the specified direction
    void  MVFRWRD(); // Move forward one step
    void  MVBCKWRD(); // Move backward one step
    void  setCoilState(int val_1, int val_2, int val_3, int val_4); // Set the state of the stepper motor coils
    void  setSpeeds(double speedRPM); // Calculate delays based on speed
};

#endif
