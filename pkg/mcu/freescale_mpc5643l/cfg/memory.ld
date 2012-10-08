/* Memory map for Freescale MPC5643L */

MEMORY
{
	boot:	org = 0x00000000, len = 0x00020000
	iflash:	org = 0x00020000, len = 0x00020000

    /* Calibrations flash area */
    calibrations_ram:	org = 0x00040000, len = 0x00020000
    calibrations_flash:	org = 0x00060000, len = 0x00020000

    /* Use only 64 kB of RAM as in DPM mode.
    /* This value can be equal to 128 in case of LSM...
     * keep in mind in case of big application
     */
	isram:	org = 0x40000000, len = 0x00010000
}

isram_base = ADDR(isram);
isram_len = SIZEOF(isram);

