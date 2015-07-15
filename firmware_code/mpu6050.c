#include <avr/io.h>
#include "i2c.h"
#include "mpu6050.h"

uint8_t accelXH, accelXL, accelYH, accelYL, accelZH, accelZL, temperatureH, temperatureL, gyroXH, gyroXL, gyroYH, gyroYL, gyroZH, gyroZL;
int16_t accelX, accelY, accelZ, temperature, gyroX, gyroY, gyroZ;

void configure_mpu(void) {
	// get out of sleep mode
	i2c_start(MPU_6050_WRITE_ADDRESS);
	i2c_write(MPU_6050_REGISTER_PWR_MANAGEMENT);
	i2c_write(0);
	i2c_stop();
	// configure gyro range & sensitivity
	i2c_start(MPU_6050_WRITE_ADDRESS);
	i2c_write(MPU_6050_REGISTER_GYRO_CONFIG);
	i2c_write(0x10);
	i2c_stop();
	// configure accel range & sensitivity
	i2c_start(MPU_6050_WRITE_ADDRESS);
	i2c_write(MPU_6050_REGISTER_ACCEL_CONFIG);
	i2c_write(0x10);
	i2c_stop();
}

void collect_data_mpu(void) {
	i2c_start(MPU_6050_WRITE_ADDRESS);
	i2c_write(MPU_6050_REGISTER_ACCEL_XOUT_H);
	i2c_rep_start(MPU_6050_READ_ADDRESS);
	i2c_read_ack(&accelXH);
	i2c_read_ack(&accelXL);
	i2c_read_ack(&accelYH);
	i2c_read_ack(&accelYL);
	i2c_read_ack(&accelZH);
	i2c_read_ack(&accelZL);
	i2c_read_ack(&temperatureH);
	i2c_read_ack(&temperatureL);
	i2c_read_ack(&gyroXH);
	i2c_read_ack(&gyroXL);
	i2c_read_ack(&gyroYH);
	i2c_read_ack(&gyroYL);
	i2c_read_ack(&gyroZH);
	i2c_read_nack(&gyroZL);
	i2c_stop();
	accelX = (accelXH << 8) | accelXL;
	accelY = (accelYH << 8) | accelYL;
	accelZ = (accelZH << 8) | accelZL;
	temperature = (temperatureH << 8) | temperatureL;
	gyroX = (gyroXH << 8) | gyroXL;
	gyroY = (gyroYH << 8) | gyroYL;
	gyroZ = (gyroZH << 8) | gyroZL;
}