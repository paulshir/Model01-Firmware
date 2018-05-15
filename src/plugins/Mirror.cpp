/* -*- mode: c++ -*-
 * Mirror.cpp -- Send the mirrored key from the other half of the board.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#include "Mirror.h"

/**
 * Initial naive implementation.
 * Always one loop behind
 * Will not handle lifting of mirror key before lifting of mirrored key.
 * Also pressing multiple mirror keys will cause issue.
 */
namespace kaleidoscope {

bool Mirror::active_ = false;

static byte mirroredCol(byte col) {
  return COLS - col - 1;
}

EventHandlerResult Mirror::onKeyswitchEvent(Key &mappedKey, byte row, byte col, uint8_t keyState) {
  if (mappedKey.raw == Key_Mirror.raw) {
    if (keyToggledOn(keyState)) {
      active_ = true;
    } else if (keyToggledOff(keyState)) {
      active_ = false;
    }

    return EventHandlerResult::EVENT_CONSUMED;
  }

  if (!active_ || (keyState & INJECTED)) {
    return EventHandlerResult::OK;
  }

  byte mirCol = mirroredCol(col);
  Key newKey = Layer.lookupOnActiveLayer(row, mirCol);
  newKey.flags = mappedKey.flags;

  handleKeyswitchEvent(newKey, row, mirCol, IS_PRESSED | INJECTED);

  return EventHandlerResult::EVENT_CONSUMED;
}

}  // namespace kaleidoscope

kaleidoscope::Mirror Mirror;
