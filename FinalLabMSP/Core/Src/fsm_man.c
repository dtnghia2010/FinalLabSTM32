/*
 * fsm_man.c
 *
 *  Created on: May 28, 2024
 *      Author: DELL
 */
#include "fsm_man.h"
#include "software_timer.h"
#include "control_led.h"
#include "button.h"
int counter = 0;
int tenSec = 0;
int tenSecFlag = 0;
void wrapAroundCounter(){
	if (counter > 9) counter=0;
	if (counter < 0) counter=9;
}

void fsm_man_run() {
    if(timer0_flag == 1) {
        setTimer0(100); // Reset the timer
        HAL_GPIO_TogglePin(LED_RED_Port, LED_RED_Pin);
        if(tenSecFlag == 1) { // If the 10-second flag is set
            counter--; // Decrease the counter
            tenSecFlag = 0; // Reset the flag
        }

        display7SEG(counter); // Display the current counter value
        tenSec++; // Increment the 10-second counter

        if(tenSec >= 10) { // If 10 timer ticks have passed
            tenSec = 0; // Reset the 10-second counter
            tenSecFlag = 1; // Set the flag to decrease the counter
        }

        if(counter < 0) { // Ensure the counter wraps around if it goes below 0
            counter = 9;
        }

    }
	  if(is_button_pressed(0) == 1 || is_long_button_flag(0) == 1) {
		  counter = 0;
	  }
	  if(is_button_pressed(1) == 1 || is_long_button_flag(1) == 1) {
		  wrapAroundCounter(++counter);
	  }
	  if(is_button_pressed(2) == 1 || is_long_button_flag(2) == 1) {
		  wrapAroundCounter(--counter);
	  }

}
