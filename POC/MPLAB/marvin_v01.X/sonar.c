
#include <p32xxxx.h>
#include <sys/attribs.h>
#include "sonar.h"
#include "types.h"
#include "tools.h"


// va falloir envoyer les PINS a definir en entree et en sortie, le trigger LATF pour modifier letat de la sortie
// En faites on sen fous des interrupt..

/*
void    marvin_setup_interrupt_sonar1()
{
}

void    marvin_setup_interrupt_sonar2()
{
}
/*
 * Fonction qui init les pins pour utiliser le Sonar
 * Param 1: L'objet Sonar
 * Param 2: Adresse Registre PIN du Trigger (TRISx)
 * Param 3: Adresse Registre d'ETAT PIN Trigger (LATx)
 * Param 4: Adresse Registre PIN Echo (TRISx)
 * Param 5: Adresse Registre de lecture PIN Echo (PORTx)
 */

void    marvin_set_sonar(m_sonar *sonar, u32 *trig_pin, u32 *trig_etat, u32 *echo_pin, u32 *echo_read)
{
    sonar->state_trig_pin = trig_etat;
    sonar->read_echo_pin = echo_read;
    *trig_etat |= 0b0 << sonar->trig_attachpin;
    *trig_pin ^= 0b1 << sonar->trig_attachpin;     // (de base tout les bits du registre TRISE sont a 1 donc mask pour mettre a 0 le bit 0)
    *echo_pin |= 0b1 << sonar->echo_attachpin;      // mask pour mettre pin de echo en input
}

/*
 * Fonction qui envoi un signal sur le Trigger pour demander la mesure
 * Param 1: L'objet Sonar
 */

void    marvin_trigger(m_sonar *sonar)
{
    *(sonar->state_trig_pin) = 1 << sonar->trig_attachpin; // OUTPUT a 1
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    *(sonar->state_trig_pin) ^= 1 << sonar->trig_attachpin; // OUTPUT a 0
}

/*
 * Fonction qui lit le retour sur echo, et return la mesure en cm
 * Param 1: L'objet Sonar
 *  Set la periode du timer a utiliser a 1 seconde, avec TCKPS = 0b11;
 */

u16      marvin_pulseIn(m_sonar *sonar)
{
    u16 ret = 0;


    while (!(*(sonar->read_echo_pin) & (1 << sonar->echo_attachpin)))   //On attend un front montant
        TMR1 = 0;
    while (((*(sonar->read_echo_pin) & (1 << sonar->echo_attachpin))) && TMR1 != PR1)    // Duree lageur impulsion
        ret = TMR1;
    return (((ret * 1000000) / PR1 )/ 58);
}

/*
 * Fonction Maitre qui effectue une serie de x mesures (NBR_CAPTURE) et return la mediane
 * Param 1: L'objet Sonar
 */

u16      marvin_capture(m_sonar *sonar)
{
    u8 i = 0;

    u16 tab[NBR_CAPTURE] ={0};
   
    while (i < NBR_CAPTURE)
    {
        marvin_trigger(sonar); //on envoie le trig
    // Fonction de tri (c.f arduino)

       marvin_tri_insertion(tab, i,marvin_pulseIn(sonar));
        ++i;
    }
    return (marvin_calcul_median(tab, NBR_CAPTURE));
    // fonction de medianne (c.f arduino)
}
