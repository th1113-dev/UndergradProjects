/*
Authour: Theodis Hill
UID: 118983264
Title: Zephyr_broker
Description: The broker is asking for data from the OPTA 1 via MQTT

As of now this code is entirely theoretical because I cannot for the life of me get zephyr to work. 
Personally, I probably should've asked about this along with all of the communinication bus stuff.
Whether or not I can get it working (Or if any of this is real), I'm gonna make my best attempt here.
*/


#include <zephyr/kernel.h >
#include <Arduino.h>
#include <LiquidCrystal.h>
// #Include <Wifiprotocol.h>
// char ssid[] = Quanser_UVS
// char pass[] = UVS_wifi
// char IP [] = 192.168.2.241


/* My zephyr isn't working as of now. I'm going to try to make code that at lease represents my intention. 
Here is my plan:
1) Define everything according to how zephyr might read it and set up wifi for the board
2) Define a structure for the shared data using the example from the lab document
3) Define all of my threads that are necessary (LCD updater that works outside of a loop, SHT20 reader) 
If I have time, I will do everythin in my power to get zephyr working after this is built out enough
*/

//Step one: Inititalize all pins and stuff
/* Pseudocode:
defining:
Define board led, A and B inputs for the RS485 shield, LCD pins
set up LCD
*/
#define BUILTIN_LED_PIN 13 //Define the board LED
#define RS485_RE 2 // Finding out how to initialize the pins for the SHT20
#define RS485_DE 3 
#define RS_PIN 11
#define EN_PIN 10
#define D4_PIN 9
#define D5_PIN 8
#define D6_PIN 7
#define D7_PIN 6

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Step three: define shared values from OPTA 1

//this is from the example in the lab. It seems to be missing something for the value of temperature
// This seems like it wants to read the outputs from the SHT20
struct SystemState {
  float current_mA;
  float temp;
  struct k_mutex mutex;
}

struct SystemState state;

void task_modbus (void){ 

  k_mutex_init(&state.mutex);

  while(1){
    float [val1, val2] = readModbus() // I know this is dumb, but it's a placeholder for when I either figure out that
    //  mA can be converted to voltage or if I can find a way to split the value so that I can get the temp and mA
    // ... I'm pretty sure there is a conversion in the manual however that I've overlooked 10 times however
    k_mutex_lock (&state.mutex, , K_FOREVER);
    state.current_mA = val1;
    state.temp = val2
    k_mutex_unlock(&state.mutex);

    digitalWrite(BUILTIN_LED_PIN, HIGH);

    k_msleep(100);

    digitalWrite(BUILTIN_LED_PIN, LOW); // I put the heartbeat here... Maybe this is dumb, but I figure:
    // If it blinks quickly, that means the data was recieved.
  }
}

//Step three: initialize functions within the code using handles and thread handles (Though I'm starting to suspect thread handles are made weird here if at all)

//LCD
void ScrollLCD(void){
// Following code is from Arduino examples - Auto Scroll
// I'm trying to fix it to suit the needs of the code so it can display the data from OPTA 1
/* If I do not get to this, my intention was to have some dummy integer or value that the for loops count up for. 
Then, within that same for loop, I was going to get the temperature, time, and voltage values from the MUTEX and 
have the LCD print the values
*/
 // set the cursor to (0,0):
  lcd.setCursor(0, 0);
  // print from 0 to 9:
  
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    lcd.print(thisChar);
    k_msleep(500);
  }

  // set the cursor to (16,1):
  lcd.setCursor(16, 1);
  // set the display to automatically scroll:
  lcd.autoscroll();
  // print from 0 to 9:
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    lcd.print(thisChar);
    lcd.print("this is the temperature - "); // gonna try to make this make more sense later if I can. My intent is to read more about this to see if this works
    lcd.print(val2);
    k_msleep(500);
  }
  // turn off automatic scrolling
  lcd.noAutoscroll();

  // clear screen for the next loop:
  lcd.clear();
}


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  K_THREAD_DEFINE(modbus_tid, 1024, task_modbus, NULL, NULL, NULL, 1, 0, 0); // set to highest priority
  K_THREAD_CREATE(LCD_Display, 1024, scrollLCD, NULL, NULL, NULL, 2, 0, 0);
}