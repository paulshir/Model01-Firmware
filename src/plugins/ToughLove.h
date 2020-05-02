/* -*- mode: c++ -*-
 * ToughLove.h -- Get rid of bad habits the hard way.
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
class ToughLove : public kaleidoscope::Plugin {
 public:
  ToughLove(void) {}
  static bool active;
  static bool shift_block_active;
  static bool function_block_active;

  EventHandlerResult onKeyswitchEvent(Key &mappedKey, KeyAddr keyAddr, uint8_t keyState);

 private:
  static bool block_left_;
  static bool block_right_;
  static paulshir::HandStateStore hands_;
};

}  // namespace plugin
}  // namespace kaleidoscope

extern kaleidoscope::plugin::ToughLove ToughLove;
