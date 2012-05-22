/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/** @file   Port_Cfg_internal.h
 *  @brief  Static part (types definition) of AUTOSAR Port Driver Configuration
 *     Header File.
 *
 *  Configured for (MCU): Freescale MPC5643L (Leopard)
 *
 *  @author Errico Guidieri
 *  @date   2012
 */

#ifndef PORT_CFG_INTERNAL_H
#define PORT_CFG_INTERNAL_H

#include "Cfg.h"

/* PORT006: The user of the PORT Driver module shall configure the symbolic
 *    names of the port pins of the MCU.
 *
 * PORT207: These symbolic names for the individual port pins (e.g.
 *    PORT_A_PIN_0) shall be defined in the configuration tool.
 *
 * PORT076: The PORT Driver modules implementer shall define symbolic names
 *    in the file Port_Cfg.h
 *
 * PORT208: The PORT Driver modules implementer shall publish the symbolic
 *    names through the file Port.h
 */

#define PORT_A    0U  /**< Port A   */
#define PORT_B    1U  /**< Port B   */
#define PORT_C    2U  /**< Port C   */
#define PORT_D    3U  /**< Port D   */
#define PORT_E    4U  /**< Port E   */
#define PORT_F    5U  /**< Port F   */
#define PORT_G    6U  /**< Port G   */
#define PORT_H    7U  /**< Port H   */
#define PORT_I    8U  /**< Port I   */

/* At Each Pin Is Associated Corresponding PCR value as ID */

#define PORT_A_PIN_0    0U    /**< Port A - Pin 0 */
#define PORT_A_PIN_1    1U    /**< Port A - Pin 1 */
#define PORT_A_PIN_2    2U    /**< Port A - Pin 2 */
#define PORT_A_PIN_3    3U    /**< Port A - Pin 3 */
#define PORT_A_PIN_4    4U    /**< Port A - Pin 4 */
#define PORT_A_PIN_5    5U    /**< Port A - Pin 5 */
#define PORT_A_PIN_6    6U    /**< Port A - Pin 6 */
#define PORT_A_PIN_7    7U    /**< Port A - Pin 7 */
#define PORT_A_PIN_8    8U    /**< Port A - Pin 8 */
#define PORT_A_PIN_9    9U    /**< Port A - Pin 9 */
#define PORT_A_PIN_10   10U   /**< Port A - Pin 10 */
#define PORT_A_PIN_11   11U   /**< Port A - Pin 11 */
#define PORT_A_PIN_12   12U   /**< Port A - Pin 12 */
#define PORT_A_PIN_13   13U   /**< Port A - Pin 13 */
#define PORT_A_PIN_14   14U   /**< Port A - Pin 14 */
#define PORT_A_PIN_15   15U   /**< Port A - Pin 15 */

#define PORT_B_PIN_0    16U   /**< Port B - Pin 0 */
#define PORT_B_PIN_1    17U   /**< Port B - Pin 1 */
#define PORT_B_PIN_2    18U   /**< Port B - Pin 2 */
#define PORT_B_PIN_3    19U   /**< Port B - Pin 3 */
#define PORT_B_PIN_4    20U   /**< Port B - Pin 4 */
#define PORT_B_PIN_5    21U   /**< Port B - Pin 5 */
#define PORT_B_PIN_6    22U   /**< Port B - Pin 6 */
#define PORT_B_PIN_7    23U   /**< Port B - Pin 7 */
#define PORT_B_PIN_8    24U   /**< Port B - Pin 8 */
#define PORT_B_PIN_9    25U   /**< Port B - Pin 9 */
#define PORT_B_PIN_10   26U   /**< Port B - Pin 10 */
#define PORT_B_PIN_11   27U   /**< Port B - Pin 11 */
#define PORT_B_PIN_12   28U   /**< Port B - Pin 12 */
#define PORT_B_PIN_13   29U   /**< Port B - Pin 13 */
#define PORT_B_PIN_14   30U   /**< Port B - Pin 14 */
#define PORT_B_PIN_15   31U   /**< Port B - Pin 15 */

#define PORT_C_PIN_0    32U   /**< Port C - Pin 0 */
#define PORT_C_PIN_1    33U   /**< Port C - Pin 1 */
#define PORT_C_PIN_2    34U   /**< Port C - Pin 2 */
#define PORT_C_PIN_3    35U   /**< Port C - Pin 3 */
#define PORT_C_PIN_4    36U   /**< Port C - Pin 4 */
#define PORT_C_PIN_5    37U   /**< Port C - Pin 5 */
#define PORT_C_PIN_6    38U   /**< Port C - Pin 6 */
#define PORT_C_PIN_7    39U   /**< Port C - Pin 7 */
#define PORT_C_PIN_8    40U   /**< Port C - Pin 8 */
#define PORT_C_PIN_9    41U   /**< Port C - Pin 9 */
#define PORT_C_PIN_10   42U   /**< Port C - Pin 10 */
#define PORT_C_PIN_11   43U   /**< Port C - Pin 11 */
#define PORT_C_PIN_12   44U   /**< Port C - Pin 12 */
#define PORT_C_PIN_13   45U   /**< Port C - Pin 13 */
#define PORT_C_PIN_14   46U   /**< Port C - Pin 14 */
#define PORT_C_PIN_15   47U   /**< Port C - Pin 15 */

