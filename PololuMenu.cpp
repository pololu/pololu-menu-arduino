#include <Arduino.h>
#include <PololuMenu.h>

static const char PololuMenu::beepButtonA[] PROGMEM = "!c32";
static const char PololuMenu::beepButtonB[] PROGMEM = "!e32";
static const char PololuMenu::beepButtonC[] PROGMEM = "!g32";

void PololuMenu::setItems(Item * items, uint8_t itemCount)
{
  this->items = items;
  this->itemCount = itemCount;
  lcdItemIndex = 0;
}

void PololuMenu::setLcd(PololuHD44780Base & l)
{
  lcd = &l;
}

void PololuMenu::setBuzzer(PololuBuzzer & b)
{
  buzzer = &b;
}

void PololuMenu::lcdUpdate(uint8_t index)
{
  if(lcd == NULL) return;
  lcd->clear();
  lcd->print(items[index].name);
  lcd->gotoXY(0, 1);
  if(secondLine != NULL)
    lcd->print(secondLine);
  else
    lcd->print(F("<A *B C>"));
}

void PololuMenu::setButtonA(PushbuttonBase & button)
{
  buttonA = &button;
}

void PololuMenu::setButtonB(PushbuttonBase & button)
{
  buttonB = &button;
}

void PololuMenu::setButtonC(PushbuttonBase & button)
{
  buttonC = &button;
}

void PololuMenu::action(uint8_t index)
{
  items[index].action();
}

bool PololuMenu::select()
{
  if(lcdNeedsUpdate)
  {
    lcdUpdate(lcdItemIndex);
  }

  // Assume we will need to update, but set to false if
  // there are no button events.
  lcdNeedsUpdate = true;

  switch (buttonMonitor())
  {
  case 'A':
    // The A button was pressed so decrement the index.
    if (lcdItemIndex == 0)
    {
      lcdItemIndex = itemCount - 1;
    }
    else
    {
      lcdItemIndex--;
    }
    return false;

  case 'C':
    // The C button was pressed so increase the index.
    if (lcdItemIndex >= itemCount - 1)
    {
      lcdItemIndex = 0;
    }
    else
    {
      lcdItemIndex++;
    }
    return false;

  case 'B':
    // The B button was pressed so run the item and return.
    action(lcdItemIndex);
    return true;
  }

  // Nothing happened, no update necessary
  lcdNeedsUpdate = false;
  return false;
}

char PololuMenu::buttonMonitor()
{
  if ((buttonA != NULL) && buttonA->getSingleDebouncedPress())
  {
    if(buzzer != NULL)
      buzzer->playFromProgramSpace(beepButtonA);
    return 'A';
  }

  if ((buttonB != NULL) && buttonB->getSingleDebouncedPress())
  {
    if(buzzer != NULL)
      buzzer->playFromProgramSpace(beepButtonB);
    return 'B';
  }

  if ((buttonC != NULL) && buttonC->getSingleDebouncedPress())
  {
    if(buzzer != NULL)
      buzzer->playFromProgramSpace(beepButtonC);
    return 'C';
  }

  return 0;
}
