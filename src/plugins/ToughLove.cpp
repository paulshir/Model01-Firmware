/* -*- mode: c++ -*-
 * ToughLove.cpp -- Get rid of bad habits the hard way.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#include "ToughLove.h"

/**
 * Initial naive implementation.
 * Always one loop behind
 * Will not handle lifting of mirror key before lifting of mirrored key.
 * Also pressing multiple mirror keys will cause issue.
 */
namespace kaleidoscope {

bool ToughLove::active = true;
bool ToughLove::block_left_ = false;
bool ToughLove::block_right_ = false;

EventHandlerResult ToughLove::onKeyswitchEvent(Key &mappedKey, byte row, byte col, uint8_t keyState) {
  if (!active) {
    return EventHandlerResult::OK;
  }

  if (row > ROWS || col > COLS) {
    return EventHandlerResult::OK;
  }

  if ((row == 0 && col == 7) || (row == 3 && col == 6)) {
    if (keyIsPressed(keyState)) {
      block_left_ = true;
    } else if (keyWasPressed(keyState)) {
      block_left_ = false;
    }

    return EventHandlerResult::OK;
  }

  if ((row == 0 && col == 8) || (row == 3 && col == 9)) {
    if (keyIsPressed(keyState)) {
      block_right_ = true;
    } else if (keyWasPressed(keyState)) {
      block_right_ = false;
    }

    return EventHandlerResult::OK;
  }

  if (block_left_ && col < COLS_SPLIT) {
    return EventHandlerResult::EVENT_CONSUMED;
  }

  if (block_right_ && col >= COLS_SPLIT) {
    return EventHandlerResult::EVENT_CONSUMED;
  }

  return EventHandlerResult::OK;
}

}  // namespace kaleidoscope

kaleidoscope::ToughLove ToughLove;