#define PORT_D_PIN_0    48U   /**< Port D - Pin 0 */
#define PORT_D_PIN_1    49U   /**< Port D - Pin 1 */
#define PORT_D_PIN_2    50U   /**< Port D - Pin 2 */
#define PORT_D_PIN_3    51U   /**< Port D - Pin 3 */
#define PORT_D_PIN_4    52U   /**< Port D - Pin 4 */
#define PORT_D_PIN_5    53U   /**< Port D - Pin 5 */
#define PORT_D_PIN_6    54U   /**< Port D - Pin 6 */
#define PORT_D_PIN_7    55U   /**< Port D - Pin 7 */
#define PORT_D_PIN_8    56U   /**< Port D - Pin 8 */
#define PORT_D_PIN_9    57U   /**< Port D - Pin 9 */
#define PORT_D_PIN_10   58U   /**< Port D - Pin 10 */
#define PORT_D_PIN_11   59U   /**< Port D - Pin 11 */
#define PORT_D_PIN_12   60U   /**< Port D - Pin 12 */
#define PORT_D_PIN_14   62U   /**< Port D - Pin 14 */

#define PORT_E_PIN_0    64U   /**< Port E - Pin 0 */
#define PORT_E_PIN_2    66U   /**< Port E - Pin 1 */
#define PORT_E_PIN_4    68U   /**< Port E - Pin 4 */
#define PORT_E_PIN_5    69U   /**< Port E - Pin 5 */
#define PORT_E_PIN_6    70U   /**< Port E - Pin 6 */
#define PORT_E_PIN_7    71U   /**< Port E - Pin 7 */
#define PORT_E_PIN_9    73U   /**< Port E - Pin 7 */
#define PORT_E_PIN_10   74U   /**< Port E - Pin 10 */
#define PORT_E_PIN_11   75U   /**< Port E - Pin 11 */
#define PORT_E_PIN_12   76U   /**< Port E - Pin 12 */
#define PORT_E_PIN_13   77U   /**< Port E - Pin 13 */
#define PORT_E_PIN_14   78U   /**< Port E - Pin 14 */
#define PORT_E_PIN_15   79U   /**< Port E - Pin 15 */

#define PORT_F_PIN_0    80U   /**< Port F - Pin 0 */
#define PORT_F_PIN_3    83U   /**< Port F - Pin 3 */
#define PORT_F_PIN_4    84U   /**< Port F - Pin 4 */
#define PORT_F_PIN_5    85U   /**< Port F - Pin 5 */
#define PORT_F_PIN_6    86U   /**< Port F - Pin 6 */
#define PORT_F_PIN_7    87U   /**< Port F - Pin 7 */
#define PORT_F_PIN_8    88U   /**< Port F - Pin 8 */
#define PORT_F_PIN_9    89U   /**< Port F - Pin 9 */
#define PORT_F_PIN_10   90U   /**< Port F - Pin 10 */
#define PORT_F_PIN_11   91U   /**< Port F - Pin 11 */
#define PORT_F_PIN_12   92U   /**< Port F - Pin 12 */
#define PORT_F_PIN_13   93U   /**< Port F - Pin 13 */
#define PORT_F_PIN_14   94U   /**< Port F - Pin 14 */
#define PORT_F_PIN_15   95U   /**< Port F - Pin 15 */

#define PORT_G_PIN_2    98U   /**< Port G - Pin 2 */
#define PORT_G_PIN_3    99U   /**< Port G - Pin 3 */
#define PORT_G_PIN_4    100U  /**< Port G - Pin 4 */
#define PORT_G_PIN_5    101U  /**< Port G - Pin 5 */
#define PORT_G_PIN_6    102U  /**< Port G - Pin 6 */
#define PORT_G_PIN_7    103U  /**< Port G - Pin 7 */
#define PORT_G_PIN_8    104U  /**< Port G - Pin 8 */
#define PORT_G_PIN_9    105U  /**< Port G - Pin 9 */
#define PORT_G_PIN_10   106U  /**< Port G - Pin 10 */
#define PORT_G_PIN_11   107U  /**< Port G - Pin 11 */
#define PORT_G_PIN_12   108U  /**< Port G - Pin 12 */
#define PORT_G_PIN_13   109U  /**< Port G - Pin 13 */
#define PORT_G_PIN_14   110U  /**< Port G - Pin 14 */
#define PORT_G_PIN_15   111U  /**< Port G - Pin 15 */

