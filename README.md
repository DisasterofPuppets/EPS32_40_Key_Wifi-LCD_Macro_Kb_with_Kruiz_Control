![GitHub Logo](/images/lPrototype.jpg)
Format: ![Alt Text](url)

Disaster of Puppets
YouTube: Http://disasterofpuppets.com
Twitch: Https://twitch.tv/disasterofpuppets

A 40 Key macro keyboard running off an ESP32, using IRC messages to 
trigger commands in Kruiz Control and automate OBS Studio scenes etc.
LCD Screen shows the current button / Scene in play
Oh, and it's wireless

Using https://github.com/fredimachado/ArduinoIRC
Kruiz Control https://github.com/Kruiser8/Kruiz-Control

It is assumed you have already installed Kruiz-Control. If not refer to documentation from the link above.
It is also assumed you know how to install any required Arduino Libraries. See the below as a starting point.

For the ESP32 Board: https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
Generic Library addition: https://www.youtube.com/watch?v=M6PZOqNHKxM

**************************************************************************************

Required Materials:

- 40 x Cherry MX switches / your choice of Key switches.
Example: https://www.ebay.com.au/itm/70Pcs-3-Pin-Mechanical-Keyboard-Switch-Blue-Plate-Gateron-Keyboard-RGB-Series/233659187775?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649

- Button Caps - I printed my own and they are included as blanks or custom buttons below.

- ESP-32 ESP32S
Example: https://www.ebay.com.au/itm/ESP-32-ESP32S-Development-Board-2-4GHz-WiFi-Bluetooth-Antenna-CP2102-Module-AU/114199620604?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649

- 1602 16X2 LCD Display IIC/I2C/TWI/SPI Serial Interface Module
Example: https://www.ebay.com.au/itm/1602-16X2-LCD-Display-IIC-I2C-TWI-SPI-Serial-Interface-Module-For-Arduino/324135354058?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649

- 3D printer or access to someone who can print the files for you

**************************************************************************************

Step # 1
Complete the fields in Creds.h and save

Step # 2 
Print the base.stl and lid.stl files
I have also included BlankButtonMaster.3mf which should allow you to make most letter combinations for custom blank keys. 
If there is button label you are unable to make with this let me know and I should be able to update the file for future users.

Step # 3
Wire as per 40KeyWifiSDKCWiring.png

Step # 4
Change the button coding to your specific needs in ESP32TwitchMACROKB.ino

Step # 5
Using ExampleTriggers Code for Kruiz Control.txt insert the specific commands into Triggers.txt


