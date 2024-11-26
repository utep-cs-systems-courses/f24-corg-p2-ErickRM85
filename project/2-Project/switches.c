#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"

char switch_state_down, switch_state_changed; /* effectively boolean */

// Base frequency for the buzzer

#define BASE_FREQUENCY 1000  // 1kHz as the base frequency

// Offset for each switch press (adjust these values as needed)

#define SW1_OFFSET 500   // Increase frequency by 500 Hz
#define SW2_OFFSET -500  // Decrease frequency by 500 Hz
#define SW3_OFFSET 1000  // Increase frequency by 1000 Hz
#define SW4_OFFSET -1000 // Decrease frequency by 1000 Hz

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  // Update switch interrupt to detect changes from current buttons

  P2IES |= (p2val & SWITCHES);  // if switch is up, sense down
  P2IES &= (p2val | ~SWITCHES); // if switch is down, sense up
  return p2val;
}

void switch_init()/* setup switches */
{
  // Enable pull-up resistors for switches on P2.0, P2.1, P2.2, P2.3
  P2REN |= SWITCHES;/* enables resistors for switches on P2.0, P2.1, P2.2, P2.*/		     P2REN |= SWITCHES;/* enables resistors for switches */
  P2IE |= SWITCHES;/* enable interrupts from switches */
  P2OUT |= SWITCHES;/* pull-ups for switches */
  P2DIR &= ~SWITCHES;/* set switches' bits for input */

  switch_update_interrupt_sense();  // Set interrupt sense for P2 switches

  led_update();  // Initial LED update
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();

  switch_state_down = 0;   // No switch is pressed initially
  switch_state_changed = 1; // Indicate a switch has been pressed

  // Detect which switch is pressed based on the input value
  if ((p2val & SW1) == 0) {
    switch_state_down = SW1;  // SW1 is pressed (P2.0)
  } else if ((p2val & SW2) == 0) {
    switch_state_down = SW2;  // SW2 is pressed (P2.1)
  } else if ((p2val & SW3) == 0) {
    switch_state_down = SW3;  // SW3 is pressed (P2.2)
  } else if ((p2val & SW4) == 0) {
    switch_state_down = SW4;  // SW4 is pressed (P2.3)
  }
  
  led_update();  // Update LEDs based on the switch state

  // Modify buzzer frequency based on switch pressed
  switch (switch_state_down) {
  case SW1:
    buzzer_set_period(BASE_FREQUENCY + SW1_OFFSET); // Increase frequency by 500 Hz
    break;
  case SW2:
    buzzer_set_period(BASE_FREQUENCY + SW2_OFFSET); // Decrease frequency by 500 Hz
    break;
  case SW3:
    buzzer_set_period(BASE_FREQUENCY + SW3_OFFSET); // Increase frequency by 1000 Hz
    break;
  case SW4:
    buzzer_set_period(BASE_FREQUENCY + SW4_OFFSET); // Decrease frequency by 1000 Hz
    break;
  default:
    buzzer_set_period(BASE_FREQUENCY); // Default to base frequency
    break;
  }
}
