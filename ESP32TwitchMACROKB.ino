/*******************************************************************
Disaster of Puppets
YouTube: Http://disasterofpuppets.com
Twitch: Https://twitch.tv/disasterofpuppets

A 40 Key macro keyboard running off an ESP32, using IRC messages to 
trigger commands in Kruiz Control and automate OBS Studio scenes etc.
LCD Screen shows the current button / Scene in play
Oh, and it's wireless

Using https://github.com/fredimachado/ArduinoIRC
Kruiz Control https://github.com/Kruiser8/Kruiz-Control

 *******************************************************************/
#include <WiFi.h> 
#include <IRCClient.h>
#include "Creds.h"
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//this causes compiling errors

//-------------EDIT in Creds.h----------
char ssid[] = WIFI_SSID;       // your network SSID (name)
char password[] = WIFI_PASS;  // your network key

//------------------------------


int led = LED_BUILTIN;
String ircChannel = "";

WiFiClient wiFiClient;
IRCClient client(IRC_SERVER, IRC_PORT, wiFiClient);

int keypress = 100; // delay between keyboard press and release
const byte ROWS = 6;
const byte COLS = 8;

char hexaKeys[ROWS][COLS] = 
{

    {'0', '1', '2', '3', '4', '5', '6', '7'}, 
    {'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'},
    {'G', 'H', '~', '~', '~', '~', 'I', 'J'},
    {'K', 'L', '~', '~', '~', '~', 'M', 'N'},
    {'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V'},
    {'W', 'X', 'Y', 'Z', '!', '@', '#', '$'},
};

byte rowPins[ROWS] = {13, 14, 27, 26, 25, 33}; //13,14,27,26,25,33 
byte colPins[COLS] = {15,16,17,18,19,23,32,4}; // PINS 15,RX2,TX2,18,19,23,32,4

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x3F for a 16 chars and 2 line display


// put your setup code here, to run once:
void setup() {

  pinMode(led, OUTPUT);
 // Keyboard.begin();
  Serial.begin(115200);
  Serial.println();

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  ircChannel = "#" + twitchChannelName;

  client.setCallback(callback);

lcd.init(); // initialize the lcd
lcd.init();
// Print a message to the LCD.
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("KC Stream Deck");
lcd.setCursor(0,1);
lcd.print("Disasterofpuppets");


}

