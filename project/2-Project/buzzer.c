#include <msp430.h>
#include "buzzer.h"
#include "libTimer.h"

void buzzer_init() {
  // Direct timer A output "TA0.1" to P2.6

  timerAUpmode();    // Used to drive the speaker
  P2SEL2 &= ~(BIT6 | BIT7);   // Clear P2SEL2.6 and P2SEL2.7
  P2SEL &= ~BIT7;           // Clear P2SEL.7
  P2SEL |= BIT6;            // Set P2SEL.6 for timer output
  P2DIR |= BIT6;            // Set P2.6 as output (for buzzer)
}

// Set the period for the buzzer (this controls the frequency)

void buzzer_set_period(short cycles) {
  CCR0 = cycles;          // Period of the buzzer
  CCR1 = cycles >> 1;     // Half cycle for the buzzer (duty cycle)

}

