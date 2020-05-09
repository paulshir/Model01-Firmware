/* -*- mode: c++ -*-
 * Mirror.h -- Send the mirrored key from the other half of the board.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#pragma once

#include "../key-defs-local.h"
#include <Kaleidoscope.h>

constexpr uint8_t kMirroredCol(KeyAddr key_addr) { return Kaleidoscope.device().matrix_columns - 1 - key_addr.col(); }

namespace kaleidoscope {
namespace plugin {
class Mirror : public kaleidoscope::Plugin {
 public:
  Mirror(void) {}

  typedef void(*MirrorKeyToggledOnFunc)(Key &mapped_key, KeyAddr mir_key_addr);
  static void setMirroredKeyToggledOnFunc(MirrorKeyToggledOnFunc func);
  EventHandlerResult onKeyswitchEvent(Key &mapped_key, KeyAddr key_addr, uint8_t key_state);

 private:
  static bool mirror_key_pressed_;
  static MirrorKeyToggledOnFunc onMirrorKeyToggledOn;
  static void defaultOnMirroredKeyToggledOn(Key &mapped_key, KeyAddr mir_keykey_addr);

};

}  // namespace plugin
}  // namespace kaleidoscope

extern kaleidoscope::plugin::Mirror Mirror;
