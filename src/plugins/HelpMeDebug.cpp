/* -*- mode: c++ -*-
 * HelpMeDebug.cpp -- Some debugging helpers.
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
namespace plugin {

HelpMeDebug::HelpMeDebug(uint8_t value) {
  this->value_ = value;
}

EventHandlerResult HelpMeDebug::onKeyswitchEvent(Key &mappedKey, KeyAddr keyAddr, uint8_t keyState) {
  if (keyToggledOn(keyState) || keyToggledOff(keyState)) {
    Serial.print("HMD");
    Serial.print(value_);
    Serial.print(" keyCode: ");
    Serial.print(mappedKey.getKeyCode());
    Serial.print(" | ");
    Serial.print(mappedKey.getFlags());
    if (keyAddr == UnknownKeyswitchLocation) {
      Serial.print("Unknown Location");
    } else {
      Serial.print(" row: ");
      Serial.print(keyAddr.row());
      Serial.print(" col: ");
      Serial.print(keyAddr.col());
    }
    Serial.print(" state: ");
    Serial.println(keyState);
  }

  return EventHandlerResult::OK;
}

}  // namespace plugin
}  // namespace kaleidoscope
