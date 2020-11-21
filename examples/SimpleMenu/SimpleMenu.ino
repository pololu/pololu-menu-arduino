#include <PololuMenu.h>

// You will need to uncomment one of the following sections
// for your platform, or customize your own.

#include <Pololu3piPlus32U4.h>
Pololu3piPlus32U4::LCD lcd;
Pololu3piPlus32U4::Buzzer buzzer;
Pololu3piPlus32U4::ButtonA buttonA;
Pololu3piPlus32U4::ButtonB buttonB;
Pololu3piPlus32U4::ButtonC buttonC;

PololuMenu mainMenu;

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

PololuMenu::Item mainMenuItems[] = {
  { "Item one", item1 },
  { "Item two", item2 },
};

void setup()
{
  mainMenu.setItems(mainMenuItems, sizeof(mainMenuItems)/sizeof(mainMenuItems[0]));
  mainMenu.setLcd(lcd);
  mainMenu.setBuzzer(buzzer);
  mainMenu.setButtons(buttonA, buttonB, buttonC);
}

void loop()
{
  mainMenu.select();
}
