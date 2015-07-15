/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2015 Naman Govil, <namangov@gmail.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <console/console.h>
#include <console/uart.h>

#define UART0_IO_ADDRESS      (0x90000000)

uintptr_t uart_platform_base(int idx)
{
	return UART0_IO_ADDRESS;
}
