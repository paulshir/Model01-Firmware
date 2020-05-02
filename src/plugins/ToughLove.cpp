/* -*- mode: c++ -*-
 * ToughLove.cpp -- Get rid of bad habits the hard way.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#include "ToughLove.h"

namespace kaleidoscope {
namespace plugin {

bool ToughLove::active = true;
bool ToughLove::shift_block_active = true;
bool ToughLove::function_block_active = false;
bool ToughLove::block_left_ = false;
bool ToughLove::block_right_ = false;
paulshir::HandStateStore ToughLove::hands_;

EventHandlerResult ToughLove::onKeyswitchEvent(Key &mappedKey, KeyAddr keyAddr, uint8_t keyState) {
  if (!active) {
    return EventHandlerResult::OK;
  }

  if (keyAddr.row() > Kaleidoscope.device().matrix_rows || keyAddr.col() > Kaleidoscope.device().matrix_rows) {
    return EventHandlerResult::OK;
  }

  if (mappedKey.getFlags() & SYNTHETIC) {
    return EventHandlerResult::OK;
  }

  if ((keyAddr.row() == 0 && keyAddr.col() == 7 && shift_block_active) || (keyAddr.row() == 3 && keyAddr.col() == 6 && function_block_active)) {
    if (keyToggledOn(keyState)) {
      block_left_ = true;
    } else if (keyToggledOff(keyState)) {
      block_left_ = false;
    }

    return EventHandlerResult::OK;
  }

  if ((keyAddr.row() == 0 && keyAddr.col() == 8 && shift_block_active) || (keyAddr.row() == 3 && keyAddr.col() == 9 && function_block_active)) {
    if (keyToggledOn(keyState)) {
      block_right_ = true;
    } else if (keyToggledOff(keyState)) {
      block_right_ = false;
    }

    return EventHandlerResult::OK;
  }

  if (keyAddr.row() == 3 && (keyAddr.col() == 6 || keyAddr.col() == 9)) {
    return EventHandlerResult::OK;
  }

  if ((block_left_ && keyAddr.col() < COLS_SPLIT - 1) || (block_right_ && keyAddr.col() >= COLS_SPLIT + 1)) {
    if (keyToggledOn(keyState)) {
      hands_.setState(keyAddr.row(), keyAddr.col());
    } else if (keyToggledOff(keyState)) {
      if (hands_.getState(keyAddr.row(), keyAddr.col())) {
        hands_.unsetState(keyAddr.row(), keyAddr.col());
      } else {
        return EventHandlerResult::OK;
      }
    }

    return EventHandlerResult::EVENT_CONSUMED;
  }

  if (hands_.getState(keyAddr.row(), keyAddr.col())) {
    if (keyToggledOff(keyState)) {
      hands_.unsetState(keyAddr.row(), keyAddr.col());
    }

    return EventHandlerResult::EVENT_CONSUMED;
  }

  block_left_ = false;
  block_right_ = false;

  return EventHandlerResult::OK;
}

}  // namespace plugin
}  // namespace kaleidoscope

kaleidoscope::plugin::ToughLove ToughLove;
