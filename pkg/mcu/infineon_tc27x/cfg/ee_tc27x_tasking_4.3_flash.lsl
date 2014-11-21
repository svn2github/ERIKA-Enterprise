#define __REDEFINE_ON_CHIP_ITEMS 
#ifndef CPU_NUMID
#define __BMHD0_CONFIG __BMHD_GENERATE
#define __BMHD1_CONFIG __BMHD_GENERATE
#include "tc27xb_tc0.lsl"
processor mpe
{
    derivative = my_tc27x;
}
derivative my_tc27x extends tc27x
{
    memory dspr0 (tag="on-chip")
    {
        mau = 8;
        type = ram;
        size = 112k;
        map (dest=bus:tc0:fpi_bus, dest_offset=0xd0000000, size=112k, priority=2);
        map (dest=bus:sri, dest_offset=0x70000000, size=112k);
    }
    memory pspr0 (tag="on-chip")
    {
        mau = 8;
        type = ram;
        size = 24k;
        map (dest=bus:tc0:fpi_bus, dest_offset=0xc0000000, size=24k);
        map (dest=bus:sri, dest_offset=0x70100000, size=24k);
    }
    memory dspr1 (tag="on-chip")
    {
        mau = 8;
        type = ram;
        size = 120k;
        map (dest=bus:sri, dest_offset=0x60000000, size=120k);
    }
    memory pspr1 (tag="on-chip")
    {
        mau = 8;
        type = ram;
        size = 32k;
        map (dest=bus:sri, dest_offset=0x60100000, size=32k);
    }
    memory dspr2 (tag="on-chip")
    {
        mau = 8;
        type = ram;
        size = 120k;
        map (dest=bus:sri, dest_offset=0x50000000, size=120k);
    }
    memory pspr2 (tag="on-chip")
    {
        mau = 8;
        type = ram;
        size = 32k;
        map (dest=bus:sri, dest_offset=0x50100000, size=32k);
    }
    memory pflash0 (tag="on-chip")
    {
        mau = 8;
        type = rom;
        size = 2M;
        map cached(dest=bus:sri, dest_offset=0x80000000, size=2M);
        map not_cached(dest=bus:sri, dest_offset=0xa0000000, size=2M, reserved);
    }
    memory pflash1 (tag="on-chip")
    {
        mau = 8;
        type = rom;
        size = 2M;
        map cached(dest=bus:sri, dest_offset=0x80200000, size=2M);
        map not_cached(dest=bus:sri, dest_offset=0xa0200000, size=2M, reserved);
    }
    memory brom (tag="on-chip")
    {
        mau = 8;
        type = reserved rom;
        size = 32k;
        map cached(dest=bus:sri, dest_offset=0x8fff8000, size=32k);
        map not_cached(dest=bus:sri, dest_offset=0xafff8000, size=32k, reserved);
    }
    memory dflash0 (tag="on-chip")
    {
        mau = 8;
        type = reserved nvram;
        size = 384k+16k;
        map (dest=bus:sri, src_offset=0, dest_offset=0xaf000000, size=384k);
        map (dest=bus:sri, src_offset=384k, dest_offset=0xaf100000, size=16k);
    }
    memory dflash1 (tag="on-chip")
    {
        mau = 8;
        type = reserved nvram;
        size = 64k;
        map (dest=bus:sri, dest_offset=0xaf110000, size=64k);
    }
    memory lmuram (tag="on-chip")
    {
        mau = 8;
        type = ram;
        size = 32k;
        priority = 2;
        map cached(dest=bus:sri, dest_offset=0x90000000, size=32k);
        map not_cached(dest=bus:sri, dest_offset=0xb0000000, size=32k, reserved);
    }
    memory mcs00 (tag="on-chip")
    {
        mau = 8;
        write_unit = 4;
        type = ram;
        size = 0x1000+0x800;
        map ram0(dest=bus:aei, src_offset=0x0000, dest_offset=0xf0100000+0x38000, size=0x1000);
        map ram1(dest=bus:aei, src_offset=0x1000, dest_offset=0xf0100000+0x38000+0x1000, size=0x800);
        map mcs_ram0(dest=bus:mcs00:mcs_bus, src_offset=0x0000, dest_offset=0, size=0x1000);
        map mcs_ram1(dest=bus:mcs00:mcs_bus, src_offset=0x1000, dest_offset=0x1000, size=0x800);
    }
    memory mcs01 (tag="on-chip")
    {
        mau = 8;
        write_unit = 4;
        type = ram;
        size = 0x1000+0x800;
        map ram0(dest=bus:aei, src_offset=0x0000, dest_offset=0xf0100000+0x40000, size=0x1000);
        map ram1(dest=bus:aei, src_offset=0x1000, dest_offset=0xf0100000+0x40000+0x1000, size=0x800);
        map mcs_ram0(dest=bus:mcs01:mcs_bus, src_offset=0x0000, dest_offset=0, size=0x1000);
        map mcs_ram1(dest=bus:mcs01:mcs_bus, src_offset=0x1000, dest_offset=0x1000, size=0x800);
    }
    memory mcs02 (tag="on-chip")
    {
        mau = 8;
        write_unit = 4;
        type = ram;
        size = 0x1000+0x800;
        map ram0(dest=bus:aei, src_offset=0x0000, dest_offset=0xf0100000+0x48000, size=0x1000);
        map ram1(dest=bus:aei, src_offset=0x1000, dest_offset=0xf0100000+0x48000+0x1000, size=0x800);
        map mcs_ram0(dest=bus:mcs02:mcs_bus, src_offset=0x0000, dest_offset=0, size=0x1000);
        map mcs_ram1(dest=bus:mcs02:mcs_bus, src_offset=0x1000, dest_offset=0x1000, size=0x800);
    }
    memory mcs03 (tag="on-chip")
    {
        mau = 8;
        write_unit = 4;
        type = ram;
        size = 0x1000+0x800;
        map ram0(dest=bus:aei, src_offset=0x0000, dest_offset=0xf0100000+0x50000, size=0x1000);
        map ram1(dest=bus:aei, src_offset=0x1000, dest_offset=0xf0100000+0x50000+0x1000, size=0x800);
        map mcs_ram0(dest=bus:mcs03:mcs_bus, src_offset=0x0000, dest_offset=0, size=0x1000);
        map mcs_ram1(dest=bus:mcs03:mcs_bus, src_offset=0x1000, dest_offset=0x1000, size=0x800);
    }
}
#else
#include <cpu.lsl>
#endif
