# PololuMenu library for Arduino

## Summary

This is a C++ library for the Arduino IDE that makes it easy to create
basic menus with an 8x2 character LCD, some buttons, and an optional
buzzer to beep when the buttons are pressed.  Adding a menu to your
project with this library will require about 1k of FLASH.

## Example usage

```cpp
void setup()
{
  static const PololuMenu::Item items[] = {
    { F("Item one"), myFunction1 },
    { F("Item two"), myFunction2 },
  };

  menu.setItems(items, 2);

  menu.setLcd(lcd);
  menu.setLcd(buzzer);
  menu.setSelectButton(buttonA, 'A');
  menu.setNextButton(buttonB, 'B');
}
```

## Recommended devices

* [Pololu 3pi+ 32U4](https://www.pololu.com/3pi+)
* [Pololu Zumo 32U4](https://www.pololu.com/zumo)
* [Pololu Balboa 32U4](https://www.pololu.com/balboa)
* [Pololu A-Star 32U4](https://www.pololu.com/a-star)

This library depends on the
[PololuHD44780](https://github.com/pololu/pololu-hd44780-arduino),
[PololuBuzzer](https://github.com/pololu/pololu-buzzer-arduino), and
[Pushbutton](https://github.com/pololu/pushbutton-arduino) libraries;
it should work on other Arduino platforms that can support these
libraries.
