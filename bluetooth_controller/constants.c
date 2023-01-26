#include "constants.h"

/******************************************************************
* coordinates value for pause menu graphic */
const Graphics_Rectangle rectangle_A =
{
    71,          //!< The minimum X coordinate of the rectangle.
    46,            //!< The minimum Y coordinate of the rectangle.
    115,           //!< The maximum X coordinate of the rectangle.
    86,           //!< The maximum Y coordinate of the rectangle.
};

const Graphics_Rectangle rectangle_A1 =
{
    72,          //!< The minimum X coordinate of the rectangle.
    47,            //!< The minimum Y coordinate of the rectangle.
    114,           //!< The maximum X coordinate of the rectangle.
    85,           //!< The maximum Y coordinate of the rectangle.
};

const Graphics_Rectangle rectangle_J =
{
    13,          //!< The minimum X coordinate of the rectangle.
    46,            //!< The minimum Y coordinate of the rectangle.
    57,           //!< The maximum X coordinate of the rectangle.
    86,           //!< The maximum Y coordinate of the rectangle.
};

const Graphics_Rectangle rectangle_J1 =
{
    14,          //!< The minimum X coordinate of the rectangle.
    47,            //!< The minimum Y coordinate of the rectangle.
    56,           //!< The maximum X coordinate of the rectangle.
    85,           //!< The maximum Y coordinate of the rectangle.
};

/*******************************************************************/

/* timer configuration */
const Timer_A_UpModeConfig upConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_64,         // SMCLK/64 = 46.875kHz
        TIMER_PERIOD,                           // to have 1/4 sec          /*EDIT: da rivedere*/
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // Clear value
};

/******************************************************************/

/* UART configuration*/
const eUSCI_UART_ConfigV1 uartConfig =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,                 // SMCLK Clock Source
        13,                                             // BRDIV = 13
        0,                                              // UCxBRF = 0
        37,                                             // UCxBRS = 37
        EUSCI_A_UART_NO_PARITY,                         // No Parity
        EUSCI_A_UART_LSB_FIRST,                         // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,                      // One stop bit
        EUSCI_A_UART_MODE,                              // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
        EUSCI_A_UART_8_BIT_LEN                          // 8 bit data length
};

/******************************************************************/
