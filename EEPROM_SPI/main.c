#include <msp430.h> 
#include <stdint.h>
#include <string.h>
#include "spieeprom.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    P1DIR |= BIT6;
    P1OUT &= ~BIT6;

    uint16_t addr = 0x00;
    uint8_t data[16] = {0,};
    char rawdata[32] = "Who is single dog?";

    eeprom_init();

    eeprom_enable_write();
    eeprom_write_bytes(addr, rawdata, strlen(rawdata));

    eeprom_read_bytes(addr, data, 16);

    eeprom_disable_write();
}
