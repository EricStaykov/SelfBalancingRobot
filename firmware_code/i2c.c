#include <avr/io.h>
#include "i2c.h"

void i2c_init(void) {
	PRR &= ~(1 << PRTWI);
	TWSR &= ~((1 << TWPS1) | (1 << TWPS0));
	TWBR = TWI_FREQ_PRESCALER;
}

int8_t _i2c_start(uint8_t addr, uint8_t rep) {
	i2c_init();
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) != ((!rep) ? I2C_START : I2C_REP_START)) {
		return -1;
	}
	TWDR = addr;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	if (!(((TWSR & 0xF8) == I2C_MT_SLA_ACK) || ((TWSR & 0xF8) == I2C_MR_SLA_ACK))) {
		return -2;
	}
	return 0;
}

int8_t i2c_start(uint8_t addr) {
	return _i2c_start(addr, 0);
}

int8_t i2c_rep_start(uint8_t addr) {
	return _i2c_start(addr, 1);
}

void i2c_stop(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	while (TWCR & (1 << TWSTO));
	TWCR &= ~(TWEN);
	PRR |= (1 << PRTWI);
	TWI_DDR &= (~TWI_PINS);
	TWI_PORT_OUT |= TWI_PINS;
}

int8_t i2c_write(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	if ((TWSR & 0xF8) != I2C_MT_DATA_ACK) {
		return -1;
	}
	return 0;
}

int8_t i2c_read(uint8_t *data, uint8_t ack) {
	uint16_t i = 0;
	TWCR = (1 << TWINT) | (1 << TWEN) | (ack ? (1 << TWEA) : 0);
	while (!(TWCR & (1 << TWINT))) {
		if (i++ > 800) {
			return -1;
		}
	}
	if ((TWSR & 0xF8) != (ack ? I2C_MR_DATA_ACK : I2C_MR_DATA_NACK)) {
		return -1;
	}
	*data = TWDR;
	return 0;
}

int8_t i2c_read_ack(uint8_t *data) {
	return i2c_read(data, 1);
}

int8_t i2c_read_nack(uint8_t *data) {
	return i2c_read(data, 0);
}