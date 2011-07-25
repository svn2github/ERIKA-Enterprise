#include "ee.h"
#include "mcu/microchip_dspic/inc/ee_uart.h"
#include "mcu/microchip_dspic/inc/ee_internal.h"
#include "mcu/microchip_dspic/inc/ee_utils.h"
#include "cpu/pic30/inc/ee_irqstub.h"

#ifdef EE_UART_PORT_1_ISR_ENABLE
static void (*Rx1IsrFunction)(EE_UINT8 data) = NULL;
static void (*Tx1IsrFunction)(void) = NULL;
#endif
#ifdef EE_UART_PORT_2_ISR_ENABLE
static void (*Rx2IsrFunction)(EE_UINT8 data) = NULL;
static void (*Tx2IsrFunction)(void) = NULL;
#endif

#if defined(EE_PROGRAMMABLE_IO)

#ifndef EE_Board_Uart1_Rx
#define EE_Board_Uart1_Rx EE_PIN_RP25 /* default chosen for miniflex board*/
#endif  /* EE_Board_Uart1_Rx */

#ifndef EE_Board_Uart1_Cts
#define EE_Board_Uart1_Cts 0b11111 /* default pin at Vss */
#endif  /* EE_Board_Uart1_Cts */

#ifndef EE_Board_Uart1_Tx
#define EE_Board_Uart1_Tx EE_PIN_RP24 /* default chosen for miniflex board*/
#endif /* EE_Board_Uart1_Tx */

#ifndef EE_Board_Uart1_Rts
#define EE_Board_Uart1_Rts EE_PIN_RP16 /* default random */
#endif /* EE_Board_Uart1_Rts */

#ifndef EE_Board_Uart2_Rx
#define EE_Board_Uart2_Rx EE_PIN_RP25 /* default chosen for miniflex board */
#endif  /* EE_Board_Uart2_Rx */

#ifndef EE_Board_Uart2_Cts
#define EE_Board_Uart2_Cts 0b11111 /* default: pin at Vss */
#endif  /* EE_Board_Uart2_Cts */

#ifndef EE_Board_Uart2_Tx
#define EE_Board_Uart2_Tx EE_PIN_RP24 /* default chosen for miniflex board */
#endif /* EE_Board_Uart2_Tx */

#ifndef EE_Board_Uart2_Rts
#define EE_Board_Uart2_Rts EE_PIN_RP16 /* default random */
#endif /* EE_Board_Uart1_Rts */

#else /* !defined(EE_PROGRAMMABLE_IO) */

#define EE_Board_Uart1_Rx  EE_NO_PROGRAMMABLE_PIN
#define EE_Board_Uart1_Cts EE_NO_PROGRAMMABLE_PIN
#define EE_Board_Uart1_Tx  EE_NO_PROGRAMMABLE_PIN
#define EE_Board_Uart1_Rts EE_NO_PROGRAMMABLE_PIN
#define EE_Board_Uart2_Rx  EE_NO_PROGRAMMABLE_PIN
#define EE_Board_Uart2_Cts EE_NO_PROGRAMMABLE_PIN
#define EE_Board_Uart2_Tx  EE_NO_PROGRAMMABLE_PIN
#define EE_Board_Uart2_Rts EE_NO_PROGRAMMABLE_PIN

#endif /* defined(EE_PROGRAMMABLE_IO) */

static EE_INT16 EE_compute_ticks_for_baud(EE_UINT32 baud)
{
    EE_INT32 ticksForBaud = EE_get_peripheral_clock();
    if(ticksForBaud > 0) {
        /* Per far eseguire l'arrotondamemto si utilizza il trucco (x + (y/2))y */
        ticksForBaud = (ticksForBaud + baud / 2) / baud;
    }
    return ticksForBaud;
}

static void EE_uart1_init()
{
    U1MODE          = 0;        /* reset UART 1 mode registry */
    IEC0bits.U1RXIE = 0;        /* Disable Interrupts */
    IEC0bits.U1TXIE = 0;
    IFS0bits.U1RXIF = 0;        /* Clear Interrupt flag bits */
    IFS0bits.U1TXIF = 0;
}

