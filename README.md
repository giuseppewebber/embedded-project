# <strong> Bluetooth Controller </strong>

The goal of the project is to create a bluetooth controller that allows us to play 
a computer game using a joystick or an accelerometer. </br>
In our case we are playing Super Mario, but with a couple of adjustments in the code 
we can potentially play any game that can run on python. 


# <strong> Table of Contents </strong>
1. [Requirements](#requirements)
2. [Project Layout](#project-layout)
3. [Getting Started](#getting-started)
4. [Code Highlights Explanation](#code-highlights-explanation)
5. [Video and Presentation](#video-and-presentation)
6. [Team Members](#team-members)
7. [References](#references)


# <strong> Requirements </strong> 

## Hardware Requirements

- [MSP432P401R](non trovo il link della Texas per la nostra scheda): which is the main board that process all the data;
- [Educational booster pack MKII](https://www.ti.com/tool/BOOSTXL-EDUMKII?keyMatch=&tisearch=search-everything&usecase=hardware): which is the board with an LCD screen, a joystick, 
buttons and the accelerometer that will act as the controller;
- [ESP32](volendo si può aggiungere il link dal quale lo abbiamo comprato): which is the board able to output the bluetooth signal to the main computer;
- Either a power-bank or a battery and a 5V power module to allow a stable power supply to the two boards;
- 3 jumper wires, and eventually a breadboard to make more efficient connections;
- A computer with a serial bluetooth port.

## Software Requirements



- Arduino to program the ESP32; 
- CCS to run the MSP code;
- An IDE with Python updated to pi-3.10.7 version;
- Some libraries that are going to be included in the README later


# <strong> Project Layout </strong> 

<pre><code>Mario_bluetooth_controller
├── 
│	├── 
│	├── 
│	├── 
├── 
├── 
└
</code></pre>


# <strong> Getting Started </strong>

## Hardware setup

- Attach the 2 boards paying attention to the pin order
- Connect as shown the main board to the power supply and to the ESP32 (after programming it)

![Board_front](/Board_front.jpeg)
![Board_back](/Board_back.jpg)

## Software setup

- First of all program the ESP32 with the Arduino code, in order to do it be sure to have (libraries);
- Plug the MSP432 to the computer and program it via CCS, be sure to have (libraries);
- Open the Python code, install the following libraries (), launch the game and be ready to play.


# <strong> Code Highlights Explanation </strong>

## Python Additions

We decided to create a one-hot encoding to differentiate the different inputs that the user can tnsmit to the game.

<pre><code>bit0 = 0b00000001       #bit0 action
bit1 = 0b00000010       #bit1 jump
bit2 = 0b00000100       #bit2 left
bit3 = 0b00001000       #bit3 right
bit4 = 0b00010000       #bit4 down
bit5 = 0b00100000       #bit5 up
bit6 = 0b01000000       #bit6 pause
bit7 = 0b10000000       #bit7 quit
</code></pre>


Through the block of code below, we are able to receive inputs via bluetooth and consequently emulate the pressure of the keyboard keys, based on the value of the signal we receive.

<pre><code>def thread_button(bt,keyboard):
    while True:
        #read data from Bluetooth
        data = int.from_bytes(bt.read(1),'big')

        #action
        if(data & c.bit0):
            keyboard.press('s')
        else :
            keyboard.release('s')  
        
        #same thing for "jump, left, right, down and up" inputs

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
        previous_bit_7 = data & c.bit7</code></pre>  


# <strong> Video and Presentation </strong>

[Presentation slides](inserire link pp google) </p>
[YouTube demo video](inserire link yt)</p>


# <strong> Team Members </strong>

The project was carried out by the collaboration of 3 people, mainly the work was made in common; 
in particular then each member took care of a specific part.

Giuseppe Webber:

Givanni Solfa:

Alessandro Gianluca Cazzaniga:

# <strong> References </strong>

We didn't create Mario's level from scratch, but we took [this github project](https://github.com/justinmeister/Mario-Level-1) and modified a couple of things to be able to receive inputs via bluetooth

