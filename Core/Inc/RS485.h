/*
 * RS485.h
 *
 *  Created on: Jun 3, 2026
 *      Author: Nguyen Anh Dung
 */

#ifndef __RS485_H
#define __RS485_H

#include "main.h"

// Khởi tạo thư viện RS485 với các tham số từ phần cứng
void RS485_Init(UART_HandleTypeDef *huart, GPIO_TypeDef *port, uint16_t pin);

// Hàm lắng nghe lệnh từ Master
HAL_StatusTypeDef RS485_Receive_Command(uint8_t *cmd, uint32_t timeout);

// Hàm đóng gói và gửi mảng dữ liệu góc qua RS485
void RS485_Send_Angles(uint16_t *angles);

#endif /* __RS485_H */
