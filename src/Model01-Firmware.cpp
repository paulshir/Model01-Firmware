/* -*- mode: c++ -*-
 * Model01-Firmware.cpp -- My Model01-Firmware
 *
 * See "LICENSE" for license details
 */

#include "Model01-Firmware.h"

static uint8_t previous_led_mode = 0;
static bool previous_tough_love_status = true;

// *INDENT-OFF*
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED(
    Key_Backtick,  Key_1, Key_2, Key_3, Key_4, Key_5, Key_LeftBracket,
    Key_Tab,       Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
    Key_Escape,    Key_A, Key_S, Key_D, Key_F, Key_G,
    OSL(MEDIA),    Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
    Key_LeftShift, Key_Backspace, Key_LeftGui, Key_LeftControl,
    ShiftToLayer(FUNCTION),

    Key_RightBracket, Key_6, Key_7, Key_8,     Key_9,      Key_0,         LockLayer(NUMPAD),
    ___,              Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
                      Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
    ___,              Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,
    Key_HyperP, Key_LeftAlt, Key_Spacebar, Key_RightShift,
    ShiftToLayer(FUNCTION)),


  [NUMPAD] =  KEYMAP_STACKED(
    ___, ___, ___, ___, ___, ___, M(MACRO_TOGGLE_VL_TRIGGER_BLOCK),
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___,
    ___,

    M(MACRO_VERSION_INFO),       ___, Key_7, Key_8,      Key_9,              Key_KeypadSubtract, ___,
    M(MACRO_TOGGLE_VL_SHIFT),    ___, Key_4, Key_5,      Key_6,              Key_KeypadAdd,      ___,
                                 ___, Key_1, Key_2,      Key_3,              Key_Equals,         ___,
    M(MACRO_TOGGLE_VL_FUNCTION), ___, Key_0, Key_Period, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
    ___, ___, ___, ___,
    ___),

  [ONESHOT] =  KEYMAP_STACKED(
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    OSM(LShift), ___, OSM(LGui), OSM(LCtrl),
    ___,

    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    OSM(HyperP), OSM(LAlt), ___, OSM(RShift),
    ___),

  [FUNCTION] =  KEYMAP_STACKED(
    XXX, Key_F1,           Key_F2,          Key_F3,           Key_F4,          Key_F5,            Key_LEDEffectNext,
    ___, Key_mouseScrollL, Key_mouseWarpNW, Key_mouseUp,      Key_mouseWarpNE, Key_mouseScrollUp, Key_mouseBtnL,
    ___, Key_mouseScrollR, Key_mouseL,      Key_mouseDn,      Key_mouseR,      Key_mouseScrollDn,
    ___, XXX,              Key_mouseWarpSW, Key_mouseWarpEnd, Key_mouseWarpSE, Key_mouseBtnM,     Key_mouseBtnR,
    Key_LeftShift, Key_mouseBtnL, Key_LeftGui, Key_LeftControl,
    ___,

    M(MACRO_ANY), Key_F6,        Key_F7,                   Key_F8,                  Key_F9,          Key_F10,          Key_F11,
    ___,          ___,           Key_LeftCurlyBracket, Key_RightCurlyBracket, Key_LeftBracket, Key_RightBracket, Key_F12,
                  Key_LeftArrow, Key_DownArrow,        Key_UpArrow,           Key_RightArrow,  ___,              ___,
    ___,          ___,           ___,                  ___,                   ___,             Key_Backslash,    Key_Pipe,
    Key_HyperP, Key_LeftAlt, Key_Enter, Key_RightShift,
    ___),


  [MEDIA] =  KEYMAP_STACKED(
    LockLayer(0), LockLayer(1),               LockLayer(2),             LockLayer(3),             LockLayer(4), LockLayer(5), LockLayer(6),
    ___,          Consumer_ScanPreviousTrack, Consumer_PlaySlashPause,  Consumer_ScanNextTrack,   Key_Home,     Key_PageUp,   Key_Enter,
    ___,          Consumer_Mute,              Consumer_VolumeDecrement, Consumer_VolumeIncrement, Key_End,      Key_PageDown,
    ___,          MacOS_Sleep,                ___,                      ___,                      ___,          ___,          Key_Spacebar,
    M(MACRO_TOGGLE_MIRROR), Key_Delete, Key_RightGui, ___,
    ___,

    ___, M(MACRO_TOGGLE_VL_SHIFT), M(MACRO_TOGGLE_VL_FUNCTION), ___,           ___,            ___, ___,
    ___, ___,                      ___,                         Key_UpArrow,   ___,            ___, ___,
         ___,                      Key_LeftArrow,               Key_DownArrow, Key_RightArrow, ___, ___,
    ___, ___,                      ___,                         ___,           ___,            ___, ___,
    ___, Key_RightAlt, Key_Enter, M(MACRO_TOGGLE_ONESHOT),
    ___),

  [EMPTY] =  KEYMAP_STACKED(
    XXX, XXX, XXX, XXX, XXX, XXX, XXX,
    XXX, XXX, XXX, XXX, XXX, XXX, XXX,
    XXX, XXX, XXX, XXX, XXX, XXX,
    XXX, XXX, XXX, XXX, XXX, XXX, XXX,
//    M(MACRO_ANY), TD(1), Key_1, Key_Escape,
    XXX, XXX, XXX, XXX,
    XXX,

    XXX, XXX, XXX, XXX, XXX, XXX, XXX,
    XXX, XXX, XXX, XXX, XXX, XXX, XXX,
         XXX, XXX, XXX, XXX, XXX, XXX,
    XXX, XXX, XXX, XXX, XXX, XXX, XXX,
    XXX, XXX, XXX, XXX,
    XXX)
)
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */
static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */
static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  bool toggledOn = false;
  if (keyToggledOn(keyState))
    lastKey.setKeyCode(Key_A.getKeyCode() + (uint8_t)(millis() % 36));

  if (keyIsPressed(keyState))
    Kaleidoscope.hid().keyboard().pressKey(lastKey, toggledOn);
}

