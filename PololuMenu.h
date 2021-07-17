// Copyright Pololu Corporation.  For more information, see http://www.pololu.com/

/** \file Menu.h **/

#pragma once

#include <PololuMenuMain.h>
#include <PololuHD44780.h>

class PololuMenu : public PololuMenuMain<PololuHD44780Base>
{
public:
  // Note: These are just here for backwards compatibility.
  // We recommend using the beeps defined in the PololuMenuBeep
  // namespace instead.
  static const char beepPrevious[] PROGMEM;
  static const char beepSelect[] PROGMEM;
  static const char beepNext[] PROGMEM;
};
