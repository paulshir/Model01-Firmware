/* -*- mode: c++ -*-
 * Mirror.cpp -- Send the mirrored key from the other half of the board.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#include "Mirror.h"

namespace kaleidoscope {

enum {
  MIRROR_OFF = 0,
  MIRROR_ACTIVE,
  MIRROR_CLEANUP,
};

uint8_t Mirror::step_ = MIRROR_OFF;
paulshir::HandStateStore Mirror::hands_;

static byte mirroredCol(byte col) {
  return COLS - col - 1;
}

EventHandlerResult Mirror::onKeyswitchEvent(Key &mappedKey, byte row, byte col, uint8_t keyState) {
  // Check if the mirror key is pressed
  if (mappedKey.raw == Key_Mirror.raw) {
    if (keyIsPressed(keyState)) {
      step_ = MIRROR_ACTIVE;
    } else if (keyToggledOff(keyState)) {
      if (!hands_.isClear()) {
        step_ = MIRROR_CLEANUP;
      } else {
        step_ = MIRROR_OFF;
      }
    }

    return EventHandlerResult::EVENT_CONSUMED;
  }

  // Pass through if not active, injected, or rows/cols are out of bounds
  if (step_ == MIRROR_OFF || row >= ROWS || col >= COLS || keyState & INJECTED) {
    return EventHandlerResult::OK;
  }

  // Update the keymap state
  if (step_ == MIRROR_ACTIVE && keyToggledOn(keyState)) {
    hands_.setState(row, col);
  } else if (keyToggledOff(keyState)) {
    hands_.unsetState(row, col);
  }

  if (step_ == MIRROR_CLEANUP && hands_.isClear()) {
    step_ = MIRROR_OFF;
  }

  // If the col is not registered don't mirror it.
  if (keyIsPressed(keyState) && !(hands_.getState(row, col))) {
    return EventHandlerResult::OK;
  }

  byte mir_col = mirroredCol(col);
  Key newKey = Layer.lookup(row, mir_col);
  handleKeyswitchEvent(newKey, row, mir_col, keyState | INJECTED);

  return EventHandlerResult::EVENT_CONSUMED;
}

}  // namespace kaleidoscope

kaleidoscope::Mirror Mirror;
