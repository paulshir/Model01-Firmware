/* -*- mode: c++ -*-
 * HelpMeDebug.cpp -- Send the mirrored key from the other half of the board.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#include "HelpMeDebug.h"

/**
 * Initial naive implementation.
 * Always one loop behind
 * Will not handle lifting of mirror key before lifting of mirrored key.
 * Also pressing multiple mirror keys will cause issue.
 */
namespace kaleidoscope {

HelpMeDebug::HelpMeDebug(uint8_t value) {
  this->value_ = value;
};

EventHandlerResult HelpMeDebug::onKeyswitchEvent(Key &mappedKey, byte row, byte col, uint8_t keyState) {
  if (keyToggledOn(keyState) || keyToggledOff(keyState)) {
    Serial.print("HMD");
    Serial.print(value_);
    Serial.print(" key: ");
    Serial.print(mappedKey.raw);
    Serial.print(" row: ");
    Serial.print(row);
    Serial.print(" col: ");
    Serial.print(col);
    Serial.print(" state: ");
    Serial.println(keyState);
  }

  return EventHandlerResult::OK;
}

}  // namespace kaleidoscope
