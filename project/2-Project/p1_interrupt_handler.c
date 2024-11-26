#include <msp430.h>
#include "switches.h"
#include "led.h"

/* Interrupt service routine for switches on Port 2 (P2.0, P2.1, P2.2, P2.3) */
void __interrupt_vec(PORT2_VECTOR) Port_2() {
  // Check for interrupts from switches on Port 2
  if (P2IFG & SWITCHES) {  // If any switch interrupt occurred
    P2IFG &= ~SWITCHES;   // Clear interrupt flags for P2.0, P2.1, P2.2, P2.3
    switch_interrupt_handler(); // Handle the switch interrupt
  }
}
