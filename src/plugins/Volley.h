/* -*- mode: c++ -*-
 * FlipFlop.h
 * Copyright (C) 2020  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#pragma once

#include <Kaleidoscope.h>

constexpr uint8_t kColSplit = Kaleidoscope.device().matrix_columns / 2;

namespace kaleidoscope {
namespace plugin {
class Volley : public kaleidoscope::Plugin {
 public:
  Volley(Key trigger_key_l, Key trigger_key_r);
  Volley() : Volley(Key_LeftShift, Key_RightShift) {};

  void activate();
  void deactivate();
  bool isActive();

  enum ModeDeciderResult {
    PRIMARY_MODE,
    SECONDARY_MODE,
    UNDECIDED
  };

  typedef ModeDeciderResult(*ModeDeciderFunc)(Key &mapped_key, KeyAddr key_addr, KeyAddr trigger_key_addr);
  void overrideModeDeciderFunction(ModeDeciderFunc func);
  void blockTriggerUntilDecided(bool block);
  void setSecondaryModeBlocked();
  void setSecondaryModeShiftToLayer(uint8_t layer);
  void setSecondaryModePressKey(Key key);
  EventHandlerResult onKeyswitchEvent(Key &mapped_key, KeyAddr key_addr, uint8_t key_state);
  EventHandlerResult beforeReportingState();

 private:
  enum VolleyState {
    READY,
    TRIGGERED,
    PRIMARY_FUNCTION_ACTIVE,
    SECONDARY_FUNCTION_ACTIVE,
    SKIP
  };

  enum VolleyTriggerState {
    SEND_AND_REVERT,
    BLOCK_UNTIL_DECIDED,
    SEND_TRIGGER_IS_PRESSED,
    SEND_TRIGGER_WAS_PRESSED,
  };

  EventHandlerResult activatePrimaryMode(Key &mapped_key, KeyAddr key_addr);
  EventHandlerResult activateSecondaryMode(Key &mapped_key, KeyAddr key_addr);
  
  // Settings
  static ModeDeciderFunc modeDecider;
  static ModeDeciderResult defaultModeDecider(Key &mapped_key, KeyAddr key_addr, KeyAddr trigger_key_addr);

  bool active_;
  Key trigger_key_1_;
  Key trigger_key_2_;
  Key secondary_mode_key_;

  Volley::VolleyTriggerState trigger_state_;

  // Internal
  Volley::VolleyState state_;
  KeyAddr trigger_key_addr_;

};

}  // namespace plugin
}  // namespace kaleidoscope

extern kaleidoscope::plugin::Volley Volley;