#include <PololuMenu.h>

// A simple example of customizable menus using an 8x2 LCD,
// buzzer, and buttons.
//
// Buttons A and C are used to move left and right; B
// selects a menu option.
//
// Uncomment one of the following sections for your
// platform, or customize your own.

/* Comment out or remove this block if you are not using an A-Star 32U4 */
// For Pololu A-Star 32U4
// https://www.pololu.com/a-star

#include <AStar32U4.h>
AStar32U4LCD lcd;
AStar32U4Buzzer buzzer;
AStar32U4ButtonA buttonA;
AStar32U4ButtonB buttonB;
AStar32U4ButtonC buttonC;
/* end of block */

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

PololuMenu menu;

void item1()
{
  lcd.clear();
  lcd.print("One!");
  delay(1000);
}

void item2()
{
  lcd.clear();
  lcd.print("Two!");
  delay(1000);
}

void setup()
{
  // The list of menu items.
  //
  // Strings are stored in flash using the F() macro.  This only works
  // within a function, so we define the menu items in setup().  The
  // static const specifiers ensure that they will remain available
  // after setup() exits.
  static const PololuMenu::Item items[] = {
    { F("Item one"), item1 },
    { F("Item two"), item2 },
  };

  // Set up the menu.
  //
  // Note that you must pass in the correct number of items to
  // setItems().  Instead of typing a literal number, you might find
  // it more convenient to have the Arduino compiler compute it
  // automatically with the following formula:
  //
  // sizeof(items)/sizeof(items[0]))
  menu.setItems(items, 2);

  // Attach the LCD, buzzer, and buttons.  All are optional, but
  // there's probably not much reason to use this library without an
  // LCD and at least two buttons.
  menu.setLcd(lcd);
  menu.setBuzzer(buzzer);
  menu.setButtons(buttonA, buttonB, buttonC);
}

void loop()
{
  menu.select();
}
