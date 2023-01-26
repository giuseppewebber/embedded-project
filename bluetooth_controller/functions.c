#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "functions.h"
#include "constants.h"
#include "images.h"

extern bool joystick_up;
extern bool joystick_down;
extern bool joystick_dx;
extern bool joystick_sx;

extern bool acc_up;
extern bool acc_down;
extern bool acc_dx;
extern bool acc_sx;

extern uint8_t button3, button5;

extern Graphics_Context g_sContext;

extern int16_t iu, id, ix, is, i3, i5;
extern int8_t iblink;

extern bool mode;
extern bool state;
extern bool quit;
extern MENU menu;

void blink(){
    if(iblink==0){
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_drawStringCentered(&g_sContext,
                                        (int8_t *)"Press a button",
                                        AUTO_STRING_LENGTH,
                                        64,
                                        74,
                                        OPAQUE_TEXT);

        Graphics_drawStringCentered(&g_sContext,
                                        (int8_t *)"to play",
                                        AUTO_STRING_LENGTH,
                                        64,
                                        84,
                                        OPAQUE_TEXT);
    }
    if(iblink==BLINK_DIV){
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
        Graphics_drawStringCentered(&g_sContext,
                                        (int8_t *)"Press a button",
                                        AUTO_STRING_LENGTH,
                                        64,
                                        74,
                                        OPAQUE_TEXT);

        Graphics_drawStringCentered(&g_sContext,
                                        (int8_t *)"to play",
                                        AUTO_STRING_LENGTH,
                                        64,
                                        84,
                                        OPAQUE_TEXT);
    }
    iblink++;
    if(iblink==BLINK_DIV*2){
        iblink=0;
    }
}

/*************************************************************************/

void draw_select(){
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)"Select",
                                    AUTO_STRING_LENGTH,
                                    64,
                                    20,
                                    OPAQUE_TEXT);
    Graphics_drawStringCentered(&g_sContext,
                                    (int8_t *)"Game Mode",
                                    AUTO_STRING_LENGTH,
                                    64,
                                    29,
                                    OPAQUE_TEXT);
}

/*************************************************************************/

void clear_menu(){
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_drawRectangle(&g_sContext, &rectangle_J);
    Graphics_drawRectangle(&g_sContext, &rectangle_J1);
    Graphics_drawRectangle(&g_sContext, &rectangle_A);
    Graphics_drawRectangle(&g_sContext, &rectangle_A1);
    Graphics_fillCircle(&g_sContext, 33, 114, 2);
    Graphics_fillCircle(&g_sContext, 33, 98, 2);
}

/*************************************************************************/

void draw_menu(){
    if(menu == gamemode){
        if(mode == 0){
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawRectangle(&g_sContext, &rectangle_A);
            Graphics_drawRectangle(&g_sContext, &rectangle_A1);
        }else{
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawRectangle(&g_sContext, &rectangle_J);
            Graphics_drawRectangle(&g_sContext, &rectangle_J1);
        }
    }
    if(menu == continua){
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_fillCircle(&g_sContext, 33, 98, 2);
        if(mode == 0){
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawRectangle(&g_sContext, &rectangle_A);
        }else{
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawRectangle(&g_sContext, &rectangle_J);
        }
    }
    if(menu == end){
        Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
        Graphics_fillCircle(&g_sContext, 33, 114, 2);
        if(mode == 0){
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawRectangle(&g_sContext, &rectangle_A);
        }else{
            Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
            Graphics_drawRectangle(&g_sContext, &rectangle_J);
        }
    }
}

/*************************************************************************/

bool joystick_moved_up(){
    if((joystick_up) && (iu==0)){
        iu++;
        return true;
    }
    if(joystick_up){
        iu++;
        if(iu>LIMIT){
            iu=0;
        }
    }else{
        iu=0;
    }
    return false;
}

/*************************************************************************/

bool joystick_moved_down(){
    if((joystick_down) && (id==0)){
        id++;
        return true;
    }
    if(joystick_down){
        id++;
        if(id>LIMIT){
            id=0;
        }
    }else{
        id=0;
    }
    return false;
}

/*************************************************************************/

bool joystick_moved_dx(){
    if((joystick_dx) && (ix==0)){
        ix++;
        return true;
    }
    if(joystick_dx){
        ix++;
        if(ix>LIMIT){
            ix=0;
        }
    }else{
        ix=0;
    }
    return false;
}

/*************************************************************************/

bool joystick_moved_sx(){
    if((joystick_sx) && (is==0)){
        is++;
        return true;
    }
    if(joystick_sx){
        is++;
        if(is>LIMIT){
            is=0;
        }
    }else{
        is=0;
    }
    return false;
}

/*************************************************************************/

bool button3_pressed(){
    if((!button3) && (i3==0)){
        i3++;
        return true;
    }
    if(!button3){
        i3++;
        if(i3>LIMIT){
            i3=0;
        }
    }else{
        i3=0;
    }
    return false;
}

/*************************************************************************/

bool button5_pressed(){
    if((!button5) && (i5==0)){
        i5++;
        return true;
    }
    if(!button5){
        i5++;
        if(i5>LIMIT){
            i5=0;
        }
    }else{
        i5=0;
    }
    return false;
}

/*************************************************************************/

void menu_selection(){
    draw_menu();
    if(joystick_moved_up()){
        clear_menu();
        if(menu == gamemode){
            menu = end;
            draw_menu();
        }else{
            menu = menu-1;
            draw_menu();
        }
    }
    if(joystick_moved_down()){
        clear_menu();
        if(menu == end){
            menu = gamemode;
            draw_menu();
        }else{
            menu = menu+1;
            draw_menu();
        }
    }
    if(menu == gamemode){
        if(joystick_moved_dx()){
            mode = 0;
            clear_menu();
            draw_menu();
        }
        if(joystick_moved_sx()){
            mode = 1;
            clear_menu();
            draw_menu();
        }
    }
}

/*************************************************************************/

void send_data(){
    uint8_t txdata = 0;

    if(state){
        txdata |= MASK_PAUSE;
    }
    if(quit){
        txdata |= MASK_QUIT;
    }

    if(mode){
        //MODE JOYSTICK
        if(joystick_up){
            txdata |= MASK_UP;
        }
        if(joystick_down){
            txdata |= MASK_DOWN;
        }
        if(joystick_dx){
            txdata |= MASK_RIGHT;
        }
        if(joystick_sx){
            txdata |= MASK_LEFT;
        }
        if(!button3){
            txdata |= MASK_JUMP;
        }
        if(!button5){
            txdata |= MASK_ACTION;
        }
    }else{
        //MODE ACCELEROMETER
        if(acc_up){
            txdata |= MASK_UP;
        }
        if(acc_down){
            txdata |= MASK_DOWN;
        }
        if(acc_dx){
            txdata |= MASK_RIGHT;
        }
        if(acc_sx){
            txdata |= MASK_LEFT;
        }
        if(!button3){
            txdata |= MASK_JUMP;
        }
        if(!button5){
            txdata |= MASK_ACTION;
        }
    }
    UART_transmitData(EUSCI_A2_BASE, txdata);
}
