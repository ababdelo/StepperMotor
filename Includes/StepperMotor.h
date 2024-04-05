/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StepperMotor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdelo <ababdelo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:21:39 by ababdelo          #+#    #+#             */
/*   Updated: 2024/04/05 17:55:55 by ababdelo         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef StepperMotor_h
#define StepperMotor_h

#include <Arduino.h>

class StepperMotor {
  public:
    StepperMotor(int *pins, int stepsPerRevolution); 
    ~StepperMotor();
    
    void  Initialize();
    void  moveForwardForTime(unsigned long duration, float speedRPM);
    void  moveBackwardForTime(unsigned long duration, float speedRPM);
    void  setAcceleration(float acceleration);
    void  setDeceleration(float deceleration);

  private:
    int* stepPins;
    int stepNumber;
    bool forward;
    float acceleration;
    float deceleration;
    unsigned long slowSpeed;
    unsigned long mediumSpeed;
    unsigned long fastSpeed;
    unsigned long minDelayMicros;
    int stepsPerRevolution;

    void  OneStep(bool dir);
    void  moveForward();
    void  moveBackward();
    void  Control(int val_1, int val_2, int val_3, int val_4);
    void  calculateSpeeds(float speedRPM);
};

#endif
