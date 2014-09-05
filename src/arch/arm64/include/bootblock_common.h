#ifdef CONFIG_BOOTBLOCK_CPU_INIT
#include CONFIG_BOOTBLOCK_CPU_INIT
#endif

#ifdef CONFIG_BOOTBLOCK_MAINBOARD_INIT
#include CONFIG_BOOTBLOCK_MAINBOARD_INIT
#else
static inline void bootblock_mainboard_init(void)
{
	/*
	 * Do nothing.
	 * Start adding activities as and when required
	 */
}
#endif
