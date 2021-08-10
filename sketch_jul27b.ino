#include <ClickEncoder.h>
#include <TimerOne.h>
#include <HID-Project.h>
#include "OneButton.h"                              //we need the OneButton library

OneButton button1(5, true);                         //attach a button on pin 5 to the library
OneButton button2(A3, true);                        //attach a button on pin A3 to the library
OneButton button3(4, true);                         //attach a button on pin 4 to the library
OneButton button4(6, true);                         //attach a button on pin 6 to the library

ClickEncoder *encoder;                              //Encoder 1
ClickEncoder *encoder2;                             //Encoder 2
int16_t last, value, last2, value2;                 //For encoders to work

void timerIsr() {                                   //For encoders to work
  encoder->service();
  encoder2->service();
}

void setup() {
  Serial.begin(9600);
  encoder = new ClickEncoder(A1, A0, A2);
  encoder2 = new ClickEncoder(2, 9, 3);
  
  button1.attachDoubleClick(doubleclick1);            // link the function to be called on a doubleclick event.
  button1.attachClick(singleclick1);                  // link the function to be called on a singleclick event.
  button1.attachDuringLongPress(longclick1);            // link the function to be called on a longpress event.
  button1.attachLongPressStop(longclickstop);            // link the function to be called on a longpress event.
  
  button2.attachDoubleClick(doubleclick2);            // link the function to be called on a doubleclick event.
  button2.attachClick(singleclick2);                  // link the function to be called on a singleclick event.
  button2.attachLongPressStart(longclick2);            // link the function to be called on a longpress event.
  
  button3.attachDoubleClick(doubleclick3);            // link the function to be called on a doubleclick event.
  button3.attachClick(singleclick3);                  // link the function to be called on a singleclick event.
  button3.attachLongPressStart(longclick3);            // link the function to be called on a longpress event.
  
  button4.attachDoubleClick(doubleclick4);            // link the function to be called on a doubleclick event.
  button4.attachClick(singleclick4);                  // link the function to be called on a singleclick event.
  button4.attachLongPressStart(longclick4);            // link the function to be called on a longpress event.
  
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr); 
  Consumer.begin();
  last = -1;
  last2 = -1;
}

void loop() {  
  button1.tick();                                    // check the status of the button
  button2.tick();                                    // check the status of the button  
  button3.tick();                                    // check the status of the button 
  button4.tick();                                    // check the status of the button 
  delay(10);                                         // a short wait between checking the button
  
//Encoder 1 =====================================================================================================
  value += encoder->getValue();
  if (value != last) {    
          if (value < last) {
            volumeChange(MEDIA_VOL_UP);      
          } 
          else {
            volumeChange(MEDIA_VOL_DOWN);             
          }
            last = value;
  }

//Encoder 1 button code
  ClickEncoder::Button b = encoder->getButton();
  if (b != ClickEncoder::Open) {
      Serial.print("Button: ");
     switch (b) {
      case ClickEncoder::Pressed:
          Serial.print("Pressed");  
          break;

      case ClickEncoder::Held:
          Serial.print("Held");
          break;

      case ClickEncoder::Released:
          Serial.print("Released");
          break;

      case ClickEncoder::Clicked:
          Serial.print("Clicked");
          volumeChange(MEDIA_VOL_MUTE); 
          break;
      
      case ClickEncoder::DoubleClicked:
          Serial.println("ClickEncoder::DoubleClicked");
          encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
          Serial.print("  Acceleration is ");
          Serial.println((encoder->getAccelerationEnabled()) ? "enabled" : "disabled");
          break;
    }
    bool Pressed = 0;
    bool Held = 0;
    bool Released = 0;
    bool Clicked = 0;
    bool DoubleClicked = 0;
  }

//Encoder 1 =====================================================================================================


//Encoder 2 =====================================================================================================
  value2 += encoder2->getValue();
  Serial.println(value2);
  if (value2 != last2) {    
    if (value2 < last2) {
      
                Keyboard.press(KEY_LEFT_CTRL);
                Keyboard.press(KEY_TAB);        
                Keyboard.releaseAll(); 
                delay(100); 
    } 
    else {
                Keyboard.press(KEY_LEFT_SHIFT);
                Keyboard.press(KEY_LEFT_CTRL);
                Keyboard.press(KEY_TAB);        
                Keyboard.releaseAll();   
                delay(100);  
    }
    
    last2 = value2;
  }

  ClickEncoder::Button b2 = encoder2->getButton();
  if (b2 != ClickEncoder::Open) {
    Serial.print("Button: ");
     switch (b2) {
      case ClickEncoder::Pressed:
          Serial.print("Pressed");  
          break;

      case ClickEncoder::Held:
          Serial.print("Held");
          break;

      case ClickEncoder::Released:
          Serial.print("Released");
          break;

      case ClickEncoder::Clicked:
          Serial.print("Clicked");
          volumeChange(MEDIA_VOL_MUTE); 
          break;
      
      case ClickEncoder::DoubleClicked:
          Serial.println("ClickEncoder::DoubleClicked");
          encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
          Serial.print("  Acceleration is ");
          Serial.println((encoder->getAccelerationEnabled()) ? "enabled" : "disabled");
          break;
    }
    bool Pressed = 0;
    bool Held = 0;
    bool Released = 0;
    bool Clicked = 0;
    bool DoubleClicked = 0;   
}
//Encoder 2 =====================================================================================================  

} //void loop closed



