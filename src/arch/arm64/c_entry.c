/*
 * This file is part of the coreboot project.
 *
 * Copyright 2014 Google Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc.
 */

#include <arch/cache.h>
#include <arch/cpu.h>
#include <arch/mmu.h>
#include <arch/stages.h>
#include <arch/startup.h>
#include "cpu-internal.h"

void __attribute__((weak)) arm64_soc_init(void)
{
	/* Default weak implementation does nothing. */
}

unsigned int  __attribute__((weak)) smp_processor_id(void)
{
	/* Default weak implementation does nothing. */
	return 0;
}

static void seed_stack(void)
{
	char *stack_begin;
	uint64_t *slot;
	int i;
	int size;

	stack_begin = cpu_get_stack(smp_processor_id());
	stack_begin -= CONFIG_STACK_SIZE;
	slot = (void *)stack_begin;

	/* Pad out 256 bytes for current usage. */
	size = CONFIG_STACK_SIZE - 256;
	size /= sizeof(*slot);
	for (i = 0; i < size; i++)
		*slot++ = 0xdeadbeefdeadbeefULL;
}

static void arm64_init(void)
{
#if !defined(__PRE_RAM__)
	cpu_set_bsp();
#endif
	seed_stack();
	arm64_soc_init();
	main();
}

//static void secondary_cpu_start(void)
//{
//#ifndef __PRE_RAM__
//	mmu_enable();
//	exception_hwinit();

	/* This will never return. */
//	arch_secondary_cpu_init();
//#endif
//}

/*
 * This variable holds entry point for CPUs starting up. The first
 * element is the BSP path, and the second is the non-BSP path.
 */
#ifdef __PRE_RAM__
void (*c_entry[2])(void) = { &arm64_init, NULL};
#else
void (*c_entry[2])(void) = { &arm64_init, &arch_secondary_cpu_init};
#endif

void *prepare_secondary_cpu_startup(void)
{
	startup_save_cpu_data();

	return secondary_entry_point(&arm64_cpu_startup_resume);
}
