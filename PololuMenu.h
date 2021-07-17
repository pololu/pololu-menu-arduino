// Copyright Pololu Corporation.  For more information, see http://www.pololu.com/

/** \file Menu.h **/

#pragma once

#include <PololuHD44780.h>
#include <PololuBuzzer.h>
#include <Pushbutton.h>

class PololuMenu
{
public:
  static const char beepPrevious[] PROGMEM;
  static const char beepSelect[] PROGMEM;
  static const char beepNext[] PROGMEM;

  struct Item
  {
    const __FlashStringHelper * name;
    void (* action)();
  };

  void restart();
  void setItems(const Item * items, uint8_t itemCount);

  void setLcd(PololuHD44780Base &);
  void setBuzzer(PololuBuzzer &);

  void setPreviousButton(PushbuttonBase &b, char name)
  {
    previousButton = &b;
    previousButtonName = name;
  }

  void setSelectButton(PushbuttonBase &b, char name)
  {
    selectButton = &b;
    selectButtonName = name;
  }

  void setNextButton(PushbuttonBase &b, char name)
  {
    nextButton = &b;
    nextButtonName = name;
  }

  void setButtons(PushbuttonBase & previous, PushbuttonBase & select, PushbuttonBase & next)
  {
    setPreviousButton(previous, 'A');
    setSelectButton(select, 'B');
    setNextButton(next, 'C');
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
  void setSecondLine(const __FlashStringHelper * text)
  {
    secondLine = text;
  }

private:
  const Item * items;
  uint8_t itemCount;
  uint8_t lcdItemIndex;
  PololuHD44780Base * lcd;
  PololuBuzzer * buzzer;
  PushbuttonBase * previousButton;
  PushbuttonBase * selectButton;
  PushbuttonBase * nextButton;

  char previousButtonName;
  char selectButtonName;
  char nextButtonName;

  const __FlashStringHelper * secondLine;

  bool lcdNeedsUpdate = true;
};
