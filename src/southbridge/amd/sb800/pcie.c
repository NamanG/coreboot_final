/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2010 Advanced Micro Devices, Inc.
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

#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <device/pci_ids.h>
#include <device/pci_ops.h>
#include "sb800.h"

static void pcie_init(struct device *dev)
{
	/* Enable pci error detecting */
	u32 dword;

	printk(BIOS_INFO, "pcie_init in rs780_ht.c\n");

	/* System error enable */
	dword = pci_read_config32(dev, 0x04);
	dword |= (1 << 8);	/* System error enable */
	dword |= (1 << 30);	/* Clear possible errors */
	pci_write_config32(dev, 0x04, dword);
}

static struct pci_operations lops_pci = {
	.set_subsystem = 0,
};

static struct device_operations pci_ops = {
	.read_resources = pci_bus_read_resources,
	.set_resources = pci_dev_set_resources,
	.enable_resources = pci_bus_enable_resources,
	.init = pcie_init,
	.scan_bus = pci_scan_bridge,
	.reset_bus = pci_bus_reset,
	.ops_pci = &lops_pci,
};

static const struct pci_driver pciea_driver __pci_driver = {
	.ops = &pci_ops,
	.vendor = PCI_VENDOR_ID_ATI,
	.device = PCI_DEVICE_ID_ATI_SB800_PCIEA,
};

static const struct pci_driver pcieb_driver __pci_driver = {
	.ops = &pci_ops,
	.vendor = PCI_VENDOR_ID_ATI,
	.device = PCI_DEVICE_ID_ATI_SB800_PCIEB,
};
static const struct pci_driver pciec_driver __pci_driver = {
	.ops = &pci_ops,
	.vendor = PCI_VENDOR_ID_ATI,
	.device = PCI_DEVICE_ID_ATI_SB800_PCIEC,
};
static const struct pci_driver pcied_driver __pci_driver = {
	.ops = &pci_ops,
	.vendor = PCI_VENDOR_ID_ATI,
	.device = PCI_DEVICE_ID_ATI_SB800_PCIED,
};
