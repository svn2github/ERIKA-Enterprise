/* Memory map for Freescale MPC5643L in Lock Step mode */

MEMORY
{
    /* First 16 KB for boot sector */
	boot:	org = 0x00000000, len = 0x00004000

    /* 512 KB of Flash memory available in single core configuration */
	iflash:	org = 0x00080000, len = 0x00080000

    /* Calibrations flash area */
    calibrations_ram:	org = 0x00040000, len = 0x00020000
    calibrations_flash:	org = 0x00060000, len = 0x00020000

    /* 128 KB of RAM for LSM */
	isram:	org = 0x40000000, len = 0x00020000
}

isram_base = ADDR(isram);
isram_len = SIZEOF(isram);

/* Variables used to manage calibrations */
cal_ram_size = SIZEOF(cal_ram);
cal_ram_base = ee_scal_ram;
cal_ram_dest_base = ee_scal_ram_dest;

