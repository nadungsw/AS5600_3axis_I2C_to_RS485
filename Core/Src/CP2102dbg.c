/*
 * CP2102dbg.c
 *
 *  Created on: Jun 5, 2026
 *      Author: Nguyen Anh Dung
 */

#include "CP2102dbg.h"

#if DEBUG_ENABLE
	void CP2102_Debug_Init(void) {
		char msg[] = "\r\n===== STM32F103 SENSOR DEBUG SYSTEM OK =====\r\n";
		HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	}

	void CP2102_Send_Angles(uint16_t *robot_angles) {
		char tx_buffer[128];

		// Quy đổi từ giá trị góc (0 - 4095) sang góc (0.0 - 360.0)
		float angle1 = (robot_angles[0] * 360.0f) / 4095.0f;
		float angle2 = (robot_angles[1] * 360.0f) / 4095.0f;
		float angle3 = (robot_angles[2] * 360.0f) / 4095.0f;

		snprintf(tx_buffer, sizeof(tx_buffer),
				 "[DBG_RAW] A1:%4d, A2:%4d, A3:%4d | [DEGREE] J1:%.1f deg, J2:%.1f deg, J3:%.1f deg\r\n",
				 robot_angles[0], robot_angles[1], robot_angles[2],
				 angle1, angle2, angle3);

		HAL_UART_Transmit(&huart1, (uint8_t*)tx_buffer, strlen(tx_buffer), HAL_MAX_DELAY);
	}
#endif
