/* -*- mode: c++ -*-
 * Hyper.h -- Use Right GUI as Ctrl/Alt/Shift/Gui
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#pragma once

#include <Kaleidoscope.h>

namespace kaleidoscope {
class Hyper : public kaleidoscope::Plugin {
 public:
  Hyper(void) {}

  EventHandlerResult onKeyswitchEvent(Key &mappedKey, byte row, byte col, uint8_t keyState);
};

}  // namespace kaleidoscope

extern kaleidoscope::Hyper Hyper;
