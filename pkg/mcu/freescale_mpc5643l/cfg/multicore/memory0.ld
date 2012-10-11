/* Memory map for Freescale MPC5643L CPU 0 in multicore setup */

MEMORY
{
	boot:	org = 0x00000000, len = 0x00020000
	iflash:	org = 0x00020000, len = 0x0000FFFF
/* Use only 256 kB of RAM, as per MMU setting from the BAM */
	isram:	org = 0x40000000, len = 0x0000FFFF
/* Use only 4 bytes to place dpm/lsm mode bit */
	sscm_area: org= 0xC3F8802C, len= 0x4
}

isram_base = ADDR(isram);
isram_len = SIZEOF(isram);
sscm_base = ADDR(sscm_area);
