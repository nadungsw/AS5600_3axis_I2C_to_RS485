/*
 * CRC16.h
 *
 *  Created on: Jul 11, 2026
 *      Author: Nguyen Anh Dung
 */

#ifndef CRC16_H
#define CRC16_H

#include <stdint.h>
#include <stddef.h>

uint16_t calculateCRC16(const uint8_t *data, size_t length);

#endif // CRC16_H
