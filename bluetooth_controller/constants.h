#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"

/* effective values for joystick in a neutral position */
#define CENTER_J_X 8100
#define CENTER_J_Y 8900

/* effective values for accelerometer in a neutral position */
#define CENTER_A_X 8250
#define CENTER_A_Y 8300

/* threshold values for logic input convertion of the joystick */
#define THR_J 3000
#define THR_J_UP CENTER_J_Y + THR_J
#define THR_J_DOWN CENTER_J_Y - THR_J
#define THR_J_RIGHT CENTER_J_X + THR_J
#define THR_J_LEFT CENTER_J_X - THR_J

/* threshold values for logic input convertion of the accelerometer */
#define THR_A 1000
#define THR_A_UP CENTER_A_Y + THR_A
#define THR_A_DOWN CENTER_A_Y - THR_A
#define THR_A_RIGHT CENTER_A_X + THR_A
#define THR_A_LEFT CENTER_A_X - THR_A

/* one hot encoding of controller's inputs for UART communication to the ESP32 */
#define MASK_ACTION     0b00000001
#define MASK_JUMP       0b00000010
#define MASK_LEFT       0b00000100
#define MASK_RIGHT      0b00001000
#define MASK_DOWN       0b00010000
#define MASK_UP         0b00100000
#define MASK_PAUSE      0b01000000
#define MASK_QUIT       0b10000000

/* value to obtain a timer frequency of 4Hz*/       /*EDIT: da rivedere*/
#define TIMER_PERIOD    0x2DC6

/* software debounce value */
#define LIMIT 5

/* blinking frequency divider */       /*EDIT: da rivedere*/
#define BLINK_DIV 10

/* pause menu states */
typedef enum{
    gamemode,
    continua,
    end
}MENU;

/******************************************************************
* coordinates value for pause menu graphic */
extern const Graphics_Rectangle rectangle_A;

extern const Graphics_Rectangle rectangle_A1;

extern const Graphics_Rectangle rectangle_J;

extern const Graphics_Rectangle rectangle_J1;

/*******************************************************************/

/* timer configuration */
extern const Timer_A_UpModeConfig upConfig;

/* UART configuration*/
extern const eUSCI_UART_ConfigV1 uartConfig;

/******************************************************************
* definition of the Finite State Machine structure */
typedef enum {
    STATE_INIT,
    STATE_MENU_SEL,
    STATE_MENU_PAUSE,
    STATE_GAME,
    NUM_STATES
}State_t;

typedef struct{
    State_t state;
    void (*state_function)(void);
} StateMachine_t;
/*******************************************************************/

#endif  /* __CONSTANTS_H__ */
