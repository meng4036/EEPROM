/*
 * spieeprom.c
 *
 *  Created on: 2018��1��13��
 *      Author: meng4
 */

#include <msp430.h>
#include <stdint.h>
#include "spieeprom.h"

void spi_master_init() {
    P1DIR |= BIT5;
    P1OUT |= BIT5;

    P1SEL = BIT1 + BIT2 + BIT4;
    P1SEL2 = BIT1 + BIT2 + BIT4;

	UCA0CTL0 |= UCSWRST;
    UCA0CTL0 |= UCCKPH + UCMSB + UCMODE_0 + UCMST + UCSYNC;
    UCA0CTL1 = UCSSEL_1;

    UCA0BR0 |= 0x02;
    UCA0BR1 = 0;
    UCA0MCTL = 0;

    UCA0CTL1 &= ~UCSWRST;
    IE2 |= UCA0RXIE + UCA0TXIE;
}

uint8_t spi_write_byte(uint8_t byte) {
	UCA0TXBUF = byte;
	while (UCA0STAT & UCBUSY);
	return UCA0RXBUF;
}

void spi_enable_slave() {
	P1OUT &= ~BIT5;
}

void spi_disable_slave() {
	P1OUT |= BIT5;
}

void eeprom_init() {
	spi_master_init();
}

/**
 * 1, Pull low CS line to select device
 * 2, transmit op-code, followed by byte address to be read
 */
uint8_t eeprom_read_byte(uint16_t addr) {
	/* pull down CS line to select device */
	spi_enable_slave();

	/* transmit read command */
	spi_write_byte(OPCODE_READ);

	/* transmit address to be read*/
	spi_write_byte(addr >> 8);
	spi_write_byte(addr & 0xFF);

	/* read data from SPI receive buffer register */
	uint8_t c = spi_write_byte(0x00);

	/* disable slave */
	spi_disable_slave();

	return c;
}

void eeprom_read_bytes(uint16_t addr, uint8_t *buf, uint8_t size) {
	uint8_t i = 0;

	/* pull down CS line to select device */
	spi_enable_slave();

	/* transmit read command */
	spi_write_byte(OPCODE_READ);

	/* transmit address to be read*/
	spi_write_byte(addr >> 8);
	spi_write_byte(addr & 0xff);

	/* read data from SPI receive buffer register */
	while((i<size)) {
		*(buf + i) = spi_write_byte(OPCODE_READ);
		i++;
	}
	spi_disable_slave();
}

void eeprom_write_byte(uint16_t addr, uint8_t data) {
	/* pull down CS line to select device */
	spi_enable_slave();

	/* transmit write command */
	spi_write_byte(OPCODE_WRITE);

	/* transmit byte address to be write*/
	spi_write_byte(addr >> 8);
	spi_write_byte(addr & 0xff);

	/* transmit byte to be write */
	spi_write_byte(data);

	/* disable slave */
	spi_disable_slave();
}

void eeprom_write_bytes(uint16_t addr, const char *buf, uint8_t size) {
	/* pull down CS line to select device */
		spi_enable_slave();

		/* transmit write command */
		spi_write_byte(OPCODE_WRITE);

		/* transmit byte address to be write*/
		spi_write_byte(addr >> 8);
		spi_write_byte(addr & 0xff);

		/* transmit byte to be write */
		char *end = buf + size;
		while(buf != end) {
			spi_write_byte(*buf++);
		}

		/* disable slave */
		spi_disable_slave();
}

void eeprom_enable_write() {
	/* pull down CS line to select device */
	spi_enable_slave();

	/* transmit read command */
	spi_write_byte(OPCODE_WREN);

	/* disable slave */
	spi_disable_slave();
}

void eeprom_disable_write() {
	/* pull down CS line to select device */
	spi_enable_slave();

	/* transmit read command */
	spi_write_byte(OPCODE_WRDI);

	/* disable slave */
	spi_disable_slave();
}

uint8_t eeprom_read_status_register() {
	uint8_t rvalue;
	/* pull down CS line to select device */
	spi_enable_slave();

	/* transmit read command */
	spi_write_byte(OPCODE_RDSR);

	/*continue generic*/
	rvalue = spi_read_byte(0x00);

	/* disable slave */
	spi_disable_slave();

	return rvalue;
}

void eeprom_write_status_register(uint8_t value) {
	/* pull down CS line to select device */
	spi_enable_slave();

	/* transmit read command */
	spi_write_byte(OPCODE_WRSR);

	/* transmit byte to be write */
	spi_write_byte(value);

	/* disable slave */
	spi_disable_slave();
}
