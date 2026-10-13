/*
 * RS485.c
 * Author: Nguyen Anh Dung
 */

#include "RS485.h"
#include "CRC16.h"

static UART_HandleTypeDef *rs485_huart;
static GPIO_TypeDef *rs485_port;
static uint16_t rs485_pin;

void RS485_Init(UART_HandleTypeDef *huart, GPIO_TypeDef *port, uint16_t pin) {
    rs485_huart = huart;
    rs485_port = port;
    rs485_pin = pin;

    // Đặt mặc định chân RE/DE ở chế độ NHẬN (LOW) ngay khi khởi tạo
    HAL_GPIO_WritePin(rs485_port, rs485_pin, GPIO_PIN_RESET);
}

HAL_StatusTypeDef RS485_Receive_Command(uint8_t *cmd, uint32_t timeout) {
    // CHỐNG KHÓA UART: Kiểm tra và xóa các cờ lỗi tràn bộ đệm hoặc khung truyền
    if (__HAL_UART_GET_FLAG(rs485_huart, UART_FLAG_ORE) != RESET) {
        __HAL_UART_CLEAR_OREFLAG(rs485_huart);
    }
    if (__HAL_UART_GET_FLAG(rs485_huart, UART_FLAG_FE) != RESET) {
        __HAL_UART_CLEAR_FEFLAG(rs485_huart);
    }

    // Chờ nhận 1 byte lệnh
    return HAL_UART_Receive(rs485_huart, cmd, 1, timeout);
}

void RS485_Send_Angles(uint16_t *angles) {
    uint8_t tx_buffer[10];

    // cấu trúc Header
    tx_buffer[0] = 0xAA;
    tx_buffer[1] = 0xBB;

    // Chặt đôi số 12-bit (uint16_t) của AS5600 thành 2 byte đơn
    tx_buffer[2] = (uint8_t)(angles[0] >> 8);   // Byte cao khớp 1
    tx_buffer[3] = (uint8_t)(angles[0] & 0xFF); // Byte thấp khớp 1
    tx_buffer[4] = (uint8_t)(angles[1] >> 8);   // Byte cao khớp 2
    tx_buffer[5] = (uint8_t)(angles[1] & 0xFF); // Byte thấp khớp 2
    tx_buffer[6] = (uint8_t)(angles[2] >> 8);   // Byte cao khớp 3
    tx_buffer[7] = (uint8_t)(angles[2] & 0xFF); // Byte thấp khớp 3

    // ==========================================================
    // TÍNH TOÁN VÀ GẮN CRC-16
    // ==========================================================
    // Tính mã CRC cho 8 byte dữ liệu đã đóng gói ở trên
    uint16_t crc_value = calculateCRC16(tx_buffer, 8);

    // Gắn 2 byte CRC vào vị trí số 8 và 9 của mảng
    tx_buffer[8] = (uint8_t)(crc_value & 0xFF);        // Byte thấp (CRC Low)
    tx_buffer[9] = (uint8_t)((crc_value >> 8) & 0xFF); // Byte cao (CRC High)

    // ==========================================================
    // TRUYỀN DỮ LIỆU QUA RS485
    // ==========================================================
    // Kéo chân RE/DE lên mức CAO để chuyển MAX485 sang chế độ TRUYỀN
    HAL_GPIO_WritePin(rs485_port, rs485_pin, GPIO_PIN_SET);

    // Đẩy toàn bộ gói 10 byte đi
    HAL_UART_Transmit(rs485_huart, tx_buffer, 10, 100);

    // Đợi phần cứng đẩy nốt Stop bit của byte cuối cùng ra khỏi dây
    while (__HAL_UART_GET_FLAG(rs485_huart, UART_FLAG_TC) == RESET);

    // Trả chân RE/DE về mức THẤP để chuyển sang chế độ NHẬN, nhường đường bus
    HAL_GPIO_WritePin(rs485_port, rs485_pin, GPIO_PIN_RESET);
}
