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


// Don't forget to edit ExampleCreds.h and save as Creds.h
 *******************************************************************/
#include <WiFi.h> 
#include <IRCClient.h>
#include "Creds.h"
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

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

int keypress = 100; // delay between keypad press and release
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

LiquidCrystal_I2C lcd(0x27,16,2); 


// put your setup code here, to run once:
void setup() {

  pinMode(led, OUTPUT);
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

  //  sendTwitchMessage("/w Changemetoyourbotname !Live"); I would't rcommend. If you move around or disconnect it will switch to this on start up;
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("D.I.Y. Stream Deck");
    lcd.setCursor(0,1);
    lcd.print("@DOFPuppets");
    runonce = 1;
}

      //Uncomment below if you want a twitch chat message on connect
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
 
if (customKey){
     switch (customKey){

// ROW 1-------------------------------------------        


// Live   
    
  case '0':
    // Send command to your bot to trigger the Kruiz Control command
    Serial.println("0");
    sendTwitchMessage("/w Changemetoyourbotname !Live");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("PC / Live");
  break;

// Craft Desk

  case '1':
    Serial.println("1");
    sendTwitchMessage("/w Changemetoyourbotname !Craft");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Craft Desk");
  break;

// Craft Desk FullScreen Cam

  case '2':
    Serial.println("2");
    sendTwitchMessage("/w Changemetoyourbotname !Craft2");
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
    sendTwitchMessage("/w Changemetoyourbotname !Idle");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Idle");

  break;

//Disclaimer

  case '5':
    Serial.println("5");
    sendTwitchMessage("/w Changemetoyourbotname !Disclaimer");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Disclaimer");

  break;

// Zoom

  case '6':
    Serial.println("6");
    sendTwitchMessage("/w Changemetoyourbotname !Zoomies");
    delay(keypress);
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print("Zoom");


  break;

// BRB
  case '7':
    Serial.println("7");        
    sendTwitchMessage("/w Changemetoyourbotname !Brb");
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
    sendTwitchMessage("/w Changemetoyourbotname !FSCam");
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
    sendTwitchMessage("/w Changemetoyourbotname !PB");
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
    sendTwitchMessage("/w Changemetoyourbotname !red");
    delay(keypress);
  break;

//Green
  case 'D':
    Serial.println("D");
    sendTwitchMessage("/w Changemetoyourbotname !green");
    delay(keypress);
  break;

//Blue
  case 'E':
    Serial.println("E");
    sendTwitchMessage("/w Changemetoyourbotname !blue");
    delay(keypress);
  break;

//DoorPrize
  case 'F':
    Serial.println("F");
    sendTwitchMessage("/w Changemetoyourbotname !Door");
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
      sendTwitchMessage("/w Changemetoyourbotname !Logitechhide");
      delay(keypress);
      logi = 0;
    }
    else if (!logi) {
      sendTwitchMessage("/w Changemetoyourbotname !Logitechshow");
      delay(keypress);
      logi = 1;     
    }
    break;

// Panasonic Cam Toggle

  case 'H':
    Serial.println("H");
    if (panacam) {
      sendTwitchMessage("/w Changemetoyourbotname !Panahide");
      delay(keypress);
      panacam = 0;
    }
    else if (!panacam) {
      sendTwitchMessage("/w Changemetoyourbotname !Panashow");
      delay(keypress);
      panacam = 1;     
    }
    break;
    
// Spare

  case 'I':
    Serial.println("I");
    delay(keypress);
  break;

// Spare

  case 'J':
    Serial.println("J");
    delay(keypress);
    break;            
    
// ROW 4 ---------------------------------


//Iphone Desk Cam Toggle

  case 'K':
    Serial.println("K");
    if (cdcam) {
      sendTwitchMessage("/w Changemetoyourbotname !CDhide");
      delay(keypress);
      cdcam = 0;
    }
    else if (!cdcam) {
      sendTwitchMessage("/w Changemetoyourbotname !CDshow");
      delay(keypress);
      cdcam = 1;     
    }
    break;

// Iphone Bot Cam Toggle
  
  case 'L':
    Serial.println("L");
    if (botscam) {
      sendTwitchMessage("/w Changemetoyourbotname !bothide");
      delay(keypress);
      botscam = 0;
    }
    else if (!botscam) {
      sendTwitchMessage("/w Changemetoyourbotname !botshow");
      delay(keypress);
      botscam = 1;     
    }
    break;

//Nulls

  case '~':
    Serial.println("~ NULL ~");
    delay(keypress);
  break;

// Spare

  case 'M':
    Serial.println("M");
    delay(keypress);
  break;

// Spare

  case 'N':
    Serial.println("N");
    delay(keypress);
  break;          

// ROW 5 ---------------------------------

// Stamp

  case 'O':
    Serial.println("O");
    sendTwitchMessage("/w Changemetoyourbotname !Stamp");
    delay(keypress);
  break;

// BS

  case 'P':
    Serial.println("P");
    sendTwitchMessage("/w Changemetoyourbotname !BS");
    delay(keypress);
  break;

// KISS

  case 'Q':
    Serial.println("Q");
    sendTwitchMessage("/w Changemetoyourbotname !Kiss");
    delay(keypress);
  break;

//PUN

  case 'R':
    Serial.println("R");
    sendTwitchMessage("/w Changemetoyourbotname !Pun");
    delay(keypress);
  break;

// Who are these people?

  case 'S':
    Serial.println("S");
    sendTwitchMessage("/w Changemetoyourbotname !Who");
    delay(keypress);
  break;

// I disagree

  case 'T':
    Serial.println("T");
    sendTwitchMessage("/w Changemetoyourbotname !Disagree");
    delay(keypress);
  break;

// Sexytimes

  case 'U':
    Serial.println("U");
    sendTwitchMessage("/w Changemetoyourbotname !Sex");
    delay(keypress);
  break;

// Why is / isn't it working gif?

  case 'V':
    Serial.println("V");
    sendTwitchMessage("/w Changemetoyourbotname !Why");
    delay(keypress);
  break;       

// ROW 6 ------------------------------

// GG

  case 'W': 
    Serial.println("W");
    sendTwitchMessage("/w Changemetoyourbotname !Goodgame");
    delay(keypress);
  break;

// McScuse me          

  case 'X':
    Serial.println("X");
    sendTwitchMessage("/w Changemetoyourbotname !McScuseme");
    delay(keypress);
  break;

// Cheese it

  case 'Y':
    Serial.println("Y");
    sendTwitchMessage("/w Changemetoyourbotname !Cheeseit");
    delay(keypress);
  break;

// Tech support

  case 'Z':
    Serial.println("Z");
    sendTwitchMessage("/w Changemetoyourbotname !TechCall");
    delay(keypress);
  break;

// Sthap it

  case '!':
    Serial.println("!");
    sendTwitchMessage("/w Changemetoyourbotname !Sthapit");
    delay(keypress);
  break;   

// Phrasing

  case '@':
    Serial.println("@");
    sendTwitchMessage("/w Changemetoyourbotname !Phrasing");
    delay(keypress);
  break;   

// Kruiz Control Reset

  case '#':
    Serial.println("#");
    sendTwitchMessage("/w Changemetoyourbotname !Reset");
    delay(keypress);
  break;   

// Mute

  case '$':
    Serial.println("$");
    if (muted) {
      sendTwitchMessage("/w Changemetoyourbotname !Mute");
      delay(keypress);
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print("***MUTED***");
      muted = 0;
    }
    else if (!muted) {
      sendTwitchMessage("/w Changemetoyourbotname !UnMute");
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
