/* -*- mode: c++ -*-
 * ToughLove.cpp -- Get rid of bad habits the hard way.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#include "ToughLove.h"

namespace kaleidoscope {

bool ToughLove::active = true;
bool ToughLove::shift_block_active = true;
bool ToughLove::function_block_active = false;
bool ToughLove::block_left_ = false;
bool ToughLove::block_right_ = false;
paulshir::HandStateStore ToughLove::hands_;

EventHandlerResult ToughLove::onKeyswitchEvent(Key &mappedKey, byte row, byte col, uint8_t keyState) {
  if (!active) {
    return EventHandlerResult::OK;
  }

  if (row > ROWS || col > COLS) {
    return EventHandlerResult::OK;
  }

  if (mappedKey.flags & SYNTHETIC) {
    return EventHandlerResult::OK;
  }

  if ((row == 0 && col == 7 && shift_block_active) || (row == 3 && col == 6 && function_block_active)) {
    if (keyToggledOn(keyState)) {
      block_left_ = true;
    } else if (keyToggledOff(keyState)) {
      block_left_ = false;
    }

    return EventHandlerResult::OK;
  }

  if ((row == 0 && col == 8 && shift_block_active) || (row == 3 && col == 9 && function_block_active)) {
    if (keyToggledOn(keyState)) {
      block_right_ = true;
    } else if (keyToggledOff(keyState)) {
      block_right_ = false;
    }

    return EventHandlerResult::OK;
  }

  if (row == 3 && (col == 6 || col == 9)) {
    return EventHandlerResult::OK;
  }

  if ((block_left_ && col < COLS_SPLIT - 1) || (block_right_ && col >= COLS_SPLIT + 1)) {
    if (keyToggledOn(keyState)) {
      hands_.setState(row, col);
    } else if (keyToggledOff(keyState)) {
      if (hands_.getState(row, col)) {
        hands_.unsetState(row, col);
      } else {
        return EventHandlerResult::OK;
      }
    }

    return EventHandlerResult::EVENT_CONSUMED;
  }

  if (hands_.getState(row, col)) {
    if (keyToggledOff(keyState)) {
      hands_.unsetState(row, col);
    }

    return EventHandlerResult::EVENT_CONSUMED;
  }

  block_left_ = false;
  block_right_ = false;

  return EventHandlerResult::OK;
}

}  // namespace kaleidoscope

kaleidoscope::ToughLove ToughLove;