static void EE_uart1_in_init(EE_UINT16 mode){
    EE_conf_dspic_pin_in(EE_Board_Uart1_Rx, U1RX_SIGNAL);
    if (mode == EE_UART_CTRL_FLOW) {
        EE_conf_dspic_pin_in(EE_Board_Uart1_Cts, U1CTS_SIGNAL);
    }
}

static void EE_uart1_out_init(EE_UINT16 mode){
    EE_conf_dspic_pin_out(EE_Board_Uart1_Tx, U1TX_SIGNAL);
    if (mode == EE_UART_CTRL_FLOW) {
        EE_conf_dspic_pin_out(EE_Board_Uart1_Rts, U1RTS_SIGNAL);
    }
}

static void EE_uart1_conf_baudrate(EE_UINT32 baud){
    EE_INT16 ticsForBaud = EE_compute_ticks_for_baud(baud);
    if(ticsForBaud > 0) {
        if(ticsForBaud > 16) {/* I have enough time to go slow (16x ticks for UART bit) */
            U1MODEbits.BRGH = 0; /* UART bit lenght is 16x of clock (istruction not needed, just to make it explicit) */
            /* UART Baud Rate Generator (BRG): vedi dspic family reference manual section 19-3 */
            U1BRG = ticsForBaud / 16 - 1;
        } else {
            U1MODEbits.BRGH = 1; /* UART bit lenght is 4x of clock */
            /* UART Baud Rate Generator (BRG): vedi dspic family reference manual section 19-3 */
            U1BRG = ticsForBaud / 4 - 1;
        }
    }
}

#if defined(_U2RXIE) /* this simbol is only defined when there is UART 2 */

static void EE_uart2_init(){
    U2MODE          = 0;        /* reset UART 2 mode registry */
    IEC1bits.U2RXIE = 0;        /* Disable Interrupts */
    IEC1bits.U2TXIE = 0;
    IFS1bits.U2RXIF = 0;        /* Clear Interrupt flag bits */
    IFS1bits.U2TXIF = 0;
}

static void EE_uart2_in_init(EE_UINT16 mode){
    EE_conf_dspic_pin_in(EE_Board_Uart2_Rx, U2RX_SIGNAL);
    if (mode == EE_UART_CTRL_FLOW) {
        EE_conf_dspic_pin_in(EE_Board_Uart2_Cts, U2CTS_SIGNAL);
    }
}

static void EE_uart2_out_init(EE_UINT16 mode){
    EE_conf_dspic_pin_out(EE_Board_Uart2_Tx, U2TX_SIGNAL);
    if (mode == EE_UART_CTRL_FLOW) {
        EE_conf_dspic_pin_out(EE_Board_Uart2_Rts, U2RTS_SIGNAL);
    }
}

static void EE_uart2_conf_baudrate(EE_UINT32 baud){
    EE_INT16 ticsForBaud = EE_compute_ticks_for_baud(baud);
    if(ticsForBaud > 0) {
        if(ticsForBaud > 16) {/* I have enough time to go slow (16x ticks for UART bit) */
            U2MODEbits.BRGH = 0; /* UART bit lenght is 16x of clock (istruction not needed, just to make it explicit) */
            /* UART Baud Rate Generator (BRG): vedi dspic family reference manual section 19-3 */
            U2BRG = ticsForBaud / 16 - 1;
        } else {
            U2MODEbits.BRGH = 1; /* UART bit lenght is 4x of clock */
            /* UART Baud Rate Generator (BRG): vedi dspic family reference manual section 19-3 */
            U2BRG = ticsForBaud / 4 - 1;
        }
    }
}
#else  /* UART2 not present */
#define EE_uart2_init()
#define EE_uart2_in_init(mode)
#define EE_uart2_out_init(mode)
#define EE_uart2_conf_baudrate(baud)
#endif /*_U2RXIE: this simbol is only defined when there is UART 2 */