/** toggleMirror is used to turn on the mirror layer
 *
 * When turning on the layer it also changes the LED mode, saving
 * the previous LED mode so it can be returned to when mirror
 * mode is turned off.
 *
 */
static kaleidoscope::plugin::Volley volleyMirror(ShiftToLayer(FUNCTION), ShiftToLayer(FUNCTION));
static kaleidoscope::plugin::Volley volleyOneShot(OSM(LShift), OSM(RShift));
static bool mirrorActive = false;
static bool oneShotActive = false;
static void toggleOneShot();
static void toggleMirror() {
  if (oneShotActive) {
    toggleOneShot();
  }


  if (mirrorActive) {
    mirrorActive = false;
    Volley.activate();
    volleyMirror.deactivate();
    StalkerEffect.inactive_color = CRGB(0, 0, 0);
    kaleidoscope::plugin::LEDControl::set_mode(previous_led_mode);
  } else {
    mirrorActive = true;
    Volley.deactivate();
    volleyMirror.activate();
    previous_led_mode = kaleidoscope::plugin::LEDControl::get_mode_index();
    StalkerEffect.inactive_color = CRGB(100, 0, 90);
    StalkerEffect.activate();
  }
}

static void toggleOneShot() {
  if (mirrorActive) {
    toggleMirror();
  }

  if (oneShotActive) {
    oneShotActive = false;
    Volley.activate();
    volleyOneShot.deactivate();
    Layer.deactivate(ONESHOT);
  } else {
    oneShotActive = true;
    Volley.deactivate();
    volleyOneShot.activate();
    Layer.activate(ONESHOT);
  }

}

static bool volleyIgnoreKeyAddr(KeyAddr key_addr, KeyAddr trigger_key_addr) {
  // Skip Function Keys
  if (key_addr.row() == 3 && (key_addr.col() == 6 || key_addr.col() == 9)) {
    return true;
  }

  // Skip Modifiers
  if (key_addr.row() != 1 && (key_addr.col() == 7 || key_addr.col() == 8)) {
    return true;
  }

  return false;
}

static void onMirrorKeyToggledOn(Key &mapped_key, KeyAddr mir_key_addr) {
  StalkerEffect.onKeyswitchEvent(mapped_key, mir_key_addr, IS_PRESSED);
}

