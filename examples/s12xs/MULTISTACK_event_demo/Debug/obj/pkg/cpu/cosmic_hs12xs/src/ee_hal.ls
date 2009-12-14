   8                         xref f_EE_thread_end_instance
   9                         xref _wreg
  10                         
  11                         .ftext: section .text
  12                         
  13                          xref _PPAGE
  14                          xref _EE_hal_endcycle_next_thread
  15                           xdef _EE_s12xs_hal_stkchange
  16                           xref _EE_s12xs_system_tos
  17                           xref _EE_s12xs_active_tos
  18                           xref _EE_hal_endcycle_next_tos
  19                         
  20                           EE_CHANGE_TOS_MACRO: macro
  21                         
  22                         
  23                           ldd OFST+3,s
  24                           cpd \1
  25                           beq \@lab2
  26                         
  27                         
  28                         
  29                         
  30                         
  31                         
  32                           tfr s,d
  33                           ldy \1
  34                           lsly
  35                           std \2,y
  36                         
  37                         
  38                           ldd OFST+3,s
  39                           std \1
  40                           ldy \1
  41                           lsly
  42                           ldd \2,y
  43                           tfr d,s
  44                         
  45                         
  46                         
  47                         
  48                         
  49                          \@lab2:
  50                           endm
  51                         xdef f_EE_s12xs_hal_ready2stacked
  52  0000                   f_EE_s12xs_hal_ready2stacked:
  53                         
  54                         
  55  0000 7c0002             std _wreg+2
  56  0003 7e0000             stx _wreg
  57                         
  58  0006                    L3:
  59       00000000           OFST: set 0
  60                         
  61                         
  62                            EE_CHANGE_TOS_MACRO _EE_s12xs_active_tos, _EE_s12xs_system_tos, _PPAGE
  77                         
  78                         
  79  0028 10ef                cli
  80                         
  81  002a 4bfbffd2            call [_wreg]
  82  002e 1410                sei
  83  0030 4a000000            call f_EE_thread_end_instance
  84                         
  85                         
  86  0034 fc0000               ldd _EE_hal_endcycle_next_tos
  87  0037 6c83                 std OFST+3,s
  88                         
  89                         
  90  0039 fc0002              ldd _EE_hal_endcycle_next_thread+2
  91                         
  92  003c 7c0002              std _wreg+2
  93  003f fc0000              ldd _EE_hal_endcycle_next_thread
  94                         
  95  0042 7c0000              std _wreg
  96                         
  97                         
  98  0045 fc0000              ldd _wreg
  99  0048 2603                bne L21
 100                         
 101  004a fc0002              ldd _wreg+2
 102  004d                    L21:
 103  004d 26b7                bne L3
 104                         
 105                         
 106                            EE_CHANGE_TOS_MACRO _EE_s12xs_active_tos, _EE_s12xs_system_tos, _PPAGE
 121                         
 122                         
 123                         
 124                         
 125  0071 0a                  rtc
 126                         xdef f_EE_s12xs_hal_stkchange
 127  0072                   f_EE_s12xs_hal_stkchange:
 128  0072 b775                tfr s,x
 129  0074 fd0000              ldy _EE_s12xs_active_tos
 130  0077 1858                lsly
 131  0079 6eea0000            stx _EE_s12xs_system_tos,y
 132                         
 133                         
 134                         
 135                         
 136  007d 7c0000              std _EE_s12xs_active_tos
 137  0080 fd0000              ldy _EE_s12xs_active_tos
 138  0083 1858                lsly
 139  0085 ecea0000            ldd _EE_s12xs_system_tos,y
 140  0089 b747                tfr d,s
 141                         
 142                         
 143                         
 144                         
 145                         
 146                         
 147  008b 0a                  rtc
 148                         
 149                         
 150                         
 151                          end

Symbol table:

.2lab2                         00000028    Defined
                                  76    65
.3lab2                         00000071    Defined
                                 120   109
L21                            0000004d    Defined
                                 102    99
L3                             00000006    Defined
                                  58   103
OFST                           00000000    Defined, Absolute
                                  59    63    70    87   107   114
_EE_hal_endcycle_next_thread   00000000    Public
                                  14    90    93
_EE_hal_endcycle_next_tos      00000000    Public
                                  18    86
_EE_s12xs_active_tos           00000000    Public
                                  17    64    67    71    72   108   111   115   116   129
                                 136   137
_EE_s12xs_hal_stkchange        00000000    Not Referenced, Public
                                  15
_EE_s12xs_system_tos           00000000    Public
                                  16    69    74   113   118   131   139
_PPAGE                         00000000    Not Referenced, Public
                                  13
_wreg                          00000000    Public
                                   9    55    56    81    92    95    98   101
f_EE_s12xs_hal_ready2stacked   00000000    Defined, Not Referenced, Public
                                  51
f_EE_s12xs_hal_stkchange       00000072    Defined, Not Referenced, Public
                                 126
f_EE_thread_end_instance       00000000    Public
                                   8    83
