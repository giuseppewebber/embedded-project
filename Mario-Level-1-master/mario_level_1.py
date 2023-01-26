#!/usr/bin/env python
__author__ = 'justinarmstrong'

"""
This is an attempt to recreate the first level of
Super Mario Bros for the NES.
"""

import sys
import pygame as pg
from data.main import main
import cProfile
from pynput.keyboard import Key, Controller
import serial
import threading
import data.constants as c

"""
function that simulate keyboard pression according to the signals
received from Bluetooth.
Button are pressed and released to simulate a realistic behaviour.

"""
def thread_button(bt,keyboard):
    while True:
        #read data from Bluetooth
        data = int.from_bytes(bt.read(1),'big')
        #action
        if(data & c.bit0):
            keyboard.press('s')
        else :
            keyboard.release('s')   
        #jump
        if(data & c.bit1):
            keyboard.press('a')
        else :
            keyboard.release('a')
        #left
        if(data & c.bit2):
            keyboard.press(Key.left)
        else :
            keyboard.release(Key.left)
        #right
        if(data & c.bit3):
            keyboard.press(Key.right)
        else :
            keyboard.release(Key.right)
        #down
        if(data & c.bit4):
            keyboard.press(Key.down)
        else :
            keyboard.release(Key.down)
        #up
        if(data & c.bit5):
            keyboard.press(Key.up)
        else :
            keyboard.release(Key.up)
        #pause
        #bit_6 toggle to 1 only when the state changes
        if((data & c.bit6) and not previous_bit_6):
            if(not c.isPauseTime):
                keyboard.press(Key.esc)
                c.isPauseTime = True
            else :
                keyboard.press(Key.enter)
                c.isPauseTime = False
        else :
            keyboard.release(Key.esc)
            keyboard.release(Key.enter)
        #quit
        ##bit_7 toggle to 1 only when the quit selection is confermed on the controller
        if((data & c.bit7) and not previous_bit_7):
            bt.close()
            keyboard.press(Key.alt)
            keyboard.press(Key.f4)
        else :
            keyboard.release(Key.alt)
            keyboard.release(Key.f4)

        previous_bit_6 = data & c.bit6
        previous_bit_7 = data & c.bit7
        data = 0



if __name__=='__main__':
    #connect to the keyboard 
    keyboard = Controller()
    # Connect to the device
    BAUD_RATE = 9600
    s = serial.Serial()
    s.baudrate = BAUD_RATE
    s.port = 'COM8'
    s.open()
    #open a thread for keyboard simulation
    x = threading.Thread(target=thread_button, args=(s, keyboard))
    x.start()

    #unchanged program
    main()
    pg.quit()
    keyboard.release(Key.alt)
    keyboard.release(Key.f4)
    s.close()
    sys.exit()