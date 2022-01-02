#include "i2c_m.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "i2c/i2c.h"

bool trdb_d5m_write(i2c_dev *i2c, uint8_t register_offset, uint16_t data) {
    uint8_t byte_data[2] = {(data >> 8) & 0xff, data & 0xff};

    int success = i2c_write_array(i2c, TRDB_D5M_I2C_ADDRESS, register_offset, byte_data, sizeof(byte_data));

    if (success != I2C_SUCCESS) {
        return false;
    } else {
        return true;
    }
}

bool trdb_d5m_read(i2c_dev *i2c, uint8_t register_offset, uint16_t *data) {
    uint8_t byte_data[2] = {0, 0};

    int success = i2c_read_array(i2c, TRDB_D5M_I2C_ADDRESS, register_offset, byte_data, sizeof(byte_data));

    if (success != I2C_SUCCESS) {
        return false;
    } else {
        *data = ((uint16_t) byte_data[0] << 8) + byte_data[1];
        return true;
    }
}

int configure_camera(void) {
    i2c_dev i2c = i2c_inst((void *) TRDB_D5M_0_I2C_0_BASE);
    i2c_init(&i2c, I2C_FREQ);

    bool success = true;
    uint16_t writedata = 0;

    //write writedata in registers
    /*
    success &= trdb_d5m_write(&i2c, 0x03, 1919);
    success &= trdb_d5m_write(&i2c, 0x04, 2559);
    success &= trdb_d5m_write(&i2c, 0x22, 51);
    success &= trdb_d5m_write(&i2c, 0x23, 51);
    success &= trdb_d5m_write(&i2c, 0x00A, 1 << 15);
    success &= trdb_d5m_write(&i2c, 0x005, 906);
    */

    // Make correct values available at rising edge of PIXCLK
	writedata = 1 << 15;
	success &= trdb_d5m_write(&i2c, 0x00A, writedata);
	// Set column-number
	writedata = 639u;
	success &= trdb_d5m_write(&i2c, 0x004, writedata);
	// Set row-number
	writedata = 479u;
	success &= trdb_d5m_write(&i2c, 0x003, writedata);
	// Disable binning and skipping
	writedata = 0;
	success &= trdb_d5m_write(&i2c, 0x022, writedata);
	success &= trdb_d5m_write(&i2c, 0x023, writedata);

	success &= trdb_d5m_write(&i2c, 0x005, 0);

    success &= trdb_d5m_write(&i2c, 0x0A0, 0);
    success &= trdb_d5m_write(&i2c, 0x0A1, 0); // Green
    success &= trdb_d5m_write(&i2c, 0x0A2, 0); // Red
    success &= trdb_d5m_write(&i2c, 0x0A3, 0); // Blue
    success &= trdb_d5m_write(&i2c, 0x0A4, 0); // width

    /* read from registers, put data in readdata */
    uint16_t readdata = 0;
    success &= trdb_d5m_read(&i2c, 0x03, &readdata);
    success &= trdb_d5m_read(&i2c, 0x04, &readdata);
    success &= trdb_d5m_read(&i2c, 0x22, &readdata);
    success &= trdb_d5m_read(&i2c, 0x23, &readdata);
    success &= trdb_d5m_read(&i2c, 0x00A, &readdata);
    success &= trdb_d5m_read(&i2c, 0x005, &readdata);
    success &= trdb_d5m_read(&i2c, 0x0A0, &readdata);
    success &= trdb_d5m_read(&i2c, 0x0A1, &readdata);
    success &= trdb_d5m_read(&i2c, 0x0A2, &readdata);
    success &= trdb_d5m_read(&i2c, 0x0A3, &readdata);
    success &= trdb_d5m_read(&i2c, 0x0A4, &readdata);

    if (success) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}