//Functions ======================================================================================================

void volumeChange(uint16_t key) {
  Consumer.write(key);
}

//For button1========================================================================================
void singleclick1(){                                 // what happens when the button is clicked
                      Keyboard.press(KEY_TAB);
                      Keyboard.releaseAll();
}
void doubleclick1() {                                // what happens when button is double-clicked
                      Keyboard.press(KEY_LEFT_ALT);
                      Keyboard.press(KEY_TAB);    
                          
                      Keyboard.releaseAll();                  
}
void longclick1(){                                    // what happens when buton is long-pressed
                      Keyboard.press(KEY_LEFT_ALT);
                    
                      Keyboard.press(KEY_TAB);     
                      Keyboard.release(KEY_TAB); 
                      delay(500);  
}
void longclickstop() {                                // what happens when button is double-clicked
                      Keyboard.releaseAll();   
                      button1.reset();                
}
//For button2========================================================================================
void singleclick2(){                                 // what happens when the button is clicked
                      Keyboard.press(KEY_LEFT_ALT);
                      Keyboard.press('a');
                      Keyboard.releaseAll();
}
void doubleclick2() {                                // what happens when button is double-clicked
                      Keyboard.press(KEY_LEFT_ALT);
                      Keyboard.press('v');
                      Keyboard.releaseAll();
}
 
void longclick2(){                                   // what happens when buton is long-pressed
                      Keyboard.press(KEY_LEFT_ALT);
                      Keyboard.press('q');
                      delay(100); 
                      Keyboard.releaseAll();
                      delay(100); 
                      Keyboard.press(KEY_RETURN);
                      delay(100); 
                      Keyboard.releaseAll();
}
//For button3========================================================================================
void singleclick3(){                                 // what happens when the button is clicked
                      Keyboard.press(KEY_PAGE_UP);
                      Keyboard.releaseAll();
}
void doubleclick3() {                                // what happens when button is double-clicked

                      Keyboard.press(KEY_RETURN);
                      Keyboard.releaseAll();
}
 
void longclick3(){                                   // what happens when buton is long-pressed
                      Keyboard.press(KEY_ESC);
                      Keyboard.releaseAll();
}
//For button4========================================================================================
void singleclick4(){                                 // what happens when the button is clicked
                      Keyboard.press(KEY_PAGE_DOWN);
                      Keyboard.releaseAll();
}
void doubleclick4() {                                // what happens when button is double-clicked

                      Keyboard.println("######");   //Windows password for quick login
}
void longclick4(){                                   // what happens when buton is long-pressed
                      Keyboard.press(KEY_RIGHT_GUI);
                      Keyboard.press('l');
                      Keyboard.releaseAll();
}
