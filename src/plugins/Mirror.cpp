/* -*- mode: c++ -*-
 * Mirror.cpp -- Send the mirrored key from the other half of the board.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#include "Mirror.h"

#define COLS_SPLIT COLS/2

/**
 * Using keys on base layer works well. Keys on other layers always work as expected.
 */
namespace kaleidoscope {

enum {
  MIRROR_OFF = 0,
  MIRROR_ACTIVE,
  MIRROR_CLEANUP,
};

uint8_t Mirror::step_ = MIRROR_OFF;
uint32_t Mirror::left_hand_ = 0;
uint32_t Mirror::right_hand_ = 0;

static byte mirroredCol(byte col) {
  return COLS - col - 1;
}

EventHandlerResult Mirror::onKeyswitchEvent(Key &mappedKey, byte row, byte col, uint8_t keyState) {
  // Check if the mirror key is pressed
  if (mappedKey.raw == Key_Mirror.raw) {
    if (keyIsPressed(keyState)) {
      step_ = MIRROR_ACTIVE;
    } else if (keyToggledOff(keyState)) {
      if (left_hand_ | right_hand_) {
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

  uint32_t scanbit;
  uint32_t* hand;
  if (col < COLS_SPLIT) {
    scanbit = SCANBIT(row, col);
    hand = &left_hand_;
  } else {
    scanbit = SCANBIT(row, col - COLS_SPLIT);
    hand = &right_hand_;
  }

  // Update the keymap state
  if (step_ == MIRROR_ACTIVE && keyToggledOn(keyState)) {
    *hand |= scanbit;
  } else if (keyToggledOff(keyState)) {
    *hand &= ~scanbit;
  }

  if (step_ == MIRROR_CLEANUP && left_hand_ == 0 && right_hand_ == 0) {
    step_ = MIRROR_OFF;
  }

  // If the col is not registered don't mirror it.
  if (keyIsPressed(keyState) && !(*hand & scanbit)) {
    return EventHandlerResult::OK;
  }

  byte mir_col = mirroredCol(col);
  Key newKey = Layer.lookup(row, mir_col);
  newKey.flags = mappedKey.flags;
  handleKeyswitchEvent(newKey, row, mir_col, keyState | INJECTED);

  return EventHandlerResult::EVENT_CONSUMED;
}

}  // namespace kaleidoscope

kaleidoscope::Mirror Mirror;