void loop() {

String Status = "WC : On  M: On";

  // Try to connect to chat. If it loses connection try again
  if (!client.connected()) {
    Serial.println("Attempting to connect to " + ircChannel );
    // Attempt to connect
    // Second param is not needed by Twtich
    if (client.connect(TWITCH_BOT_NAME, "", TWITCH_OAUTH_TOKEN)) {
      client.sendRaw("JOIN " + ircChannel);
      Serial.println("connected and ready to rock");
      //sendTwitchMessage("Ready to go Boss!");
    } else {
      Serial.println("failed... try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
    return;
  }
  client.loop();

//*********** Keypad Matrix *************
char customKey = customKeypad.getKey();

//Serial.println((int)customKey);
//delay(500);
  
if (customKey){
     switch (customKey){

// ROW 1-------------------------------------------        
        
case '0':

// LIVE
            // Send command to your bot to trigger the Kruiz Control command
            Serial.println("0");
            sendTwitchMessage("/w drpuppetmaster !Live");
            delay(keypress);
            lcd.clear();
            lcd.print("LIVE");
            lcd.setCursor(0,1);
            lcd.print(Status);
break;

case '1':
Serial.println("1");
delay(keypress);
break;


case '2':
Serial.println("2");
delay(keypress);
break;


case '3':
Serial.println("3");
delay(keypress);
break;


case '4':
Serial.println("4");
delay(keypress);
break;

case '5':
Serial.println("5");
delay(keypress);
break;

case '6':
Serial.println("6");
delay(keypress);
break;

// BRB
case '7':
Serial.println("7");
            
            sendTwitchMessage("/w drpuppetmaster !Brb");
            delay(keypress);
            lcd.clear();
            lcd.print("BRB");
            lcd.setCursor(0,1);
            lcd.print(Status);
            delay(keypress);
break;

// ROW 2 ---------------------------------

case '8':
Serial.println("8");
delay(keypress);
break;

case '9':
Serial.println("9");
delay(keypress);
break;

case 'A':
Serial.println("A");
delay(keypress);
break;

case 'B':
Serial.println("B");
delay(keypress);
break;

case 'C':
Serial.println("C");
delay(keypress);
break;

case 'D':
Serial.println("D");
delay(keypress);
break;

case 'E':
Serial.println("E");
delay(keypress);
break;

case 'F':
Serial.println("F");
delay(keypress);
break;

// ROW 3 ---------------------------------

case 'G':
Serial.println("G");
delay(keypress);
break;

case 'H':
Serial.println("H");
delay(keypress);
break;

case 'I':
Serial.println("I");
delay(keypress);
break;

// Media Play / Pause 
case 'J':
Serial.println("J");
            //Keyboard.press(KEY_F14);
            delay(keypress);
            //Keyboard.releaseAll();
delay(keypress);
break;            

// ROW 4 ---------------------------------

case 'K':
Serial.println("K");
delay(keypress);
break;

// Iphone Bot Cam
case 'L':
Serial.println("L");


            sendTwitchMessage("/w drpuppetmaster !Botcam");
            
            lcd.clear();
            lcd.print("BotCam");
            lcd.setCursor(0,1);
            lcd.print(Status);
delay(keypress);
break;

//Null

case '~':
Serial.println("~ NULL ~");
delay(keypress);
break;


case 'M':
Serial.println("M");
delay(keypress);
break;

case 'N':
Serial.println("N");
delay(keypress);
break;          

// ROW 5 ---------------------------------

case 'O':
Serial.println("O");
delay(keypress);
break;

case 'P':
Serial.println("P");
delay(keypress);
break;

case 'Q':
Serial.println("Q");
delay(keypress);
break;

case 'R':
Serial.println("R");
delay(keypress);
break;

case 'S':
Serial.println("S");
delay(keypress);
break;

case 'T':
Serial.println("T");
delay(keypress);
break;

case 'U':
Serial.println("U");
delay(keypress);
break;

case 'V':
Serial.println("V");
delay(keypress);
break;       

// ROW 6 ------------------------------

case 'W': 
Serial.println("W");
delay(keypress);
break;
          
case 'X':
Serial.println("X");
delay(keypress);
break;

case 'Y':
Serial.println("Y");
delay(keypress);
break;

case 'Z':
Serial.println("Z");
delay(keypress);
break;

case '!':
Serial.println("!");
delay(keypress);
break;   

case '@':
Serial.println("@");
delay(keypress);
break;   

case '#':
Serial.println("#");
delay(keypress);
break;   

// Mute
case '$':
Serial.println("$");

            sendTwitchMessage("/w drpuppetmaster !Mute");
            delay(keypress);
            lcd.clear();
            lcd.print("Mute");
            lcd.setCursor(0,1);
            lcd.print(Status);
delay(keypress);
break;
            
            
     }
  }
  
}

void sendTwitchMessage(String message) {
  client.sendMessage(ircChannel, message);
}


void callback(IRCMessage ircMessage) {
  //Serial.println("In CallBack");

  if (ircMessage.command == "PRIVMSG" && ircMessage.text[0] != '\001') {
    //Serial.println("Passed private message.");
    ircMessage.nick.toUpperCase();

    String message("<" + ircMessage.nick + "> " + ircMessage.text);

    //prints chat to serial
    Serial.println(message);

    for (int i = 0; i < 6; i++) {
      digitalWrite(led, HIGH);
      delay(50);
      digitalWrite(led, LOW);
      delay(25);
    }

    return;
  }
}
