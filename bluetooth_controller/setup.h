#ifndef __SETUP_H__
#define __SETUP_H__

/* LCD screen with image and color initialization */
void _graphicsInit();

/* UART module initialization to transmit with ESP */
void _uartInit();

/* ADC with manual sampling for joystick and accelerometer */
void _adcInit();

/* Standard hardware initialization */
void _hwInit();

/* Timer initialization to obtain constant 4Hz sampling frequency */
void _timerInit();

#endif /* __SETUP_H__ */
