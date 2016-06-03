/* 
 * File:   sonar.h
 * Author: bocal
 *
 * Created on June 2, 2016, 7:01 PM
 */

#ifndef SONAR_H
#define	SONAR_H
#include "types.h"



#define SONAR1_SET_TRIG &TRISE  // E0
#define SONAR1_STATE_TRIG &LATE // E0
#define SONAR1_SET_ECHO &TRISD  // D9
#define SONAR1_READ_ECHO &PORTD // RD9


#define NBR_CAPTURE 11
typedef struct  s_sonar
{
    u32     *state_trig_pin;// etat
    u32     *read_echo_pin;// read
   // u8      i; // la ou en est dans les captures
    //u16     tab[NBR_CAPTURE]; // Les valeurs de capture;
}               m_sonar;


void    marvin_set_sonar(m_sonar *sonar, u32 *trig_pin, u32 *trig_etat, u32 *echo_pin, u32 *echo_read);
void    marvin_trigger(m_sonar *sonar);
u16     marvin_pulseIn(m_sonar *sonar); //Retourne Une seule capture
u16     marvin_capture(m_sonar *sonar);// retourne une distance en cm dedans on appelera le fonction de tri et la fonction de calcul de medianne

#endif	/* SONAR_H */

