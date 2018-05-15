/* -*- mode: c++ -*-
 * Mirror.h -- Send the mirrored key from the other half of the board.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#pragma once

#include "../key-defs-local.h"
#include <Kaleidoscope.h>

namespace kaleidoscope {
class Mirror : public kaleidoscope::Plugin {
 public:
  Mirror(void) {}

  EventHandlerResult onKeyswitchEvent(Key &mappedKey, byte row, byte col, uint8_t keyState);

 private:
  static bool active_;
};

}  // namespace kaleidoscope

extern kaleidoscope::Mirror Mirror;
