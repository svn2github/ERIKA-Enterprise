/* Memory map for Freescale MPC5674 */

MEMORY
{
	boot:	org = 0x00000000, len = 0x00020000
	iflash:	org = 0x00020000, len = 0x001c0000

    /* Dummy memory areas. Used only bu MPC5643L with Codewarrior */
    calibrations_ram:	org = 0x00040000, len = 0x1
    calibrations_flash:	org = 0x00060000, len = 0x1

	isram:	org = 0x40000000, len = 0x00040000
}

isram_base = ADDR(isram);
isram_len = SIZEOF(isram);

