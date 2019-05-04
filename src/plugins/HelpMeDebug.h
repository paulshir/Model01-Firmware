/* -*- mode: c++ -*-
 * HelpMeDebug.h -- Some debugging helpers.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#pragma once

#include <Kaleidoscope.h>

namespace kaleidoscope {
class HelpMeDebug : public kaleidoscope::Plugin {
 public:
  explicit HelpMeDebug(uint8_t value);

  EventHandlerResult onKeyswitchEvent(Key &mappedKey, byte row, byte col, uint8_t keyState);

 private:
  uint8_t value_;
};

}  // namespace kaleidoscope
