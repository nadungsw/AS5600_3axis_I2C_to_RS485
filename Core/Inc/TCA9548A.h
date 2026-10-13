/*
 * TCA9548A.h
 *
 *  Created on: Jun 3, 2026
 *      Author: Nguyen Anh Dung
 */

#ifndef __TCA9548A_H
#define __TCA9548A_H

#include "main.h"

// Định nghĩa địa chỉ (Đã dịch trái 1 bit cho chuẩn HAL của STM32)
#define TCA9548A_ADDRESS     0xE0
#define AS5600_ADDRESS       0x6C
#define AS5600_REG_RAW_ANGLE 0x0C

// Khởi tạo thư viện với bộ I2C tương ứng
void TCA9548A_Init(I2C_HandleTypeDef *hi2c);

// Chọn kênh kích hoạt trên TCA9548A (0 đến 7)
HAL_StatusTypeDef TCA9548A_SelectChannel(uint8_t channel);

// Đọc giá trị góc thô từ AS5600
uint16_t AS5600_ReadRawAngle(void);

// Quét toàn bộ 3 trục và lưu vào mảng dữ liệu
void Update_All_Angles(uint16_t *angles);

#endif /* __TCA9548A_H */