EE_INT8 EE_uart_init(EE_UINT8 port, EE_UINT32 baud, EE_UINT16 byte_format,
             EE_UINT16 mode)
{
    if (port == EE_UART_PORT_1) {
        EE_uart1_init();
        EE_uart1_in_init(mode);
        EE_uart1_out_init(mode);
        /* baud rate */
        EE_uart1_conf_baudrate(baud);
        U1MODEbits.UARTEN = 1; /* abilito l'UART */
        if (mode == EE_UART_CTRL_FLOW) {
            U1MODEbits.RTSMD = 1;
            U1MODEbits.UEN = 2;
        } else {
            U1MODEbits.RTSMD = 0;
            U1MODEbits.UEN = 0;
        }
        /* Number of bit, Parity and Stop bits */
        U1MODE |= byte_format & 0x07;
        /* TX & RX interrupt modes */
        U1STA = 0;
        U1STAbits.UTXEN = 1;
        return 1;
    } else if (port == EE_UART_PORT_2) {
        EE_uart2_init();
        EE_uart2_in_init(mode);
        EE_uart2_out_init(mode);
        /* baud rate */
        EE_uart2_conf_baudrate(baud);

        U2MODEbits.UARTEN = 1; /* abilito l'UART */
        if (mode == EE_UART_CTRL_FLOW) {
            U2MODEbits.RTSMD = 1;
            U2MODEbits.UEN = 2;
        } else {    /* Simple Mode */
            U2MODEbits.RTSMD = 0;
            U2MODEbits.UEN = 0;
        }
        /* Number of bit, Parity and Stop bits */
        U2MODE |= byte_format & 0x07;
        /* TX & RX interrupt modes */
        U2STA = 0;
        U2STAbits.UTXEN = 1;
        return 1;
    }
    return EE_UART_ERR_BAD_PORT;
}

EE_INT8 EE_uart_close(EE_UINT8 port)
{
    if (port == EE_UART_PORT_1) {
        /* chris: TODO: Release something */
        return 1;
    } else if (port == EE_UART_PORT_2) {
        /* chris: TODO: Release something */
        return 1;
    }
    return EE_UART_ERR_BAD_PORT;
}

EE_INT8 EE_uart_set_tx_callback(EE_UINT8 port, void (*TxFunc)(void),
                EE_UINT16 txmode)
{
    if (port == EE_UART_PORT_1) {
        #ifdef EE_UART_PORT_1_ISR_ENABLE
        Tx1IsrFunction = TxFunc;
        if (TxFunc) {
            U1STA &= 0x5FFF;
            U1STA |= txmode & 0xA000;
            IEC0bits.U1TXIE = 1;
            IFS0bits.U1TXIF = 0;
        }
        return 1;
        #else
        return EE_UART_ERR_INT_DISABLED;
        #endif
    } else if (port == EE_UART_PORT_2) {
        #ifdef EE_UART_PORT_2_ISR_ENABLE
        Tx2IsrFunction = TxFunc;
        if (TxFunc) {
            U2STA &= 0x5FFF;
            U2STA |= txmode & 0xA000;
            IEC1bits.U2TXIE = 1;
            IFS1bits.U2TXIF = 0;
        }
        return 1;
        #else
        return EE_UART_ERR_INT_DISABLED;
        #endif
    }
    return EE_UART_ERR_BAD_PORT;
}

EE_INT8 EE_uart_set_rx_callback(EE_UINT8 port, void (*RxFunc)(EE_UINT8 data),
                EE_UINT16 rxmode)
{
    if (port == EE_UART_PORT_1) {
        #ifdef EE_UART_PORT_1_ISR_ENABLE
        Rx1IsrFunction = RxFunc;
        if (RxFunc) {
            U1STA &= 0xFF3F;
            U1STA |= rxmode & 0x00C0;
            IEC0bits.U1RXIE = 1;
            IFS0bits.U1RXIF = 0;
        }
        return 1;
        #else
        return EE_UART_ERR_INT_DISABLED;
        #endif
    } else if (port == EE_UART_PORT_2) {
        #ifdef EE_UART_PORT_2_ISR_ENABLE
        Rx2IsrFunction = RxFunc;
        if (RxFunc) {
            U2STA &= 0xFF3F;
            U2STA |= rxmode & 0x00C0;
            IEC1bits.U2RXIE = 1;
            IFS1bits.U2RXIF = 0;
        }
        return 1;
        #else
        return EE_UART_ERR_INT_DISABLED;
        #endif
    }
    return EE_UART_ERR_BAD_PORT;
}

