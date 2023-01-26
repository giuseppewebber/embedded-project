/* 
 * File containing the bitmap images used for the different LCD screens during the game.
 * The bitmap images are included in a struct with dimensions and color palette.
 */

#ifndef __IMAGES_H__
#define __IMAGES_H__

#include <ti/grlib/grlib.h>

/* colors used */
#define WHITE_COLOR 0xffffff
#define BLACK_COLOR 0x000000

/* dimension of the image */
#define WIDTH 128
#define HEIGHT 128

/* number of colors */
#define N_COLOR 2

/* game image */
extern const tImage GAME;

/* pause menu image */
extern const tImage MENU_IMAGE;

/* gamemode selection menu image */
extern const tImage MENU_SEL;

#endif /* __IMAGES_H__ */
