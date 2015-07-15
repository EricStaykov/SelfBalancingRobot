#define CPU_SPEED								20000000UL

#define I2C_START								0x08
#define I2C_REP_START							0x10
#define I2C_MT_SLA_ACK							0x18
#define I2C_MT_DATA_ACK							0x28
#define I2C_MR_SLA_ACK							0x40
#define I2C_MR_DATA_ACK							0x50
#define I2C_MR_DATA_NACK						0x58

#define TWI_FREQ								400000UL
#define TWI_FREQ_PRESCALER						(uint8_t)(((CPU_SPEED / TWI_FREQ) - 16) / 2)
#define TWI_DDR									DDRC
#define TWI_PIN_IN								PINC
#define TWI_PORT_OUT							PORTC
#define TWI_PINS								0x30

void i2c_init(void);
int8_t _i2c_start(uint8_t addr, uint8_t rep);
int8_t i2c_start(uint8_t addr);
int8_t i2c_rep_start(uint8_t addr);
void i2c_stop(void);
int8_t i2c_write(uint8_t data);
int8_t i2c_read(uint8_t *data, uint8_t ack);
int8_t i2c_read_ack(uint8_t *data);
int8_t i2c_read_nack(uint8_t *data);