/* -*- mode: c++ -*-
 * HelpMeDebug.h -- Some debugging helpers.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#pragma once

#include <Kaleidoscope.h>

namespace kaleidoscope {
namespace plugin {
class HelpMeDebug : public kaleidoscope::Plugin {
 public:
  explicit HelpMeDebug(uint8_t value);

  EventHandlerResult onKeyswitchEvent(Key &mappedKey, KeyAddr keyAddr, uint8_t keyState);

 private:
  uint8_t value_;
};

}  // namespace plugin
}  // namespace kaleidoscope
