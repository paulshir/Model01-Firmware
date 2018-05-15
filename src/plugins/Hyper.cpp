/* -*- mode: c++ -*-
 * Hyper.cpp -- Use Right GUI as Ctrl/Alt/Shift/Gui
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#include "Hyper.h"

namespace kaleidoscope {

EventHandlerResult Hyper::onKeyswitchEvent(Key &mappedKey, byte row, byte col, uint8_t keyState) {
  if (mappedKey.raw != Key_RightGui.raw) {
    return EventHandlerResult::OK;
  }

  handleKeyswitchEvent(LCTRL(LSHIFT(LALT(Key_RightGui))), row, col, IS_PRESSED | INJECTED);

  return EventHandlerResult::EVENT_CONSUMED;
}

}  // namespace kaleidoscope

kaleidoscope::Hyper Hyper;
