#include <zephyr/kernel.h >
#include <Arduino.h>
#include <LiquidCrystal.h>
/* My zephyr isn't working as of now. I'm going to try to make code that at lease represents my intention. 
Here is my plan:
1) Define everything according to how zephyr might read it and set up wifi for the board
2) Define a structure for the shared data using the example from the lab document
3) Define all of my threads that are necessary (LCD updater that works outside of a loop, SHT20 reader) 
*/

//Step one: Inititalize all pins and stuff
/* Pseudocode:
defining:
Define board led, A and B inputs for the RS485 shield, 

*/
#define BUILTIN_LED_PIN 13 //Define the board LED
#define RS485_RE 2 // Finding out how to initialize the pins for the SHT20
#define RS485_DE 3 
const int rs = 11, en = 10, d4 = 9, d5 = 8, d6 = 7, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//Step two: define shared values from OPTA 1

//this is from the example in the lab. It seems to be missing something for the value of temperature
struct SystemState {
  float current_mA;
  float temp;
  struct k_mutex mutex
}

struct SystemState state;

void task_modbus (void){ 

  k_mutex_init(&state.mutex);

  while(1){
    float val = readModbus()
    k_mutex_lock (&state.mutex, , K_FOREVER);
    state.current_mA = val;
    k_mutex_unlock(&state.mutex);

    k_msleep(100);
  }
}

K_THREAD_DEFINE(modbus_tid, 1024, task_modbus, NULL, NULL, NULL, 4, 0, 0); // 
)


//Step three: initialize functions within the code using handles and thread handles (Though I'm starting to suspect thread handles are made weird here)


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
    k_msleep(500);
  }
  // turn off automatic scrolling
  lcd.noAutoscroll();

  // clear screen for the next loop:
  lcd.clear();

k_thread_create(LCD_Displayy)

}


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}