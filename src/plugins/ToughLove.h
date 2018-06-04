/* -*- mode: c++ -*-
 * ToughLove.h -- Get rid of bad habits the hard way.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#pragma once

#include "../key-defs-local.h"
#include <Kaleidoscope.h>

namespace kaleidoscope {
class ToughLove : public kaleidoscope::Plugin {
 public:
  ToughLove(void) {}
  static bool active;

  EventHandlerResult onKeyswitchEvent(Key &mappedKey, byte row, byte col, uint8_t keyState);

 private:
  static bool block_left_;
  static bool block_right_;
};

}  // namespace kaleidoscope

extern kaleidoscope::ToughLove ToughLove;
