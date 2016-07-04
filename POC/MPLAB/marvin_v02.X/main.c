/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on June 22, 2016, 6:34 PM
 */
#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"
#include "timer.h"
#include "Servo.h"
#include "setup.h"
#include "marvin.h"

        /*
         * Useless
        if (TMR1 == PR1)
       {
            marvin_send_message("Je suis Marvin et j'ai la tete comme une planete", 50);
            TMR1 = 0;
       }
         */

/*  PB AVEC LE RELAIS ALIM TOUT LE TEMPS A 5V SUR SERVO
 *      INTGRATION CODE
 *  FONCTION TIMER => OK
 *  FONCTION SERVO => OK
 *  FONCTION SONAR => OK
 *  FONCTION IR    => OK
 *  FONCTION LEDS  => OK
 * 
 *  FAIRE FONCTIONNER L'UART a
 *
 *  SERVO PITCH DEBATTEMENT MAX: 50 a 100, repos a 60
 */
u8 speed = 10;

int main()
{
    marvin_setup(&marvin);
    marvin_init(&marvin);
    marvin_stop_move(&marvin);
    while (1)
    {
        //if (marvin.counter1 > 30000)
            marvin_behavior1();
//                marvin_veille(60000);
    /*    else
        {
                    marvin_refresh(&marvin);
                    if (marvin_is_someone_found(marvin))
                    {
                        marvin_stop_move(&marvin);
                        marvin_set_lux_speed(&marvin.led_left, 25, 1, 40);
                        marvin_set_lux_speed(&marvin.led_right, 25, 1, 40);
                        marvin_move_servo_speed(&marvin.servo_pitch, 100, 1, 25);
                    //    marvin_send_message(UART_SEND_FIND);
                     }
                    if (marvin_is_someone_left(marvin))
                    {
                         marvin_move_servo_speed(&marvin.servo_yaw, marvin.servo_yaw.pos +10, 1, 25);
                         marvin_set_lux_speed(&marvin.led_left, 25, 1, 20);
                         marvin_set_lux_speed(&marvin.led_right, 2, 1, 20);
                         marvin_move_servo_speed(&marvin.servo_pitch, 60, 1, 25);
                    //      marvin_send_message(UART_SEND_LEFT);
                    }
                    if (marvin_is_someone_right(marvin))
                    {
                         marvin_move_servo_speed(&marvin.servo_yaw, marvin.servo_yaw.pos - 10, 1, 25);
                         marvin_set_lux_speed(&marvin.led_right, 25, 1, 20);
                         marvin_set_lux_speed(&marvin.led_left, 2, 1, 20);
                         marvin_move_servo_speed(&marvin.servo_pitch, 60, 1, 25);
//                         marvin_send_message(UART_SEND_RIGHT);
                    }
        }*/
    }
    return (0);
}


