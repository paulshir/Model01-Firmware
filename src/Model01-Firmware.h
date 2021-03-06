/* -*- mode: c++ -*-
 * Model01-Firmware.h -- My Model01-Firmware
 *
 * See "LICENSE" for license details
 */
#pragma once

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

#include "key-defs-local.h"

#include "plugins/HelpMeDebug.h"
#include "plugins/Hyper.h"
#include "plugins/Mirror.h"
#include "plugins/Volley.h"

#include <Kaleidoscope.h>
// #include <Kaleidoscope-EEPROM-Settings.h>
// #include <Kaleidoscope-EEPROM-Keymap.h>
#include <Kaleidoscope-Escape-OneShot.h>
// #include <Kaleidoscope-FocusSerial.h>
#include <Kaleidoscope-HostPowerManagement.h>
#include <Kaleidoscope-MouseKeys.h>
#include <Kaleidoscope-Macros.h>
#include <Kaleidoscope-MagicCombo.h>
#include <Kaleidoscope-NumPad.h>
#include <Kaleidoscope-OneShot.h>
// #include <Kaleidoscope-Qukeys.h>
#include <Kaleidoscope-Ranges.h>
#include <Kaleidoscope-USB-Quirks.h>

#include <Kaleidoscope-LEDControl.h>
#include <Kaleidoscope-IdleLEDs.h>
#include <Kaleidoscope-LED-ActiveModColor.h>
#include <Kaleidoscope-LED-Stalker.h>
#include <Kaleidoscope-LED-Wavepool.h>
#include <Kaleidoscope-LEDEffect-BootGreeting.h>
#include <Kaleidoscope-LEDEffect-SolidColor.h>
#include <Kaleidoscope-LEDEffect-Breathe.h>
#include <Kaleidoscope-LEDEffect-Rainbow.h>

// Macros
enum {
  MACRO_VERSION_INFO,
  MACRO_ANY,
  MACRO_CLEAR_ONESHOT,
  MACRO_TOGGLE_MIRROR,
  MACRO_TOGGLE_VL_SHIFT,
  MACRO_TOGGLE_VL_FUNCTION,
  MACRO_TOGGLE_VL_TRIGGER_BLOCK,
  MACRO_TOGGLE_ONESHOT,
};

// Layers
enum {
  QWERTY,
  NUMPAD,
  ONESHOT,
  FUNCTION,
  MEDIA,
  // MIRROR,
  EMPTY
};

// TapDance
enum {
  TD_LEFT_BRACKET,
  TD_RIGHT_BRACKET,
  TD_SLASH
};

namespace paulshir {
void setup(void);
}  // namespace paulshir
