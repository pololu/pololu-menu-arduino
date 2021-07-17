#include <Arduino.h>
#include <PololuMenu.h>

extern const char PololuMenuBeep::beepPrevious[] PROGMEM = "!c32";
extern const char PololuMenuBeep::beepSelect[] PROGMEM = "!e32";
extern const char PololuMenuBeep::beepNext[] PROGMEM = "!g32";

// These are just here for backwards compatibility.
static const char PololuMenu::beepPrevious[] PROGMEM = "!c32";
static const char PololuMenu::beepSelect[] PROGMEM = "!e32";
static const char PololuMenu::beepNext[] PROGMEM = "!g32";
