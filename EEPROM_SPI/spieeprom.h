/*
 * spieeprom.h
 *
 *  Created on: 2018��1��13��
 *      Author: meng4
 */

#ifndef SPIEEPROM_H_
#define SPIEEPROM_H_

#define OPCODE_WREN     0x06
#define OPCODE_WRDI     0x04
#define OPCODE_RDSR     0x05
#define OPCODE_WRSR     0x01
#define OPCODE_READ     0x03
#define OPCODE_WRITE    0x02

#define MISO_PIN        BIT1
#define MOSI_PIN        BIT2
#define CLK_PIN         BIT4
#define CS_PIN          BIT5

void spi_master_init();
uint8_t spi_write_byte(uint8_t data);
void spi_disable_slave();
void spi_enable_slave();

void eeprom_init();
uint8_t eeprom_read_byte(uint16_t addr);
void eeprom_write_byte(uint16_t addr, uint8_t data);
uint8_t eeprom_read_multibyte(uint16_t addr, uint8_t *buf, uint8_t size);
void eeprom_enable_write();
void eeprom_disable_write();
uint8_t eeprom_read_status_register();
void eeprom_write_status_register(uint8_t value);


//#########################################################

#define CYCLES_PER_US 1L // depends on the CPU speed
#define CYCLES_PER_MS (CYCLES_PER_US * 1000L)

#define DELAY_US(x) __delay_cycles((x * CYCLES_PER_US))
#define DELAY_MS(x) __delay_cycles((x * CYCLES_PER_MS))

#define delay_us(x) __delay_cycles((x * CYCLES_PER_US))
#define delay_ms(x) __delay_cycles((x * CYCLES_PER_MS))



#endif /* SPIEEPROM_H_ */
