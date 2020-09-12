Disaster of Puppets
YouTube: Http://disasterofpuppets.com
Twitch: Https://twitch.tv/disasterofpuppets

A 40 Key macro keyboard running off an ESP32, using IRC messages to 
trigger commands in Kruiz Control and automate OBS Studio scenes etc.
LCD Screen shows the current button / Scene in play
Oh, and it's wireless

Using https://github.com/fredimachado/ArduinoIRC
Kruiz Control https://github.com/Kruiser8/Kruiz-Control

Required Materials:

40 x Cherry MX switches / your choice of Key switches.
Example: 

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


