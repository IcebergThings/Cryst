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
// ■ RS232.cpp
//-----------------------------------------------------------------------------
//   i686设备驱动：RS232串口。
//=============================================================================

#include "RS232.h"

void Init_RS232(RS232_t* device, uint16_t port) {
	device->port = port;
	io_out8(port + 1, 0x00);    // Disable all interrupts
	io_out8(port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	io_out8(port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	io_out8(port + 1, 0x00);    //                  (hi byte)
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
