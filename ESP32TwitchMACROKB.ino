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

//-------------EDIT in Creds.h----------
char ssid[] = WIFI_SSID;       // your network SSID (name)
char password[] = WIFI_PASS;  // your network key

//------------------------------


int led = LED_BUILTIN;
String ircChannel = "";

WiFiClient wiFiClient;
IRCClient client(IRC_SERVER, IRC_PORT, wiFiClient);

const byte ROWS = 6;
const byte COLS = 8;

char hexaKeys[ROWS][COLS] = 
{

    {'0', '1', '2', '3', '4', '5', '6', '7'},
    {'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'},
    {'G', 'H', 'I', 'J'},
    {'K', 'L', 'M', 'N'},
    {'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V'},
    {'W', 'X', 'Y', 'Z', '!', '@', '#', '$'},
};

byte rowPins[ROWS] = {28, 29, 30, 31, 32, 33};
byte colPins[COLS] = {13, 14, 15, 16, 17, 18, 19, 20};

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x3F for a 16 chars and 2 line display


// put your setup code here, to run once:
void setup() {

  pinMode(led, OUTPUT);

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
  
if (customKey){
     switch (customKey){
        case '0':

// LIVE
            // Send command to your bot to trigger the Kruiz Control command
            sendTwitchMessage("/w drpuppetmaster !live");
            //clearLCD
            lcd.setCursor(0,0);
            lcd.print("LIVE");
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
