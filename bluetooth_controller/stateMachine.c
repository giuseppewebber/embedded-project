#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "constants.h"
#include "stateMachine.h"
#include "images.h"
#include "functions.h"

extern State_t current_state;

extern Graphics_Context g_sContext;

extern uint8_t button3, button5, buttonj;
extern MENU menu;
extern bool state;
extern bool quit;

void fn_INIT(){
    quit = 0;
    blink();
    if (button3_pressed() || button5_pressed()){
        Graphics_drawImage(&g_sContext, &MENU_SEL, 0, 0);
        draw_select();
        menu_selection();
        current_state = STATE_MENU_SEL;
    }
}

void fn_MENU_SEL(){
    menu_selection();
    if (menu == continua && button3_pressed() ){
        Graphics_drawImage(&g_sContext, &GAME, 0, 0);
        current_state = STATE_GAME;
    }
    if (menu == end && button3_pressed() ){
        Graphics_drawImage(&g_sContext, &GAME, 0, 0);
        current_state = STATE_INIT;
        quit = 1;
    }
}

void fn_GAME(){
    state = 0;
    if (!buttonj){
        Graphics_drawImage(&g_sContext, &MENU_IMAGE, 0, 0);
        menu_selection();
        current_state = STATE_MENU_PAUSE;
        state = 1;
    }
}

void fn_MENU_PAUSE(){
    state = 0;
    menu_selection();
    if (menu == continua && button3_pressed() ){
        Graphics_drawImage(&g_sContext, &GAME, 0, 0);
        current_state = STATE_GAME;
        state = 1;
    }
    if (menu == end && button3_pressed() ){
        Graphics_drawImage(&g_sContext, &GAME, 0, 0);
        current_state = STATE_INIT;
        state = 0;
        quit = 1;
    }
}