static bool volley_blocked_mode = false;
const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {
  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;
  case MACRO_ANY:
    anyKeyMacro(keyState);
    break;
  case MACRO_TOGGLE_MIRROR:
    if (keyToggledOn(keyState))
      toggleMirror();
    break;
  case MACRO_TOGGLE_VL_SHIFT:
    if (keyToggledOn(keyState))
      Volley.setSecondaryModeBlocked();
    break;
  case MACRO_TOGGLE_VL_FUNCTION:
    if (keyToggledOn(keyState))
      Volley.setSecondaryModeShiftToLayer(FUNCTION);
    break;
  case MACRO_TOGGLE_VL_TRIGGER_BLOCK:
    if (keyToggledOn(keyState)) {
      volley_blocked_mode = !volley_blocked_mode;
      Volley.blockTriggerUntilDecided(volley_blocked_mode);
      volleyOneShot.blockTriggerUntilDecided(volley_blocked_mode);
    }
    break;
  case MACRO_TOGGLE_ONESHOT:
    if (keyToggledOn(keyState))
      toggleOneShot();
    break;
  }

  return MACRO_NONE;
}

static kaleidoscope::plugin::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::plugin::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::plugin::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::plugin::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::plugin::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::plugin::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::plugin::LEDSolidColor solidViolet(130, 0, 120);

void magicComboActions(uint8_t combo_index) {
  switch (combo_index) {
  case 0:
    if (Layer.isActive(EMPTY)) {
      Layer.deactivate(EMPTY);
    } else {
      Layer.activate(EMPTY);
    }
    break;
  case 1:
    toggleMirror();
    break;
  }
}

USE_MAGIC_COMBOS({
  .action = magicComboActions,
  .keys = {R3C6, R3C9}
});

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    LEDControl.disable();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.enable();
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

// static kaleidoscope::plugin::HelpMeDebug hmd1(1);
// static kaleidoscope::plugin::HelpMeDebug hmd2(2);

static kaleidoscope::plugin::BootGreetingEffect bootGreeting(KeyAddr(0, 0));

KALEIDOSCOPE_INIT_PLUGINS(
  // Order Dependent Plugins
  // Qukeys,
  // FlipFlop,
  // hmd1,
  Volley,
  volleyMirror,
  volleyOneShot,
  // hmd2,

  Mirror,
  OneShot,

  // LED Plugins
  ActiveModColorEffect,
  bootGreeting,
  LEDControl,
  LEDOff,
  IdleLEDs,
  LEDBreatheEffect,
  StalkerEffect,
  LEDRainbowEffect,
  LEDRainbowWaveEffect,
  solidRed, solidOrange, solidYellow, solidGreen, solidBlue, solidIndigo, solidViolet,
  WavepoolEffect,

  // Other Plugins
  EscapeOneShot,
  // EEPROMKeymap,
  // EEPROMSettings,
  // Focus,
  // FocusSettingsCommand,
  // FocusEEPROMCommand,
  HostPowerManagement,
  Hyper,
  Macros,
  MagicCombo,
  MouseKeys,
  NumPad,
  USBQuirks
);

namespace paulshir {
void setup() {
  Serial.begin(9600);
  Kaleidoscope.setup();

  // QUKEYS(
  //   kaleidoscope::Qukey(MIRROR, 3, 7, Key_LeftControl),
  //   kaleidoscope::Qukey(MIRROR, 3, 8, Key_RightControl),
  //   kaleidoscope::Qukey(QWERTY, 0, 0, Key_Hyper)
  // )

  // LED Effect Settings
  ActiveModColorEffect.highlight_color = CRGB(0, 255, 255);
  ActiveModColorEffect.sticky_color = CRGB(0, 255, 150);
  LEDBreatheEffect.hue = 50;
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);
  NumPad.numPadLayer = NUMPAD;
  StalkerEffect.variant = STALKER(Haunt, (CRGB(255, 100, 225)));

  MouseKeys.speed = 20;
  MouseKeys.accelSpeed = 40;
  MouseKeys.accelDelay = 100;

  // Volley.setIgnoreKeyAddrFunc(volleyIgnoreKeyAddr);
  Mirror.setMirroredKeyToggledOnFunc(onMirrorKeyToggledOn);
  volleyMirror.deactivate();
  volleyMirror.setSecondaryModePressKey(Key_Mirror);
  volleyMirror.blockTriggerUntilDecided(true);

  volleyOneShot.deactivate();
  volleyOneShot.setSecondaryModeShiftToLayer(FUNCTION);
  volleyOneShot.blockTriggerUntilDecided(true);

  LEDOff.activate();
}

}  // namespace paulshir
