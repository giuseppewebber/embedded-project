#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

/* Initial state function of the FSM */
void fn_INIT(void);

/* Selection menu state function of the FSM.
*  Chose gamemode on the first run.
*/
void fn_MENU_SEL(void);

/* Pause menu state function of the FSM.
*  Stop the game to change gamemode or quit the game.
*/
void fn_MENU_PAUSE(void);

/* Game state function of the FSM */
void fn_GAME(void);

#endif /* __STATEMACHINE_H__ */
