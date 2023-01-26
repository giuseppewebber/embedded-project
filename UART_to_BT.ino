#include <HardwareSerial.h>
#include "BluetoothSerial.h"
#include <Arduino.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
HardwareSerial SerialPort(2); // use UART2

void setup() 
{
    Serial.begin(9600);                                //9600 baud rate for terminal
    SerialPort.begin(115200, SERIAL_8N1, 16, 17);      //115200 baud rate for UART, port 16 RX, port 17 TX (not used)
    SerialBT.begin("ESP32test");                       //initialize Bluetooth device
}

void loop() 
{
    if(SerialPort.available())                        //control if a UART connection is established
    {
        int value = SerialPort.read();                //read value from UART
        SerialBT.write(value);                        //write on serial Bluetooth connection
    }
}