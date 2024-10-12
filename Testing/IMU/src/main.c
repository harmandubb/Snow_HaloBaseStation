/*
 * Copyright (c) 2018 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/i2c.h>
#include <stdio.h>
#include <zephyr/sys/util.h>

#define I2C0_NODE DT_NODELABEL(mysensor)
// static inline float out_ev(struct sensor_value *val)
// {
// 	return (val->val1 + (float)val->val2 / 1000000);
// }

// static int print_samples;
// static int lsm6dsl_trig_cnt;

// static struct sensor_value accel_x_out, accel_y_out, accel_z_out;
// static struct sensor_value gyro_x_out, gyro_y_out, gyro_z_out;
// #if defined(CONFIG_LSM6DSL_EXT0_LIS2MDL)
// static struct sensor_value magn_x_out, magn_y_out, magn_z_out;
// #endif
// #if defined(CONFIG_LSM6DSL_EXT0_LPS22HB)
// static struct sensor_value press_out, temp_out;
// #endif

// #ifdef CONFIG_LSM6DSL_TRIGGER
// static void lsm6dsl_trigger_handler(const struct device *dev,
// 				    const struct sensor_trigger *trig)
// {
// 	static struct sensor_value accel_x, accel_y, accel_z;
// 	static struct sensor_value gyro_x, gyro_y, gyro_z;
// #if defined(CONFIG_LSM6DSL_EXT0_LIS2MDL)
// 	static struct sensor_value magn_x, magn_y, magn_z;
// #endif
// #if defined(CONFIG_LSM6DSL_EXT0_LPS22HB)
// 	static struct sensor_value press, temp;
// #endif
// 	lsm6dsl_trig_cnt++;

// 	sensor_sample_fetch_chan(dev, SENSOR_CHAN_ACCEL_XYZ);
// 	sensor_channel_get(dev, SENSOR_CHAN_ACCEL_X, &accel_x);
// 	sensor_channel_get(dev, SENSOR_CHAN_ACCEL_Y, &accel_y);
// 	sensor_channel_get(dev, SENSOR_CHAN_ACCEL_Z, &accel_z);

// 	/* lsm6dsl gyro */
// 	sensor_sample_fetch_chan(dev, SENSOR_CHAN_GYRO_XYZ);
// 	sensor_channel_get(dev, SENSOR_CHAN_GYRO_X, &gyro_x);
// 	sensor_channel_get(dev, SENSOR_CHAN_GYRO_Y, &gyro_y);
// 	sensor_channel_get(dev, SENSOR_CHAN_GYRO_Z, &gyro_z);

// #if defined(CONFIG_LSM6DSL_EXT0_LIS2MDL)
// 	/* lsm6dsl external magn */
// 	sensor_sample_fetch_chan(dev, SENSOR_CHAN_MAGN_XYZ);
// 	sensor_channel_get(dev, SENSOR_CHAN_MAGN_X, &magn_x);
// 	sensor_channel_get(dev, SENSOR_CHAN_MAGN_Y, &magn_y);
// 	sensor_channel_get(dev, SENSOR_CHAN_MAGN_Z, &magn_z);
// #endif

// #if defined(CONFIG_LSM6DSL_EXT0_LPS22HB)
// 	/* lsm6dsl external press/temp */
// 	sensor_sample_fetch_chan(dev, SENSOR_CHAN_PRESS);
// 	sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);

// 	sensor_sample_fetch_chan(dev, SENSOR_CHAN_AMBIENT_TEMP);
// 	sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
// #endif

// 	if (print_samples) {
// 		print_samples = 0;

// 		accel_x_out = accel_x;
// 		accel_y_out = accel_y;
// 		accel_z_out = accel_z;

// 		gyro_x_out = gyro_x;
// 		gyro_y_out = gyro_y;
// 		gyro_z_out = gyro_z;

// #if defined(CONFIG_LSM6DSL_EXT0_LIS2MDL)
// 		magn_x_out = magn_x;
// 		magn_y_out = magn_y;
// 		magn_z_out = magn_z;
// #endif

// #if defined(CONFIG_LSM6DSL_EXT0_LPS22HB)
// 		press_out = press;
// 		temp_out = temp;
// #endif
// 	}

// }
// #endif

