#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <stdbool.h>

/*****************************************************************************
*
*    blink() - toggle the background and text on the start menu
*    
*    \parameter no input values needed
*
*    \return none            
*
*****************************************************************************/
void blink();


/*****************************************************************************
*
*    draw_select() - writes on selection menu screen
*   
*    \parameter no input values needed
*
*    \return none      
*
*****************************************************************************/
void draw_select();


/*****************************************************************************
*
*    clear_menu() - deletes selection graphics from menu 
*   
*    \parameter no input values needed
*
*    \return none      
*
*****************************************************************************/
void clear_menu();


/*****************************************************************************
*
*    draw_menu() - draws selection graphics from menu 
*   
*    \parameter no input values needed
*
*    \return none      
*
*****************************************************************************/
void draw_menu();


/*****************************************************************************
*
*    joystick_moved_up() - debouncing joystick up 
*   
*    \parameter no input values needed
*
*    \return bool: 
*               TRUE  when joystick is moved up
*               FALSE when joystick is holded up for const
*                     LIMIT number of cicles    
*
*****************************************************************************/
bool joystick_moved_up();


/*****************************************************************************
*
*    joystick_moved_down() - debouncing joystick down 
*   
*    \parameter no input values needed
*
*    \return bool: 
*               TRUE  when joystick is moved down
*               FALSE when joystick is holded down for const
*                     LIMIT number of cicles    
*
*****************************************************************************/
bool joystick_moved_down();


/*****************************************************************************
*
*    joystick_moved_dx() - debouncing joystick right 
*   
*    \parameter no input values needed
*
*    \return bool: 
*               TRUE  when joystick is moved right
*               FALSE when joystick is holded right for const
*                     LIMIT number of cicles    
*
*****************************************************************************/
bool joystick_moved_dx();


/*****************************************************************************
*
*    joystick_moved_sx() - debouncing joystick left 
*   
*    \parameter no input values needed
*
*    \return bool: 
*               TRUE  when joystick is moved left
*               FALSE when joystick is holded left for const
*                     LIMIT number of cicles    
*
*****************************************************************************/
bool joystick_moved_sx();


/*****************************************************************************
*
*    button3_pressed() - debouncing button 3.5 
*   
*    \parameter no input values needed
*
*    \return bool: 
*               TRUE  when button 3.5 is pressed
*               FALSE when button 3.5 is holded down for const
*                     LIMIT number of cicles    
*
*****************************************************************************/
bool button3_pressed();


/*****************************************************************************
*
*    button5_pressed() - debouncing button 5.1 
*   
*    \parameter no input values needed
*
*    \return bool: 
*               TRUE  when button 5.1 is pressed
*               FALSE when button 5.1 is holded down for const
*                     LIMIT number of cicles    
*
*****************************************************************************/
bool button5_pressed();


/*****************************************************************************
*
*    menu_selection() - keeps track of the cursor position in the
*                       pause and selection menu and calls the draw/clear 
*                       functions.
*                       Update the gamemode and menu state variables.
*   
*    \parameter no input values needed
*
*    \return none      
*
*****************************************************************************/
void menu_selection();


/*****************************************************************************
*
*    send_data() - sets the 8-bit data variable referring to controller's
*                  inputs and sends it to the ESP via UART
*   
*    \parameter no input values needed
*
*    \return none      
*
*****************************************************************************/
void send_data();

#endif /* __FUNCTIONS_H__ */
