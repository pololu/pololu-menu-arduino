#include <PololuMenu.h>

// A more complicated menu example, with two levels of nested menus.
//
// Uncomment one of the following sections for your
// platform, or customize your own.

/*
// For Pololu 3pi+ 32U4
// https://www.pololu.com/3pi+

#include <Pololu3piPlus32U4.h>
Pololu3piPlus32U4::LCD lcd;
Pololu3piPlus32U4::Buzzer buzzer;
Pololu3piPlus32U4::ButtonA buttonA;
Pololu3piPlus32U4::ButtonB buttonB;
Pololu3piPlus32U4::ButtonC buttonC;
*/

/*
// For Pololu Zumo 32U4
// https://www.pololu.com/zumo

#include <Zumo32U4.h>
Zumo32U4LCD lcd;
Zumo32U4Buzzer buzzer;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4ButtonC buttonC;
*/

/*
// For Pololu Balboa 32U4
// https://www.pololu.com/balboa

#include <Balboa32U4.h>
Balboa32U4LCD lcd;
Balboa32U4Buzzer buzzer;
Balboa32U4ButtonA buttonA;
Balboa32U4ButtonB buttonB;
Balboa32U4ButtonC buttonC;
*/

/*
// For Pololu A-Star 32U4
// https://www.pololu.com/a-star

#include <AStar32U4.h>
AStar32U4LCD lcd;
AStar32U4Buzzer buzzer;
AStar32U4ButtonA buttonA;
AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;
*/

PololuMenu mainMenu;
PololuMenu subMenu;
PololuMenu *activeMenu = &mainMenu;

bool anyButtonPress()
{
  if(mainMenu.buttonMonitor())
    return true;

  if(buttonC.getSingleDebouncedPress())
  {
    buzzer.play("!c32");
    return true;
  }

  return false;
}

void item1()
{
  lcd.clear();
  lcd.print("This is");
  lcd.gotoXY(0,1);
  lcd.print("item one");
  while(!anyButtonPress());
}

void item21()
{
  lcd.clear();
  lcd.print("This is");
  lcd.gotoXY(0,1);
  lcd.print("item 2.1");
  while(!anyButtonPress());
}

void item22()
{
  lcd.clear();
  lcd.print("This is");
  lcd.gotoXY(0,1);
  lcd.print("item 2.2");
  while(!anyButtonPress());
}

void openSubMenu()
{
  activeMenu = &subMenu;
  subMenu.restart();
}

void closeSubMenu()
{
  activeMenu = &mainMenu;
}

void setup()
{
  static const PololuMenu::Item items[] = {
    { F("Item 1"), item1 },
    { F("2.x ..."), openSubMenu },
  };

  mainMenu.setItems(items, 2);
  mainMenu.setLcd(lcd);
  mainMenu.setBuzzer(buzzer);
  mainMenu.setSelectButton(buttonB, 'B');
  mainMenu.setNextButton(buttonA, 'A');
  mainMenu.setSecondLine(F("A> B*"));

  static const PololuMenu::Item subMenuItems[] = {
    { F("Item 2.1"), item21 },
    { F("Item 2.2"), item22 },
  };

  subMenu.setItems(subMenuItems, 2);
  subMenu.setLcd(lcd);
  subMenu.setBuzzer(buzzer);
  subMenu.setSelectButton(buttonB, 'B');
  subMenu.setNextButton(buttonA, 'A');
  subMenu.setSecondLine(F("A> B* C<"));
}

void loop()
{
  activeMenu->select();

  // button C exits from the submenu
  if(activeMenu == &subMenu && buttonC.getSingleDebouncedPress())
  {
    buzzer.play("!l32gec");
    closeSubMenu();
  }
}
