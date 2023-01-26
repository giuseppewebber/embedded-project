/* --COPYRIGHT--,BSD
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include <stdbool.h>
#include "setup.h"
#include "images.h"
#include "constants.h"
#include "stateMachine.h"
#include "functions.h"

/* variables for tracking joystick position
*  0: default, 1: moved
*/
bool joystick_up = 0;
bool joystick_down = 0;
bool joystick_dx = 0;
bool joystick_sx = 0;

/* variables for tracking board position
*  0: default, 1: inclined
*/
bool acc_up = 0;
bool acc_down = 0;
bool acc_dx = 0;
bool acc_sx = 0;

/* variables for buttons 3.5, 5.1, 4.1(joystick) */
uint8_t button3, button5, buttonj;

/* indexes for debouncing functions */
int16_t iu = 0;
int16_t id = 0;
int16_t ix = 0;
int16_t is = 0;
int16_t i3 = 0;
int16_t i5 = 0;

/* index for blinking function */
int8_t iblink = 0;

/* variables for tracking gamemode
*  0: accelerometer, 1: joystick
*/
bool mode = 0;

/* variables for tracking changes between game and menu
*  0: default, 1: change
*/
bool state = 0;

/* variables for tracking end confirmation
*  0: default, 1: quit
*/
bool quit = 0;

/* variable for tracking pause menu states */
MENU menu = gamemode;

/* ADC results buffer */
static uint16_t resultsBuffer[4];

/* Graphic library context */
Graphics_Context g_sContext;

/* variable to hold current state */
State_t current_state = STATE_INIT;

/* architecture of the state machine */
StateMachine_t fsm[] = {
                      {STATE_INIT, fn_INIT},
                      {STATE_MENU_SEL, fn_MENU_SEL},
                      {STATE_MENU_PAUSE, fn_MENU_PAUSE},
                      {STATE_GAME, fn_GAME}
};

/*
 * Main function
 */
int main(void)
{
    /* system init */
    _hwInit();
    _timerInit();
    _graphicsInit();
    _adcInit();
    _uartInit();

    while(1)
    {
        PCM_gotoLPM0();                     //sleep mode
        ADC14_toggleConversionTrigger();    //start ADC conversion
        PCM_gotoLPM0();                     //sleep mode

        if(current_state < NUM_STATES){
            (*fsm[current_state].state_function)();     //call to FSM functions
        }
        else{
            /* error */
        }
        send_data();     //send data to ESP
    }
}

void ADC14_IRQHandler(void)
{
    joystick_up = 0;
    joystick_down = 0;
    joystick_dx = 0;
    joystick_sx = 0;
    acc_up = 0;
    acc_down = 0;
    acc_dx = 0;
    acc_sx = 0;

    uint64_t status;

    status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);

    /* ADC_MEM4 conversion completed */ 
    if(status & ADC_INT3)
    {
        button3 = GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN5);
        button5 = GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1);
        buttonj = GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN1);

        /* store ADC14 conversion results */
        resultsBuffer[0] = ADC14_getResult(ADC_MEM0);
        resultsBuffer[1] = ADC14_getResult(ADC_MEM1);
        resultsBuffer[2] = ADC14_getResult(ADC_MEM2);
        resultsBuffer[3] = ADC14_getResult(ADC_MEM3);

        /* digital to binary conversion of controller inputs*/
        if(resultsBuffer[3] > THR_J_UP){
            joystick_up = 1;
        }else if(resultsBuffer[3] < THR_J_DOWN){
            joystick_down = 1;
        }
        if(resultsBuffer[2] > THR_J_RIGHT){
            joystick_dx = 1;
        }else if(resultsBuffer[2] < THR_J_LEFT){
            joystick_sx = 1;
        }
        if(resultsBuffer[1] > THR_A_UP){
            acc_up = 1;
        }else if(resultsBuffer[1] < THR_A_DOWN){
            acc_down = 1;
        }
        if(resultsBuffer[0] > THR_A_RIGHT){
            acc_dx = 1;
        }else if(resultsBuffer[0] < THR_A_LEFT){
            acc_sx = 1;
        }
    }
}

void TA1_0_IRQHandler(){
    /* clear the timer pending interrupt flag */ 
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
}
