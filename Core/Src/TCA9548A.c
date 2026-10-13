/*
 * TCA9548A.c
 *
 *  Created on: Jun 3, 2026
 *      Author: Nguyen Anh Dung
 */

#include "TCA9548A.h"

static I2C_HandleTypeDef *tca_hi2c;

void TCA9548A_Init(I2C_HandleTypeDef *hi2c) {
    tca_hi2c = hi2c;
}

HAL_StatusTypeDef TCA9548A_SelectChannel(uint8_t channel) {
    if (channel > 7) return HAL_ERROR;

    uint8_t control_register = 1 << channel;
    return HAL_I2C_Master_Transmit(tca_hi2c, TCA9548A_ADDRESS, &control_register, 1, HAL_MAX_DELAY);
}

uint16_t AS5600_ReadRawAngle(void) {
    uint8_t reg = AS5600_REG_RAW_ANGLE;
    uint8_t data[2] = {0};

    // Chỉ định thanh ghi cần đọc
    if (HAL_I2C_Master_Transmit(tca_hi2c, AS5600_ADDRESS, &reg, 1, HAL_MAX_DELAY) != HAL_OK) {
        return 0; // Lỗi truyền
    }

    // Yêu cầu nhận về 2 byte
    if (HAL_I2C_Master_Receive(tca_hi2c, AS5600_ADDRESS, data, 2, HAL_MAX_DELAY) == HAL_OK) {
        return (uint16_t)((data[0] << 8) | data[1]);
    }

    return 0; // Lỗi nhận
}

void Update_All_Angles(uint16_t *angles) {
    // Đọc Trục 1 (Cổng 0)
    if (TCA9548A_SelectChannel(0) == HAL_OK) {
        angles[0] = AS5600_ReadRawAngle();
    }
    // Đọc Trục 2 (Cổng 1)
    if (TCA9548A_SelectChannel(1) == HAL_OK) {
        angles[1] = AS5600_ReadRawAngle();
    }
    // Đọc Trục 3 (Cổng 3)
    if (TCA9548A_SelectChannel(3) == HAL_OK) {
        angles[2] = AS5600_ReadRawAngle();
    }
}
