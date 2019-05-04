/* -*- mode: c++ -*-
 * Hyper.cpp -- Use Right GUI as Ctrl/Alt/Shift/Gui
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#include "Hyper.h"

#define Key_HyperSend LCTRL(LSHIFT(LALT(LGUI(Key_RightGui))))

namespace kaleidoscope {

EventHandlerResult Hyper::onKeyswitchEvent(Key &mappedKey, byte row, byte col, uint8_t keyState) {
  if (mappedKey.raw != Key_RightGui.raw) {
    return EventHandlerResult::OK;
  }

  handleKeyswitchEvent(Key_HyperSend, row, col, keyState | INJECTED);

  return EventHandlerResult::EVENT_CONSUMED;
}

}  // namespace kaleidoscope

kaleidoscope::Hyper Hyper;
