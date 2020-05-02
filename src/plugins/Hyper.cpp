/* -*- mode: c++ -*-
 * Hyper.cpp -- Use Right GUI as Ctrl/Alt/Shift/Gui
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#include "Hyper.h"

#define Key_HyperSend LCTRL(LSHIFT(LALT(LGUI(Key_RightGui))))

namespace kaleidoscope {
namespace plugin {

EventHandlerResult Hyper::onKeyswitchEvent(Key &mappedKey, KeyAddr keyAddr, uint8_t keyState) {
  if (mappedKey.getRaw() != Key_RightGui.getRaw()) {
    return EventHandlerResult::OK;
  }

  handleKeyswitchEvent(Key_HyperSend, keyAddr, keyState | INJECTED);

  return EventHandlerResult::EVENT_CONSUMED;
}

}  // namespace plugin
}  // namespace kaleidoscope

kaleidoscope::plugin::Hyper Hyper;
