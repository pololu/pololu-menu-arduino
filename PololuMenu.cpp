#include <Arduino.h>
#include <PololuMenu.h>

static const char PololuMenu::beepPrevious[] PROGMEM = "!c32";
static const char PololuMenu::beepSelect[] PROGMEM = "!e32";
static const char PololuMenu::beepNext[] PROGMEM = "!g32";

void PololuMenu::setItems(Item * items, uint8_t itemCount)
{
  this->items = items;
  this->itemCount = itemCount;
}

void PololuMenu::restart()
{
  lcdItemIndex = 0;
  lcdNeedsUpdate = true;
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
  {
    // Generate something based on the key names
    if(previousButton)
    {
      lcd->print('<');
      lcd->print(previousButtonName);
    }
    if(selectButton)
    {
      lcd->gotoXY(3,1);
      lcd->print('*');
      lcd->print(selectButtonName);
    }
    if(nextButton)
    {
      lcd->gotoXY(6,1);
      lcd->print(nextButtonName);
      lcd->print('>');
    }
  }
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

  char button = buttonMonitor();
  if(button && button == previousButtonName)
  {
    // The "previous" button was pressed so decrement the index.
    if (lcdItemIndex == 0)
    {
      lcdItemIndex = itemCount - 1;
    }
    else
    {
      lcdItemIndex--;
    }
    return false;
  }

  if(button && button == nextButtonName)
  {
    // The "next" button was pressed so increase the index.
    if (lcdItemIndex >= itemCount - 1)
    {
      lcdItemIndex = 0;
    }
    else
    {
      lcdItemIndex++;
    }
    return false;
  }

  if(button && button == selectButtonName)
  {
    // The "select" button was pressed so run the item and return true.
    action(lcdItemIndex);
    return true;
  }

  // Nothing happened, no update necessary
  lcdNeedsUpdate = false;
  return false;
}

char PololuMenu::buttonMonitor()
{
  if ((previousButton != NULL) && previousButton->getSingleDebouncedPress())
  {
    if(buzzer != NULL)
      buzzer->playFromProgramSpace(beepPrevious);
    return previousButtonName;
  }

  if ((selectButton != NULL) && selectButton->getSingleDebouncedPress())
  {
    if(buzzer != NULL)
      buzzer->playFromProgramSpace(beepSelect);
    return selectButtonName;
  }

  if ((nextButton != NULL) && nextButton->getSingleDebouncedPress())
  {
    if(buzzer != NULL)
      buzzer->playFromProgramSpace(beepNext);
    return nextButtonName;
  }

  return 0;
}
