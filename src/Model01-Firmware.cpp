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
    Key_Enter,        Key_Y, Key_U, Key_I,     Key_O,      Key_P,         Key_Equals,
                      Key_H, Key_J, Key_K,     Key_L,      Key_Semicolon, Key_Quote,
    OSM(Hyper),       Key_N, Key_M, Key_Comma, Key_Period, Key_Slash,     Key_Minus,
    Key_Hyper, Key_LeftAlt, Key_Spacebar, Key_RightShift,
    ShiftToLayer(FUNCTION)),


  [NUMPAD] =  KEYMAP_STACKED(
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___,
    ___,

    M(MACRO_VERSION_INFO),  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___,
    ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___,
                            ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         ___,
    ___,                    ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
    ___, ___, ___, ___,
    ___),


  [FUNCTION] =  KEYMAP_STACKED(
    XXX, Key_F1,           Key_F2,          Key_F3,           Key_F4,          Key_F5,            Key_LEDEffectNext,
    ___, Key_mouseScrollL, Key_mouseWarpNW, Key_mouseUp,      Key_mouseWarpNE, Key_mouseScrollUp, Key_mouseBtnL,
    ___, Key_mouseScrollR, Key_mouseL,      Key_mouseDn,      Key_mouseR,      Key_mouseScrollDn,
    ___, XXX,              Key_mouseWarpSW, Key_mouseWarpEnd, Key_mouseWarpSE, Key_mouseBtnM,     Key_mouseBtnR,
    OSM(LeftShift), Key_mouseBtnL, OSM(LeftGui), OSM(LeftControl),
    ___,

    M(MACRO_ANY), Key_F6,        Key_F7,                   Key_F8,                  Key_F9,          Key_F10,          Key_F11,
    ___,          ___,           Key_LeftCurlyBracket,     Key_RightCurlyBracket,   Key_LeftBracket, Key_RightBracket, Key_F12,
                  Key_LeftArrow, Key_DownArrow,            Key_UpArrow,             Key_RightArrow,  ___,              ___,
    ___,          Consumer_Mute, Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
    OSM(Hyper), OSM(LeftAlt), Key_Enter, OSM(RightShift),
    ___),


  [MEDIA] =  KEYMAP_STACKED(
    XXX, LockLayer(0),               LockLayer(1),             LockLayer(2),             LockLayer(3), LockLayer(4), LockLayer(5),
    ___, Consumer_ScanPreviousTrack, Consumer_PlaySlashPause,  Consumer_ScanNextTrack,   Key_Home,     Key_PageUp,   Key_Enter,
    ___, Consumer_Mute,              Consumer_VolumeDecrement, Consumer_VolumeIncrement, Key_End,      Key_PageDown,
    ___, MacOS_Sleep,                ___,                      ___,                      ___,          ___,          Key_Spacebar,
    M(MACRO_TOGGLE_MIRROR), Key_Delete, Key_RightGui, ___,
    ___,

    ___, M(MACRO_TOGGLE_TOUGH_LOVE), ___,           ___,           ___,            ___, ___,
    ___, ___,                        ___,           Key_UpArrow,   ___,            ___, ___,
         ___,                        Key_LeftArrow, Key_DownArrow, Key_RightArrow, ___, ___,
    ___, ___,                        ___,           ___,           ___,            ___, ___,
    ___, Key_RightAlt, Key_Enter, M(MACRO_TOGGLE_MIRROR),
    ___),


  [MIRROR] =  KEYMAP_STACKED(
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, LockLayer(FUNCTION),
    Key_Mirror,

    ___, ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
         ___, ___, ___, ___, ___, ___,
    ___, ___, ___, ___, ___, ___, ___,
    LockLayer(FUNCTION), ___, ___, ___,
    Key_Mirror),


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
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey);
}

/** toggleMirror is used to turn on the mirror layer
 *
 * When turning on the layer it also changes the LED mode, saving
 * the previous LED mode so it can be returned to when mirror
 * mode is turned off.
 *
 */
static void toggleMirror() {
  if (Layer.isOn(MIRROR)) {
    Layer.off(MIRROR);
    StalkerEffect.breathe_on = false;
    kaleidoscope::LEDControl::set_mode(previous_led_mode);
    ToughLove.active = previous_tough_love_status;
  } else {
    Layer.on(MIRROR);
    previous_led_mode = kaleidoscope::LEDControl::get_mode_index();
    StalkerEffect.breathe_on = true;
    StalkerEffect.activate();
    previous_tough_love_status = ToughLove.active;
    ToughLove.active = false;
  }
}

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
  case MACRO_TOGGLE_TOUGH_LOVE:
    ToughLove.active = !ToughLove.active;
  }

  return MACRO_NONE;
}

static const kaleidoscope::MagicCombo::combo_t magic_combos[] PROGMEM = {
  {
    R3C6,
    R3C9
  },
  {
    R0C7,
    R0C8
  },
  {0, 0}
};

static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);

void magicComboActions(uint8_t combo_index, uint32_t left_hand, uint32_t right_hand) {
  switch (combo_index) {
  case 0:
    if (Layer.isOn(EMPTY)) {
      Layer.off(EMPTY);
    } else {
      Layer.on(EMPTY);
    }
    break;
  case 1:
    toggleMirror();
    break;
  }
}

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
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

// static kaleidoscope::HelpMeDebug hmd1(1);
// static kaleidoscope::HelpMeDebug hmd2(2);

KALEIDOSCOPE_INIT_PLUGINS(
  // Order Dependent Plugins
  Qukeys,
  // hmd1,
  Mirror,
  // hmd2,
  OneShot,

  // LED Plugins
  ActiveModColorEffect,
  BootGreetingEffect,
  LEDControl,
  LEDOff,
  LEDBreatheEffect,
  StalkerEffect,
  LEDRainbowEffect,
  LEDRainbowWaveEffect,
  solidRed, solidOrange, solidYellow, solidGreen, solidBlue, solidIndigo, solidViolet,
  NumPad,

  // Other Plugins
  EscapeOneShot,
  HostPowerManagement,
  Hyper,
  Macros,
  MagicCombo,
  MouseKeys,
  ToughLove
);

namespace paulshir {
void setup() {
  Serial.begin(9600);
  Kaleidoscope.setup();

  QUKEYS(
    kaleidoscope::Qukey(MIRROR, 3, 7, Key_LeftControl),
    kaleidoscope::Qukey(MIRROR, 3, 8, Key_RightControl),
    kaleidoscope::Qukey(QWERTY, 0, 0, Key_Hyper)
  )

  // LED Effect Settings
  ActiveModColorEffect.highlight_color = CRGB(0, 255, 255);
  ActiveModColorEffect.sticky_color = CRGB(0, 255, 150);
  BootGreetingEffect.key_col = 0;
  BootGreetingEffect.key_row = 0;
  LEDBreatheEffect.hue = 50;
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);
  NumPad.numPadLayer = NUMPAD;
  StalkerEffect.variant = STALKER(Haunt, (CRGB(255, 100, 225)));
  StalkerEffect.breath_hue = 205;

  MagicCombo.magic_combos = magic_combos;
  MouseKeys.speed = 2;
  MouseKeys.accelSpeed = 5;
  MouseKeys.accelDelay = 20;

  LEDOff.activate();
}

}  // namespace paulshir