int main(void)
{
	// int cnt = 0;
	// char out_str[64];
	// struct sensor_value odr_attr;
	// const struct device *const lsm6dsl_dev = DEVICE_DT_GET_ONE(st_lsm6dsl);

	// if (!device_is_ready(lsm6dsl_dev)) {
	// 	printk("sensor: device not ready.\n");
	// 	return 0;
	// }

	uint8_t reg_addr = 0x00;
	uint8_t who_am_i; 
	// Step 1: Get I2C device binding (for I2C0)
    static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C0_NODE);  // Using DEVICE_DT_GET for I2C0 bus
    if (!device_is_ready(dev_i2c.bus)) {
		printk("I2C bus %s is not ready!\n\r",dev_i2c.bus->name);
		return -1;
	} else {
		printk("I2C bus FOUND\n");
		printk("Address of I2C device: 0x%x\n", dev_i2c.addr);
		printk("Name of I2C: %s", dev_i2c.bus->name);
	}



	// Step 2: Configure I2C bus speed to standard mode (100 kHz)
    if (i2c_configure(dev_i2c.bus, I2C_SPEED_SET(I2C_SPEED_STANDARD)) < 0) {
        printk("I2C: Failed to configure.\n");
        return -1;
    } else {
		printk("I2C: Speed Config Done\n");
	}

	// Step 3: Read WHO_AM_I register from the sensor
    if (i2c_write_read(dev_i2c.bus, dev_i2c.addr, &reg_addr, sizeof(reg_addr), &who_am_i, sizeof(who_am_i)) < 0) {
        printk("I2C: Failed to read WHO_AM_I register.\n");
        return -1;
    }

	 // Step 4: Print the read value
    printk("WHO_AM_I register: 0x%x\n", who_am_i);  // Expected output for LSM6DS3TR-C: 0x6a



// 	/* set accel/gyro sampling frequency to 104 Hz */
// 	odr_attr.val1 = 104;
// 	odr_attr.val2 = 0;

// 	if (sensor_attr_set(lsm6dsl_dev, SENSOR_CHAN_ACCEL_XYZ,
// 			    SENSOR_ATTR_SAMPLING_FREQUENCY, &odr_attr) < 0) {
// 		printk("Cannot set sampling frequency for accelerometer.\n");
// 		return 0;
// 	}

// 	if (sensor_attr_set(lsm6dsl_dev, SENSOR_CHAN_GYRO_XYZ,
// 			    SENSOR_ATTR_SAMPLING_FREQUENCY, &odr_attr) < 0) {
// 		printk("Cannot set sampling frequency for gyro.\n");
// 		return 0;
// 	}

// #ifdef CONFIG_LSM6DSL_TRIGGER
// 	struct sensor_trigger trig;

// 	trig.type = SENSOR_TRIG_DATA_READY;
// 	trig.chan = SENSOR_CHAN_ACCEL_XYZ;

// 	if (sensor_trigger_set(lsm6dsl_dev, &trig, lsm6dsl_trigger_handler) != 0) {
// 		printk("Could not set sensor type and channel\n");
// 		return 0;
// 	}
// #endif

// 	if (sensor_sample_fetch(lsm6dsl_dev) < 0) {
// 		printk("Sensor sample update error\n");
// 		return 0;
// 	}

// 	while (1) {
// 		/* Erase previous */
// 		printk("\0033\014");
// 		printf("LSM6DSL sensor samples:\n\n");

// 		/* lsm6dsl accel */
// 		sprintf(out_str, "accel x:%f ms/2 y:%f ms/2 z:%f ms/2",
// 							  out_ev(&accel_x_out),
// 							  out_ev(&accel_y_out),
// 							  out_ev(&accel_z_out));
// 		printk("%s\n", out_str);

// 		/* lsm6dsl gyro */
// 		sprintf(out_str, "gyro x:%f dps y:%f dps z:%f dps",
// 							   out_ev(&gyro_x_out),
// 							   out_ev(&gyro_y_out),
// 							   out_ev(&gyro_z_out));
// 		printk("%s\n", out_str);

// #if defined(CONFIG_LSM6DSL_EXT0_LIS2MDL)
// 		/* lsm6dsl external magn */
// 		sprintf(out_str, "magn x:%f gauss y:%f gauss z:%f gauss",
// 							   out_ev(&magn_x_out),
// 							   out_ev(&magn_y_out),
// 							   out_ev(&magn_z_out));
// 		printk("%s\n", out_str);
// #endif

// #if defined(CONFIG_LSM6DSL_EXT0_LPS22HB)
// 		/* lsm6dsl external press/temp */
// 		sprintf(out_str, "press: %f kPa - temp: %f deg",
// 			out_ev(&press_out), out_ev(&temp_out));
// 		printk("%s\n", out_str);
// #endif

// 		printk("loop:%d trig_cnt:%d\n\n", ++cnt, lsm6dsl_trig_cnt);

// 		print_samples = 1;
// 		k_sleep(K_MSEC(2000));
// 	}
}
