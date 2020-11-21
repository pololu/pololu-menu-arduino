// Copyright Pololu Corporation.  For more information, see http://www.pololu.com/

/** \file Menu.h **/

#pragma once

#include <PololuHD44780.h>
#include <PololuBuzzer.h>
#include <Pushbutton.h>

class PololuMenu
{
public:
  static const char beepButtonA[] PROGMEM;
  static const char beepButtonB[] PROGMEM;
  static const char beepButtonC[] PROGMEM;

  struct Item
  {
    const __FlashStringHelper * name;
    void (* action)();
  };

  void setItems(Item * items, uint8_t itemCount);

  void setLcd(PololuHD44780Base &);
  void setBuzzer(PololuBuzzer &);
  void setButtonA(PushbuttonBase & a);
  void setButtonB(PushbuttonBase & b);
  void setButtonC(PushbuttonBase & c);

  void setButtons(PushbuttonBase & a, PushbuttonBase & b, PushbuttonBase & c)
  {
    setButtonA(a);
    setButtonB(b);
    setButtonC(c);
  }

  void lcdUpdate(uint8_t index);

  void action(uint8_t index);

  // This function is meant to be called repeatedly in a loop.
  // Prompts the user to choose one of the menu items.
  // If a button is pressed, take the appropriate action;
  // return true if a menu item was selected.
  bool select();

  // This function watches for button presses.  If a button is
  // pressed, it beeps a corresponding beep and it returns 'A',
  // 'B', or 'C' depending on what button was pressed.  If no
  // button was pressed, it returns 0.  This function is meant to
  // be called repeatedly in a loop.
  char buttonMonitor();

  // Set the second line of text to be displayed below each menu
  // option.  By default it displays "<A .B C>".  To replace the
  // special characters with nicer arrows and a dot, you could
  // use F("\x7f" "A \xa5" "B C\x7e").
  void setSecondLine(__FlashStringHelper * text)
  {
    secondLine = text;
  }

private:
  Item * items;
  uint8_t itemCount;
  uint8_t lcdItemIndex;
  PololuHD44780Base * lcd;
  PololuBuzzer * buzzer;
  PushbuttonBase * buttonA;
  PushbuttonBase * buttonB;
  PushbuttonBase * buttonC;
  __FlashStringHelper * secondLine;

  bool lcdNeedsUpdate = true;
};
