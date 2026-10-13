/*
 * CP2102dbg.h
 *
 *  Created on: Jun 5, 2026
 *      Author: Nguyen Anh Dung
 */


#ifndef INC_CP2102DBG_H_
#define INC_CP2102DBG_H_

#define DEBUG_ENABLE 0

#if DEBUG_ENABLE
	#include "main.h"
	#include <stdio.h>
	#include <string.h>

	// Khai báo bộ UART dùng để Debug
	extern UART_HandleTypeDef huart1;

	/**
	 * @brief  Khởi tạo cổng Debug (Nếu cần thiết lập biến hoặc xóa đệm)
	 */
	void CP2102_Debug_Init(void);

	/**
	 * @brief  Hàm gửi giá trị thô của 3 góc cảm biến lên máy tính qua cổng USART1
	 * @param  robot_angles: Mảng chứa 3 giá trị nguyên uint16_t (0 đến 4095)
	 */
	void CP2102_Send_Angles(uint16_t *robot_angles);
#endif

#endif /* INC_CP2102DBG_H_ */
