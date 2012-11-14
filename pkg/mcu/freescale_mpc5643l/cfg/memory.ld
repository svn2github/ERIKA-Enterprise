/* Memory map for Freescale MPC5643L in DPM mode */

MEMORY
{
    /* First 16 KB for boot sector */
	boot:	org = 0x00000000, len = 0x00004000

    /* 512 KB of Flash memory available in single core configuration */
	iflash:	org = 0x00080000, len = 0x00080000

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

/* Variables used to manage calibrations */
calib_ram_size = SIZEOF(calib_ram);
calib_ram_base = ee_scalib_ram;
calib_ram_dest_base = ee_scalib_ram_dest;

