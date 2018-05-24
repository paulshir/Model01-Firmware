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

bool ToughLove::block_ = false;
bool ToughLove::block_left_ = false;

EventHandlerResult ToughLove::onKeyswitchEvent(Key &mappedKey, byte row, byte col, uint8_t keyState) {
  return EventHandlerResult::OK;
}

}  // namespace kaleidoscope

kaleidoscope::ToughLove ToughLove;
