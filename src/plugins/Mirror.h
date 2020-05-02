/* -*- mode: c++ -*-
 * Mirror.h -- Send the mirrored key from the other half of the board.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#pragma once

#include "../key-defs-local.h"
#include "HandStateStore.h"
#include <Kaleidoscope.h>

namespace kaleidoscope {
namespace plugin {
class Mirror : public kaleidoscope::Plugin {
 public:
  Mirror(void) {}

  EventHandlerResult onKeyswitchEvent(Key &mappedKey, KeyAddr keyAddr, uint8_t keyState);

 private:
  static uint8_t step_;
  static paulshir::HandStateStore hands_;
};

}  // namespace plugin
}  // namespace kaleidoscope

extern kaleidoscope::plugin::Mirror Mirror;