EE_INT8 EE_uart_write_byte(EE_UINT8 port, EE_UINT8 data)
{
    if (port == EE_UART_PORT_1) {
        /* Polling mode */
        while (U1STAbits.UTXBF) ;
        U1TXREG = data;
        while (!U1STAbits.TRMT) ;
        return 1;
    } else if (port == EE_UART_PORT_2) {
        /* Polling mode */
        while (U2STAbits.UTXBF) ;
        U2TXREG = data;
        while (!U2STAbits.TRMT) ;
        return 1;
    }
    return EE_UART_ERR_BAD_PORT;
}

EE_INT8 EE_uart_write_string(EE_UINT8 port, const char* str)
{
    int error, i = 0;
    if(str){
        for(; str[i]!='\0'; ++i){
            error = EE_uart_write_byte(port, str[i]);
            if(error < 0)
                return error;
        }
    }
    return i;
}

EE_INT8 EE_uart_read_byte(EE_UINT8 port, EE_UINT8 *data)
{
    if (port == EE_UART_PORT_1) {
        #ifdef EE_UART_PORT_1_ISR_ENABLE
        if (Rx1IsrFunction == NULL) {
            /* Polling mode */
        #endif
            if (U1STAbits.OERR) {
                U1STAbits.OERR = 0;
                return EE_UART_ERR_OVERFLOW;
            }
            if (U1STAbits.URXDA) {
                *data = U1RXREG & 0x00FF;
                U1STAbits.URXDA = 0;
                return 1;
            }
            return EE_UART_ERR_NO_DATA;
        #ifdef EE_UART_PORT_1_ISR_ENABLE
        }
        return EE_UART_ERR_INT_MODE;
        #endif
    } else if (port == EE_UART_PORT_2) {
        #ifdef EE_UART_PORT_2_ISR_ENABLE
        if (Rx2IsrFunction == NULL) {
            /* Polling mode */
        #endif
            if (U2STAbits.OERR) {
                U2STAbits.OERR = 0;
                return EE_UART_ERR_OVERFLOW;
            }
            if (U2STAbits.URXDA) {
                U2STAbits.URXDA = 0;
                *data = U2RXREG & 0x00FF;
                return 1;
            }
            return EE_UART_ERR_NO_DATA;
        #ifdef EE_UART_PORT_2_ISR_ENABLE
        }
        return EE_UART_ERR_INT_MODE;
        #endif
    }
    return EE_UART_ERR_BAD_PORT;
}


#ifdef EE_UART_PORT_1_ISR_ENABLE
ISR2(_U1RXInterrupt)
{
    if (Rx1IsrFunction != NULL) {
        /* Execute callback function */
        Rx1IsrFunction(U1RXREG & 0x00FF);
    }
    IFS0bits.U1RXIF = 0;
}

ISR2(_U1TXInterrupt)
{
    if (Tx1IsrFunction != NULL) {
        /* Execute callback function */
        Tx1IsrFunction();
    }
    IFS0bits.U1TXIF = 0;
}
#endif

#ifdef EE_UART_PORT_2_ISR_ENABLE
ISR2(_U2RXInterrupt)
{
    if (Rx2IsrFunction != NULL) {
        /* Execute callback function */
        Rx2IsrFunction(U2RXREG & 0x00FF);
    }
    IFS1bits.U2RXIF = 0;
}

ISR2(_U2TXInterrupt)
{
    if (Tx2IsrFunction != NULL) {
        /* Execute callback function */
        Tx2IsrFunction();
    }
    IFS1bits.U2TXIF = 0;
}
#endif