#define PORT_H_PIN_0    112U  /**< Port H - Pin 0 */
#define PORT_H_PIN_1    113U  /**< Port H - Pin 1 */
#define PORT_H_PIN_2    114U  /**< Port H - Pin 2 */
#define PORT_H_PIN_3    115U  /**< Port H - Pin 3 */
#define PORT_H_PIN_4    116U  /**< Port H - Pin 4 */
#define PORT_H_PIN_5    117U  /**< Port H - Pin 5 */
#define PORT_H_PIN_6    118U  /**< Port H - Pin 6 */
#define PORT_H_PIN_7    119U  /**< Port H - Pin 7 */

#define PORT_I_PIN_0    128U  /**< Port I - Pin 0 */
#define PORT_I_PIN_1    129U  /**< Port I - Pin 1 */
#define PORT_I_PIN_2    130U  /**< Port I - Pin 2 */
#define PORT_I_PIN_3    131U  /**< Port I - Pin 3 */

/** @brief  Number of Port Pins */
#define PORT_PINS_NUMBER 132U /* does it make sense ? */

/* Macros to check/set Pad Control Registes (PCR) */
/** @brief enable safe mode (override mode configuration) */
#define PORT_SAFE_MODE_CONTROL              AS_16_BIT1
/** @brief enable analog pad input (override mode configuration) */
#define PORT_ANALOG_PAD_CONTROL             AS_16_BIT2

/** @brief pad output function assignement */
#define PORT_OUTPUT_ASSIGNMENT_ALT_MODE_0   0U
#define PORT_OUTPUT_ASSIGNMENT_ALT_MODE_1   AS_16_BIT5
#define PORT_OUTPUT_ASSIGNMENT_ALT_MODE_2   AS_16_BIT4
#define PORT_OUTPUT_ASSIGNMENT_ALT_MODE_3   (AS_16_BIT4 | AS_16_BIT5)

/** @brief enable pad output */
#define PORT_OUTPUT_BUFFER_ENABLE            AS_16_BIT6
/** @brief enable pad input */
#define PORT_INPUT_BUFFER_ENABLE             AS_16_BIT7
/** @brief enable pad output as open drain */
#define PORT_OPEN_DRAIN_OUTPUT_ENABLE        AS_16_BIT10
/** @brief control pad output slew rate */
#define PORT_SLEW_RATE_CONTROL               AS_16_BIT13
/** @brief Weak Pull Up/Down Enable */
#define PORT_WEAK_PULL_UPDOWN_ENABLE         AS_16_BIT14
/** @brief active Weak Pull Up/Down when WPE is true */
#define PORT_WEAK_PULL_UPDOWN_SELECT         AS_16_BIT15

/* PORT Pins Modes (Port_PinModeType: uint8_least) */

/*
   Each Port Pin Can Support as far as 4 modes for output and 5 for input
   (GPIO + 4 Alternate Input) DIO mode is in common between input ed output
   for a total of 8 modes.

   DIO Mode must be used like a bitmasks.

   OUT alternative modes are really alternative so I use only 2 bits to encode
   them

   Input modes have to be handled as bitmasks because they could be more than
   one
*/

/** @brief Pin DIO Mode (default mode, have to be used as bitmasks) */
#define PORT_PIN_MODE_DIO             0x01U
/** @brief Pin Alternate Out Mode 1 */
#define PORT_PIN_MODE_ALT_OUT_1       2U
/** @brief Pin Alternate Out Mode 2 */
#define PORT_PIN_MODE_ALT_OUT_2       4U
/** @brief Pin Alternate Out Mode 3 */
#define PORT_PIN_MODE_ALT_OUT_3       6U
/** @brief Pin Analog Input MODE 1 (Input modes have to be used like bitmsks) */
#define PORT_PIN_MODE_ALT_INPUT_1     0x08U
/** @brief Pin Analog Input MODE 2 (Input modes have to be used like bitmsks) */
#define PORT_PIN_MODE_ALT_INPUT_2     0x10U
/** @brief Pin Analog Input MODE 3 (Input modes have to be used like bitmsks) */
#define PORT_PIN_MODE_ALT_INPUT_3     0x20U
/** @brief Pin Analog Input MODE 4 (Input modes have to be used like bitmsks)
    (only pin C[15] sob) */
#define PORT_PIN_MODE_ALT_INPUT_4     0x40U

/** @brief "Number" of modes for a port pin (is not the actual number of modes
    is just a guard bigger than all valid configurations) */
#define PORT_PIN_MODES_NUMBER         0x80U

/*                Semantic Names Mode Remapping for each pin
                 (TODO: add all alternative in & out for pins)
*/

