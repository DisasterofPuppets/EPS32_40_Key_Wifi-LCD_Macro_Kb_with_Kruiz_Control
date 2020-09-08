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

bool muted = 1;
bool logi = 1;
bool cdcam = 1;
bool panacam = 1;
bool botscam = 1;
int led = LED_BUILTIN;
String ircChannel = "";
int runonce = 0;
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

}

void loop() {

  // Try to connect to chat. If it loses connection try again
  if (!client.connected()) {
    Serial.println("Attempting to connect to " + ircChannel );
    // Attempt to connect
    // Second param is not needed by Twtich
    if (client.connect(TWITCH_BOT_NAME, "", TWITCH_OAUTH_TOKEN)) {
      client.sendRaw("JOIN " + ircChannel);
      Serial.println("connected and ready to rock");

if (runonce == 0){
//run your default state here, eg I duplicated button 1's functionality

    sendTwitchMessage("/w drpuppetmaster !Live");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("PC / Live");
    runonce = 1;
}

      
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

//Serial.print("Muted State: ");
//Serial.println(muted);

  
if (customKey){
     switch (customKey){

// ROW 1-------------------------------------------        


// Live   
    
  case '0':
    // Send command to your bot to trigger the Kruiz Control command
    Serial.println("0");
    sendTwitchMessage("/w drpuppetmaster !Live");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("PC / Live");
  break;

// Craft Desk

  case '1':
    Serial.println("1");
    sendTwitchMessage("/w drpuppetmaster !Craft");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Craft Desk");
  break;

// Craft Desk FullScreen Cam

  case '2':
    Serial.println("1");
    sendTwitchMessage("/w drpuppetmaster !Craft2");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Craft FaceCam");
  break;

// Spare

  case '3':
    Serial.println("3");
    delay(keypress);
  break;

// Idle

  case '4':
    Serial.println("4");
    sendTwitchMessage("/w drpuppetmaster !Idle");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Idle");

  break;

//Disclaimer

  case '5':
    Serial.println("5");
    sendTwitchMessage("/w drpuppetmaster !Disclaimer");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Disclaimer");

  break;

// Zoom

  case '6':
    Serial.println("6");
    sendTwitchMessage("/w drpuppetmaster !Zoomies");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Zoom");


  break;

// BRB
  case '7':
    Serial.println("7");        
    sendTwitchMessage("/w drpuppetmaster !Brb");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("BRB");

  break;

// ROW 2 ---------------------------------

// Fullscreen PC Webcam

  case '8':
    Serial.println("8");
    sendTwitchMessage("/w drpuppetmaster !FSCam");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("FS Cam");

  break;

//Spare

  case '9':
    Serial.println("9");
    delay(keypress);
  break;

// Dodgy Paintbrush Time
  case 'A':
    Serial.println("A");
    sendTwitchMessage("/w drpuppetmaster !PB");
    delay(keypress);           
  break;

//Spare
  case 'B':
    Serial.println("B");
    delay(keypress);
  break;

//Red
  case 'C':
    Serial.println("C");
    sendTwitchMessage("/w drpuppetmaster !red");
    delay(keypress);
  break;

//Green
  case 'D':
    Serial.println("D");
    sendTwitchMessage("/w drpuppetmaster !green");
    delay(keypress);
  break;

//Blue
  case 'E':
    Serial.println("E");
    sendTwitchMessage("/w drpuppetmaster !blue");
    delay(keypress);
  break;

//DoorPrize
  case 'F':
    Serial.println("F");
    sendTwitchMessage("/w drpuppetmaster !Door");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Door Prize");
  break;

// ROW 3 ---------------------------------

// Logitech Webcam Toggle

  case 'G':
    Serial.println("G");
    if (logi) {
      sendTwitchMessage("/w drpuppetmaster !Logitechhide");
      delay(keypress);
      logi = 0;
    }
    else if (!logi) {
      sendTwitchMessage("/w drpuppetmaster !Logitechshow");
      delay(keypress);
      logi = 1;     
    }
    break;

// Panasonic Cam Toggle

  case 'H':
    Serial.println("H");
    if (panacam) {
      sendTwitchMessage("/w drpuppetmaster !Panahide");
      delay(keypress);
      panacam = 0;
    }
    else if (!panacam) {
      sendTwitchMessage("/w drpuppetmaster !Panashow");
      delay(keypress);
      panacam = 1;     
    }
    break;
    
// Spare

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
    break;            
    
// ROW 4 ---------------------------------


//Iphone Desk Cam Toggle

  case 'K':
    Serial.println("K");
    if (cdcam) {
      sendTwitchMessage("/w drpuppetmaster !CDhide");
      delay(keypress);
      cdcam = 0;
    }
    else if (!cdcam) {
      sendTwitchMessage("/w drpuppetmaster !CDshow");
      delay(keypress);
      cdcam = 1;     
    }
    break;

// Iphone Bot Cam Toggle
  
  case 'L':
    Serial.println("L");
    if (botscam) {
      sendTwitchMessage("/w drpuppetmaster !bothide");
      delay(keypress);
      botscam = 0;
    }
    else if (!botscam) {
      sendTwitchMessage("/w drpuppetmaster !botshow");
      delay(keypress);
      botscam = 1;     
    }
    break;

//Nulls

  case '~':
    Serial.println("~ NULL ~");
    delay(keypress);
  break;

// Media Key Previous Track

  case 'M':
    Serial.println("M");
    delay(keypress);
  break;

// Media Key Next Track

  case 'N':
    Serial.println("N");
    delay(keypress);
  break;          

// ROW 5 ---------------------------------

// Stamp

  case 'O':
    Serial.println("O");
    sendTwitchMessage("/w drpuppetmaster !Stamp");
    delay(keypress);
  break;

// BS

  case 'P':
    Serial.println("P");
    sendTwitchMessage("/w drpuppetmaster !BS");
    delay(keypress);
  break;

// KISS

  case 'Q':
    Serial.println("Q");
    sendTwitchMessage("/w drpuppetmaster !Kiss");
    delay(keypress);
  break;

//PUN

  case 'R':
    Serial.println("R");
    sendTwitchMessage("/w drpuppetmaster !Pun");
    delay(keypress);
  break;

// Who are these people?

  case 'S':
    Serial.println("S");
    sendTwitchMessage("/w drpuppetmaster !Who");
    delay(keypress);
  break;

// I disagree

  case 'T':
    Serial.println("T");
    sendTwitchMessage("/w drpuppetmaster !Disagree");
    delay(keypress);
  break;

// Sexytimes

  case 'U':
    Serial.println("U");
    sendTwitchMessage("/w drpuppetmaster !Sex");
    delay(keypress);
  break;

// Why is / isn't it working gif?

  case 'V':
    Serial.println("V");
    sendTwitchMessage("/w drpuppetmaster !Why");
    delay(keypress);
  break;       

// ROW 6 ------------------------------

// GG

  case 'W': 
    Serial.println("W");
    sendTwitchMessage("/w drpuppetmaster !Goodgame");
    delay(keypress);
  break;

// McScuse me          

  case 'X':
    Serial.println("X");
    sendTwitchMessage("/w drpuppetmaster !McScuseme");
    delay(keypress);
  break;

// Cheese it

  case 'Y':
    Serial.println("Y");
    sendTwitchMessage("/w drpuppetmaster !Cheeseit");
    delay(keypress);
  break;

// Tech support

  case 'Z':
    Serial.println("Z");
    sendTwitchMessage("/w drpuppetmaster !TechCall");
    delay(keypress);
  break;

// Sthap it

  case '!':
    Serial.println("!");
    sendTwitchMessage("/w drpuppetmaster !Sthapit");
    delay(keypress);
  break;   

// Phrasing

  case '@':
    Serial.println("@");
    sendTwitchMessage("/w drpuppetmaster !Phrasing");
    delay(keypress);
  break;   

// Kruiz Control Reset

  case '#':
    Serial.println("#");
    sendTwitchMessage("/w drpuppetmaster !Reset");
    delay(keypress);
  break;   

// Mute

  case '$':
    Serial.println("$");
    if (muted) {
      sendTwitchMessage("/w drpuppetmaster !Mute");
      delay(keypress);
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("***MUTED***");
      muted = 0;
    }
    else if (!muted) {
      sendTwitchMessage("/w drpuppetmaster !UnMute");
      delay(keypress);
      lcd.setCursor(0,1);
      lcd.print("                ");
      muted = 1;     
    }
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
