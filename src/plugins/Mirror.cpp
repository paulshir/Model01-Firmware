/* -*- mode: c++ -*-
 * Mirror.cpp -- Send the mirrored key from the other half of the board.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#include "Mirror.h"

namespace kaleidoscope {
namespace plugin {

enum {
  MIRROR_OFF = 0,
  MIRROR_ACTIVE,
  MIRROR_CLEANUP,
};

uint8_t Mirror::step_ = MIRROR_OFF;
paulshir::HandStateStore Mirror::hands_;

static byte mirroredCol(byte col) {
  return Kaleidoscope.device().matrix_columns - col - 1;
}

EventHandlerResult Mirror::onKeyswitchEvent(Key &mappedKey, KeyAddr keyAddr, uint8_t keyState) {
  // Check if the mirror key is pressed
  if (mappedKey.getRaw() == Key_Mirror.getRaw()) {
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
  if (step_ == MIRROR_OFF || keyAddr.row() >= Kaleidoscope.device().matrix_rows || keyAddr.col() >= Kaleidoscope.device().matrix_columns || keyState & INJECTED) {
    return EventHandlerResult::OK;
  }

  // Update the keymap state
  if (step_ == MIRROR_ACTIVE && keyToggledOn(keyState)) {
    hands_.setState(keyAddr.row(), keyAddr.col());
  } else if (keyToggledOff(keyState)) {
    hands_.unsetState(keyAddr.row(), keyAddr.col());
  }

  if (step_ == MIRROR_CLEANUP && hands_.isClear()) {
    step_ = MIRROR_OFF;
  }

  // If the col is not registered don't mirror it.
  if (keyIsPressed(keyState) && !(hands_.getState(keyAddr.row(), keyAddr.col()))) {
    return EventHandlerResult::OK;
  }

  byte mir_col = mirroredCol(keyAddr.col());
  keyAddr.setCol(mir_col);
  Key newKey = Layer.lookup(keyAddr);
  handleKeyswitchEvent(newKey, keyAddr, keyState | INJECTED);

  return EventHandlerResult::EVENT_CONSUMED;
}

}  // namespace plugin
}  // namespace kaleidoscope

kaleidoscope::plugin::Mirror Mirror;
