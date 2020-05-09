/* -*- mode: c++ -*-
 * Mirror.cpp -- Send the mirrored key from the other half of the board.
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#include "Mirror.h"

namespace kaleidoscope {
namespace plugin {

bool Mirror::mirror_key_pressed_ = false;
Mirror::MirrorKeyToggledOnFunc Mirror::onMirrorKeyToggledOn = defaultOnMirroredKeyToggledOn;

void Mirror::setMirroredKeyToggledOnFunc(Mirror::MirrorKeyToggledOnFunc func) {
  onMirrorKeyToggledOn = func;
}

EventHandlerResult Mirror::onKeyswitchEvent(Key &mapped_key, KeyAddr key_addr, uint8_t key_state) {
  // Check if the mirror key is pressed
  if (mapped_key.getRaw() == Key_Mirror.getRaw()) {
    if (keyToggledOn(key_state)) {
      mirror_key_pressed_ = true;
    } else if (keyToggledOff(key_state)) {
      mirror_key_pressed_ = false;
    }

    return EventHandlerResult::EVENT_CONSUMED;
  }

  if (!mirror_key_pressed_ || !key_addr.isValid() || key_state & INJECTED) {
    return EventHandlerResult::OK;
  }

  if (keyToggledOn(key_state)) {
    KeyAddr mir_key_addr = key_addr;
    mir_key_addr.setCol(kMirroredCol(key_addr.col()));
    Key mir_key = Layer.lookupOnActiveLayer(mir_key_addr);
    Layer.updateLiveCompositeKeymap(key_addr, mir_key);
    mapped_key.setRaw(mir_key.getRaw());
    onMirrorKeyToggledOn(mapped_key, mir_key_addr);
  }
  
  return EventHandlerResult::OK;
}

void Mirror::defaultOnMirroredKeyToggledOn(Key &mapped_key, KeyAddr mir_key_addr) {}

}  // namespace plugin
}  // namespace kaleidoscope

kaleidoscope::plugin::Mirror Mirror;
