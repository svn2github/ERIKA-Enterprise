/* Memory map for Freescale MPC5643L CPU 1 in multicore setup */

MEMORY
{
	boot:	org = 0x00000000, len = 0x00020000
	iflash:	org = 0x00020000, len = 0x001c0000
/* Use only 256 kB of RAM, as per MMU setting from the BAM */
	isram:	org = 0x50000000, len = 0x0000FFFF
}

isram_base = ADDR(isram);
isram_len = SIZEOF(isram);
