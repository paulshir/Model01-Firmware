/* -*- mode: c++ -*-
 * Hyper.h -- Use Right GUI as Ctrl/Alt/Shift/Gui
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#pragma once

#include <Kaleidoscope.h>

namespace kaleidoscope {
namespace plugin {
class Hyper : public kaleidoscope::Plugin {
 public:
  Hyper(void) {}

  EventHandlerResult onKeyswitchEvent(Key &mappedKey, KeyAddr keyAddr, uint8_t keyState);
};

}  // namespace plugin
}  // namespace kaleidoscope

extern kaleidoscope::plugin::Hyper Hyper;
