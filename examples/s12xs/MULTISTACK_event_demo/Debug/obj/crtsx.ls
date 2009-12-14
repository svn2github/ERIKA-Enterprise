   8                         ; C STARTUP FOR S12X
   9                         ; WITH AUTOMATIC DATA/CODE INITIALISATION
  10                         ; Copyright (c) 2006 by COSMIC Software
  11                         ;
  12                          xdef _exit, __stext
  13                         ; xref _main
  14                          xref f_main
  15                          xref __sbss, __memory, __idesc__, __stack, __sdirect
  16                          xref __subsct, __eubsct, __sgdflt
  17                          xref _GPAGE, _RPAGE, _PPAGE, _DIRECT, _EPAGE
  18                         ;
  19  0000                   __stext:
  20  0000 cf0000             lds #__stack ; initialize stack pointer
  21  0003 180b000000         movb #$00, _EPAGE
  22  0008 180bfd0000         movb #$FD,_RPAGE ; default ram configuration
  23  000d 180b000000         movb #high(__sdirect),_DIRECT ; direct page register
  24  0012 180b000000         movb #page(__idesc__),_PPAGE ; allows banked descriptor
  25  0017 ce0000             ldx #__idesc__ ; descriptor address
  26  001a ed31               ldy 2,x+ ; start address of prom data
  27  001c                   ibcl:
  28  001c a634               ldaa 5,x+ ; test flag byte
  29  001e 2737               beq zbss ; no more segment
  30  0020 2a02               bpl nopg ; page indicator
  31  0022 1a02               leax 2,x ; skip it
  32  0024                   nopg:
  33  0024 8560               bita #$60 ; test for moveable code segment
  34  0026 2604               bne dseg ; no, copy it
  35  0028 ed1e               ldy -2,x ; reload code address
  36  002a 20f0               bra ibcl ; and continue with next segment
  37  002c                   dseg:
  38  002c 34                 pshx ; save pointer
  39  002d 97                 tsta ; global addresses
  40  002e 2b10               bmi glob ; yes, copy
  41  0030 b764               tfr y,d ; start address
  42  0032 a31e               subd -2,x ; minus end address
  43  0034 ee1c               ldx -4,x ; destination address
  44  0036                   dbcl:
  45  0036 180a7030           movb 1,y+,1,x+ ; copy from prom to ram
  46  003a 04b4f9             ibne d,dbcl ; count up and loop
  47  003d 30                 pulx ; reload pointer to desc
  48  003e 20dc               bra ibcl ; and loop
  49  0040                   glob:
  50  0040 ec1e               ldd -2,x ; end address
  51  0042 3b                 pshd ; on the stack
  52  0043 180d1b0000         movb -5,x,_GPAGE ; set page register
  53  0048 ee1c               ldx -4,x ; destination address
  54  004a                   xbcl:
  55  004a e670               ldab 1,y+ ; read data
  56  004c 186b30             gstab 1,x+ ; and write to ram
  57  004f ad80               cpy 0,s ; compare with end address
  58  0051 25f7               blo xbcl ; and loop back
  59  0053 30                 pulx ; clean stack
  60  0054 30                 pulx ; reload pointer to desc
  61  0055 20c5               bra ibcl ; and loop
  62  0057                   zbss:
  63  0057 ce0000             ldx #__sbss ; start of bss
  64  005a c7                 clrb ; complete zero
  65  005b 2002               bra loop ; start loop
  66  005d                   zbcl:
  67  005d 6c31               std 2,x+ ; clear word
  68  005f                   loop:
  69  005f 8e0000             cpx #__memory ; end of bss
  70  0062 25f9               blo zbcl ; no, continue
  71  0064 ce0000             ldx #__subsct ; start of ubsct
  72  0067 2002               bra uloop ; start loop
  73  0069                   zubs:
  74  0069 6b30               stab 1,x+ ; clear byte
  75  006b                   uloop:
  76  006b 8e0000             cpx #__eubsct ; end of ubsct
  77  006e 25f9               blo zubs ; no continue
  78  0070 180b000000         movb #phigh(__sgdflt),_GPAGE ; set global page default
  79                         ; jsr _main ; execute main
  80  0075 4a000000           call f_main ; in case main is banked
  81  0079                   _exit:
  82  0079 20fe               bra _exit ; stay here
  83                         ;
  84                          end

Symbol table:

_DIRECT     00000000    Public
               17    23
_EPAGE      00000000    Public
               17    21
_GPAGE      00000000    Public
               17    52    78
_PPAGE      00000000    Public
               17    24
_RPAGE      00000000    Public
               17    22
__eubsct    00000000    Public
               16    76
__idesc__   00000000    Public
               15    24    25
__memory    00000000    Public
               15    69
__sbss      00000000    Public
               15    63
__sdirect   00000000    Public
               15    23
__sgdflt    00000000    Public
               16    78
__stack     00000000    Public
               15    20
__stext     00000000    Defined, Not Referenced, Public
               12
__subsct    00000000    Public
               16    71
_exit       00000079    Defined, Public
               12    82
dbcl        00000036    Defined
               44    46
dseg        0000002c    Defined
               37    34
f_main      00000000    Public
               14    80
glob        00000040    Defined
               49    40
ibcl        0000001c    Defined
               27    36    48    61
loop        0000005f    Defined
               68    65
nopg        00000024    Defined
               32    30
uloop       0000006b    Defined
               75    72
xbcl        0000004a    Defined
               54    58
zbcl        0000005d    Defined
               66    70
zbss        00000057    Defined
               62    29
zubs        00000069    Defined
               73    77
