   8                         xdef f_EE_s12xs_terminate_savestk
   9  0000                   f_EE_s12xs_terminate_savestk:
  10                         
  11  0000 3b                 pshd
  12       00000000          OFST: set 0
  13                         
  14                         
  15                         
  16  0001 b774                  tfr s,d
  17  0003 c30002                addd #$02
  18                         
  19  0006 6cf30000              std [OFST+0,s]
  20                         
  21  000a 4bf30005           call [OFST+5,s]
  22                         
  23  000e 3a                 puld
  24                         
  25                         xdef f_EE_s12xs_terminate_task
  26  000f                   f_EE_s12xs_terminate_task:
  27                         
  28  000f b746               tfr d,y
  29                         
  30                         
  31                         
  32  0011 ef40               lds 0,y
  33                         
  34  0013 0a                    rtc
  35                         
  36                          end

Symbol table:

OFST                           00000000    Defined, Absolute
                                  12    19    21
f_EE_s12xs_terminate_savestk   00000000    Defined, Not Referenced, Public
                                   8
f_EE_s12xs_terminate_task      0000000f    Defined, Not Referenced, Public
                                  25
