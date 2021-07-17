// Copyright Pololu Corporation.  For more information, see http://www.pololu.com/

/// \file PololuMenuMain.h

#pragma once

#include <Arduino.h>
#include <PololuBuzzer.h>
#include <Pushbutton.h>
#include <PololuMenuBeep.h>

template<class D> class PololuMenuMain
{
public:
  struct Item
  {
    const __FlashStringHelper * name;
    void (* action)();
  };
};
