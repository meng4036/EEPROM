#include <msp430.h> 
#include <stdint.h>
#include <stdio.h>
#include "spieeprom.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    P1DIR |= BIT6;
    P1OUT &= ~BIT6;
    uint8_t value = 0;


    eeprom_init();
    eeprom_enable_write();
	eeprom_write_byte(0x0001, 'a');

	value = eeprom_read_byte(0x0001);
	if (value == 'a') {
		P1OUT |= BIT6;
	}
	value = eeprom_read_byte(0x0002);

    eeprom_enable_write();
    eeprom_write_byte(0x0009, value);

    eeprom_disable_write();
}
