// Copyright 2016 Iceberg OS
//
// Licensed under the Apache License, Versio_n 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITio_NS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissio_ns and
// limitatio_ns under the License.
//=============================================================================
// ■ RS232.c
//-----------------------------------------------------------------------------
//   i686设备驱动：RS232串口。
//=============================================================================

#include "RS232.h"

void Init_RS232(RS232_t* device, uint16_t port, int rate) {
	device->port = port;
	device->rate = rate;
	device->rate_divisor = 115200 / rate;

	io_out8(port + 1, 0x00);    // Disable all interrupts
	io_out8(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)

	// Set divisor
	io_out8(port + 0, (uint8_t) ((device->rate_divisor) & 0xFF));
	io_out8(port + 1, (uint8_t) ((device->rate_divisor >> 8) & 0xFF));

	io_out8(port + 3, 0x03);    // 8 bits, no parity, one stop bit
	io_out8(port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	io_out8(port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

int RS232_is_transmit_empty(RS232_t* device) {
   return io_in8(device->port + 5) & 0x20;
}

void RS232_write_serial(RS232_t* device, char a) {
   while (RS232_is_transmit_empty(device) == 0);

   io_out8(device->port,a);
}