#define PORT_B_PIN_6_OUT_CLOCK            PORT_PIN_MODE_ALT_OUT_1

#define PORT_B_PIN_7_IN_ADC0_0            PORT_PIN_MODE_ALT_INPUT_2

#define PORT_B_PIN_8_IN_ADC0_1            PORT_PIN_MODE_ALT_INPUT_2

#define PORT_C_PIN_1_IN_ADC0_2            PORT_PIN_MODE_ALT_INPUT_1

#define PORT_C_PIN_14_OUT_CTU_0_EXT_TGR   PORT_PIN_MODE_ALT_OUT_2

#define PORT_C_PIN_15_FLEXPWM0_A1         PORT_PIN_MODE_ALT_OUT_3

#define PORT_D_PIN_10_FLEXPWM0_A0         PORT_PIN_MODE_ALT_OUT_1

#define PORT_D_PIN_11_FLEXPWM0_B0         PORT_PIN_MODE_ALT_OUT_1

#define PORT_G_PIN_3_FLEXPWM0_A2          PORT_PIN_MODE_ALT_OUT_1

/** @brief  Pin Mode Configuration Parameters
 *
 * This container contains the configuration (parameters) of a Port Pin Mode.
 */
typedef struct {

  /** @brief  Pin Mode
   *
   *  <b>PORT130_Conf:</b> Port pin mode from mode list. Note that more than one
   *  mode is allowed by default. That way it is e.g. possible to combine DIO
   *  with another mode such as ICU. More HW specific literals may be added by
   *  module implementor. E.g. SPI may be further broken down into SpiCsHw,
   *  SpiCsSw, etc. if necessary.
   */
  const Port_PinModeType  PortPinMode;

  /** @brief  Pad Configuration Data.
   *
   * Port Pin Mode Hardware Configuration Data.
   */
  const uint16            PortPinModePadConfig;

} Port_PinModeConfType;

/** @brief  Pin Configuration Parameters
 *
 *  <b>PORT118_Conf:</b> Configuration of the individual port pins.
 */
typedef struct {

  /** @brief  Direction
   *
   *  <b>PORT125_Conf:</b> The initial direction of the pin (<tt>IN</tt> or
   *  <tt>OUT</tt>). If the direction is not changeable, the value configured
   *  here is fixed. The direction must match the pin mode. E.g. a pin used for
   *  an ADC must be configured to be an in port.
   */
  const Port_PinDirectionType   PortPinDirection;

  /** @brief  Direction Changeable
   *
   *  <b>PORT126_Conf:</b> Parameter to indicate if the direction is changeable
   *  on a port pin during runtime.
   *  - <b>true</b>:  Port Pin direction changeable enabled.
   *  - <b>false</b>: Port Pin direction changeable disabled.
   */
  const boolean                 PortPinDirectionChangeable;

  /** @brief  Identifier
   *
   *  <b>PORT127_Conf:</b> Pin Id of the port pin. This value will be assigned
   *  to the symbolic name derived from the port pin container short name.
   */
  const Port_PinType            PortPinId;

  /** @brief  Initial Mode
   *
   *  <b>PORT128_Conf:</b> Port pin mode from mode list for use with
   *  <tt>Port_Init()</tt> function.
   */
  const Port_PinModeType        PortPinInitialMode;

  /** @brief  Level Value
   *
   *  <b>PORT129_Conf:</b> Port Pin Level value from Port pin list.
   */
  const Port_PinLevelType       PortPinLevelValue;

  /** @brief  Modes Number
   *
   *  Number of Supported Port Pin Modes ( > 0 ).
   */
  const uint32                  PortPinModeNumber;

  /** @brief  Supported Modes
   *
   *  Supported Port Pin Modes.
   */
  const Port_PinModeConfType * const PortPinSupportedModes;

  /** @brief  Pin Mode Changeable
   *
   *  <b>PORT134_Conf:</b> Parameter to indicate if the mode is changeable on a
   *  port pin during runtime.
   *  - <b>true</b>:  Port Pin mode changeable allowed.
   *  - <b>False:</b> Port Pin mode changeable not permitted.
   */
  const boolean                 PortPinModeChangeable;

} Port_PinConfType;

/** @brief  Port Pins Configuration Parameters
 *
 *  <b>PORT122_Conf:</b> Container collecting the PortPins.
 */
typedef struct {

  /** @brief  Pins Number
   *
   *  <b>PORT124_Conf:</b>  The number of specified PortPins.
   */
  const uint32                      PortNumberOfPortPins;

  /** @brief  Pins Configuration Parameters
   *
   *  PortPins.
   */
  const Port_PinConfType * const    PortPins;

} Port_ConfigType;

#endif /* PORT_CFG_INTERNAL_H */

