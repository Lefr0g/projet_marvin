/*
 * File:   setup.h
 * Author: bocal
 *
 * Created on June 16, 2016, 4:54 PM
 */

#ifndef SETUP_H
#define	SETUP_H

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"
#include "timer.h"
#include "Servo.h"
#include "sonar.h"
//#include "uart.h"

void    marvin_mapping_pin();
void    marvin_setup();
void    marvin_setup_leds();
void    marvin_setup_timer();
void    marvin_setup_sonar();
void    marvin_setup_servo();
void    marvin_setup_interrupt();
void    marvin_setup_interrupt_tmr1();
void    marvin_setup_interrupt_tmr3();
void    marvin_enable_sensor_servo();

#endif	/* SETUP_H */

