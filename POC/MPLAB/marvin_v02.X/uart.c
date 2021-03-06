#include "timer.h"
#include "uart.h"
#include "types.h"
#include "marvin.h"
#include <p32xxxx.h>
#include <sys/attribs.h>

/*
 * Note pour test sur protoboard U1Rx -> RF2 ; U1Tx -> RF3
 * Fonction qui set le BAUD RATE automatiquement en fonction des reglages OSCILLATOR
 */
void    marvin_setup_baud_rate()
{
    REGISTER_BAUD_RATE = marvin_calcul_oscillator_prescaler() / (4 * BAUD_RATE) - 1;
}

/*
 *  Fonction de config de l'UART
 *  Param1: Adresse du mode register de l'UART (UxMODE)
 *  Param2: Adresse du Status / Control register (UxSTA)
 */
void    marvin_setup_uart()
{
    marvin_setup_baud_rate(); // baud rate calcul en auto
    U1MODE = 0 | BRGH_x4 ;
    U1MODE |= PDSEL_00 |  STSEL_0;         // config de l'UART avec define choisit
    U1STA = 0 | UTXEN_1 | URXEN_1;
    U1MODE |= UART_ON;                               // Uart enable
}

/*
 *  Fonction qui envoi un tableau de donnees en UART
 *  Param1: Tableau a envoyer
 */
void    marvin_send_message(u8 *tab)
{
    while (*tab)
        U1TXREG = *tab++;
}

void marvin_send_trame(u8 *tab)
{
    marvin_send_message(tab);
    marvin_send_message(tab);
    marvin_send_message(tab);
    marvin_send_message(tab);
    marvin_send_message(tab);
    marvin_send_message(tab);
    marvin_send_message(tab);
    marvin_send_message(tab);
    marvin_send_message(tab);
    marvin_send_message(tab);
}
/*
 * Fonction de setup de l'interrupt, sur reception d'une trame
 * Param1: piority level a donner a l'interrupt
 */
void    marvin_setup_uart_interrupt(u8 priority_lvl)
{
    IFS1bits.U1RXIF = 0;
    IPC8bits.U1IP = priority_lvl;
    IEC1bits.U1RXIE = 1;
}


/*
 * Interrupt de reception de l'UART
 * Verifier qu'on a l'acces sur le tableau et sa taille
 *
 * Message: 0 ou 1, si personne ou non devant la cam
 */
void    __ISR(32, IPL5) uart_interrupt()
{
    while (U1STAbits.URXDA && marvin.counter2 < SIZE_MESS)
        marvin.receive[marvin.counter2++] = U1RXREG;
    if (marvin.counter2 == SIZE_MESS)
        marvin.counter2 = 0;
    if (marvin_is_a_person())
        marvin_eye_blink();
    marvin_reset_buffer();
    IFS1bits.U1RXIF = 0;
}

/*
 * Empty le premier ordre
 */
/*
void    marvin_empty_receive(u8 *receive)
{
    u8 *d;

    d = receive;
    while (*receive != '\n' && *(receive + 1) && *(receive + 1) != '\r')
        *receive++ = 0;
    *receive++ == 0; // kill le \n
    *receive++ = 0; //kill le \r
    while (*receive)
       *d++ = *receive++;
}

*/
/*
 *  Fonction qui remplit les donnees recus dans un tableau
 *  Param1: Tableau a remplir
 *  Param2: Size du Tableau a remplir
 *  Param3: Adresse du receive register (UxRXREG)
 *  Param4: Adresse du Status/Control register (UxSTA)
 *  Param5: Adresse Receive buffer(read only) (UxSTA.bits.URXDA, 0 = buffer empty / 1 = buffer has data)
 *
 *  Voir pendant codage de l'algo si utile ou si on utilise que l'interrupt
 */
char    *marvin_receive_message(u8 *receive, u16 *uart_nbr)
{
    while (U1STAbits.URXDA )
    {
        receive[*uart_nbr] == U1RXREG;
        ++*uart_nbr;
    }
    if (SIZE_MESS == *uart_nbr)
        *uart_nbr = 0;

    return (receive);
}