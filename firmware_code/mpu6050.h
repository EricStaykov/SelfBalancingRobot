#define MPU_6050_WRITE_ADDRESS					0xD0
#define MPU_6050_READ_ADDRESS					0xD1
#define MPU_6050_REGISTER_PWR_MANAGEMENT		0x6B
#define MPU_6050_REGISTER_ACCEL_XOUT_H			0x3B
#define MPU_6050_REGISTER_GYRO_CONFIG			0x1B
#define MPU_6050_REGISTER_ACCEL_CONFIG			0x1C
#define GYROSCOPE_SENSITIVITY					32.8 // LSB/°/s
#define ACCELEROMETER_SENSITIVITY				4096.0 // LSB/g

extern uint8_t accelXH, accelXL, accelYH, accelYL, accelZH, accelZL, temperatureH, temperatureL, gyroXH, gyroXL, gyroYH, gyroYL, gyroZH, gyroZL;
extern int16_t accelX, accelY, accelZ, temperature, gyroX, gyroY, gyroZ;

void configure_mpu(void);
void collect_data_mpu(void);