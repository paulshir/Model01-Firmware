/* -*- mode: c++ -*-
 * FlipFlop.cpp
 * Copyright (C) 2020  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#include "Volley.h"

namespace kaleidoscope {
namespace plugin {

Volley::ModeDeciderFunc Volley::modeDecider = Volley::defaultModeDecider;

Volley::Volley(Key trigger_key_1, Key trigger_key_2) {
    this->active_ = true;
    this->trigger_key_1_ = trigger_key_1;
    this->trigger_key_2_ = trigger_key_2;
    this->secondary_mode_key_ = 0;

    this->state_ = VolleyState::READY;
    this->trigger_state_ = VolleyTriggerState::SEND_AND_REVERT;

    this->trigger_key_addr_ = 0;
}

void Volley::activate() {
    active_ = true;
}

void Volley::deactivate() {
    active_ = false;
}

bool Volley::isActive() {
    return active_;
}

void Volley::blockTriggerUntilDecided(bool block) {
    if (block) {
        trigger_state_ = VolleyTriggerState::BLOCK_UNTIL_DECIDED;
    } else {
        trigger_state_ = VolleyTriggerState::SEND_AND_REVERT;
    }
}

void Volley::overrideModeDeciderFunction(Volley::ModeDeciderFunc modeDeciderFunc) {
    modeDecider = modeDeciderFunc;
}

void Volley::setSecondaryModeBlocked() {
    secondary_mode_key_ = 0;
}

void Volley::setSecondaryModeShiftToLayer(uint8_t layer) {
    secondary_mode_key_ = ShiftToLayer(layer);
}

void Volley::setSecondaryModePressKey(Key key) {
    secondary_mode_key_ = key;
}

EventHandlerResult Volley::onKeyswitchEvent(Key &mapped_key, KeyAddr key_addr, uint8_t key_state) {
    if ((!active_ && state_ == VolleyState::READY) || (key_state & INJECTED) || state_ == VolleyState::SKIP) {
        return EventHandlerResult::OK;
    }

    EventHandlerResult handlerResult = EventHandlerResult::OK;
    VolleyState old_state = state_;
    if (keyToggledOn(key_state)) {
        if (old_state == VolleyState::READY) {
            if (mapped_key == trigger_key_1_ || mapped_key == trigger_key_2_) {
                state_ = VolleyState::TRIGGERED;
                trigger_key_addr_ = key_addr;
            }
        }

        if (old_state == VolleyState::TRIGGERED) {
            ModeDeciderResult decision = modeDecider(mapped_key, key_addr, trigger_key_addr_);
            if (decision == ModeDeciderResult::PRIMARY_MODE) {
                handlerResult = activatePrimaryMode(mapped_key, key_addr);
            } else if (decision == ModeDeciderResult::SECONDARY_MODE) {
                handlerResult = activateSecondaryMode(mapped_key, key_addr);
            } // No action required for IGNORED
        }

        if (old_state == VolleyState::PRIMARY_FUNCTION_ACTIVE) {
            if ((secondary_mode_key_ != 0) && (mapped_key == trigger_key_1_ || mapped_key == trigger_key_2_)) {
                Layer.updateLiveCompositeKeymap(key_addr, secondary_mode_key_);
                mapped_key.setRaw(secondary_mode_key_.getRaw());
            }
        }
    }

    if (key_addr == trigger_key_addr_) {
        if (keyToggledOff(key_state) && old_state != VolleyState::READY) {
            state_ = VolleyState::READY;

            if (old_state == VolleyState::TRIGGERED && trigger_state_ == VolleyTriggerState::BLOCK_UNTIL_DECIDED) {
                trigger_state_ = VolleyTriggerState::SEND_TRIGGER_IS_PRESSED;
            }
        }

        if (old_state <= VolleyState::TRIGGERED && trigger_state_ != VolleyTriggerState::SEND_AND_REVERT) {
            handlerResult = EventHandlerResult::EVENT_CONSUMED;
        }
    }

    return handlerResult;
}

EventHandlerResult Volley::beforeReportingState() {
    if (trigger_state_ == VolleyTriggerState::SEND_TRIGGER_IS_PRESSED || trigger_state_ == VolleyTriggerState::SEND_TRIGGER_WAS_PRESSED) {
        Volley::VolleyState old_state = state_;
        state_ = VolleyState::SKIP;

        if (trigger_state_ == VolleyTriggerState::SEND_TRIGGER_IS_PRESSED) {
            handleKeyswitchEvent(Key_NoKey, trigger_key_addr_, IS_PRESSED);
            trigger_state_ = VolleyTriggerState::SEND_TRIGGER_WAS_PRESSED;
        } else {
            handleKeyswitchEvent(Key_NoKey, trigger_key_addr_, WAS_PRESSED);
            trigger_state_ = VolleyTriggerState::BLOCK_UNTIL_DECIDED;
        }

        state_ = old_state;
    }

    return EventHandlerResult::OK;
}

EventHandlerResult Volley::activatePrimaryMode(Key &mapped_key, KeyAddr key_addr) {
    if (trigger_state_ == VolleyTriggerState::SEND_AND_REVERT) {
        if ((secondary_mode_key_ != 0) && (mapped_key == trigger_key_1_ || mapped_key == trigger_key_2_)) {
            Layer.updateLiveCompositeKeymap(key_addr, secondary_mode_key_);
            mapped_key.setRaw(secondary_mode_key_.getRaw());
        }

        state_ = VolleyState::PRIMARY_FUNCTION_ACTIVE;
        return EventHandlerResult::OK;
    }

    state_ = VolleyState::SKIP;
    handleKeyswitchEvent(Key_NoKey, trigger_key_addr_, IS_PRESSED);
    Key updatedKey = Layer.lookupOnActiveLayer(key_addr);

    if ((secondary_mode_key_ != 0) && (updatedKey == trigger_key_1_ || updatedKey == trigger_key_2_)) {
        updatedKey.setRaw(secondary_mode_key_.getRaw());
    }

    handleKeyswitchEvent(updatedKey, key_addr, IS_PRESSED);
    state_ = VolleyState::PRIMARY_FUNCTION_ACTIVE;

    return EventHandlerResult::EVENT_CONSUMED;
}

EventHandlerResult Volley::activateSecondaryMode(Key &mapped_key, KeyAddr key_addr) {
    if (secondary_mode_key_ == 0) {
        // Update the liveCompositeMap so that future events on this key_addr will be represented correctly.
        Layer.updateLiveCompositeKeymap(key_addr, Key_NoKey);
        // We don't want to block the whole keyboard, so we just swallow this key event without updating the state.
        return EventHandlerResult::EVENT_CONSUMED;
    }

    /* These steps are done in a particular order to set the keyboard in the desired state.
     * It makes for a simple solution, as it sets the state, and delegates handling of any
     * new keys to the Layers class natively.
     * 
     * We set the state to SKIP so that these events will not be processed by this plugin. Then we send the following
     * events:
     *   - A key up event on the original modifier. This gets the current value from the liveCompositeMap.
     *   - A key down event on the secondary mode modifier. This will apply any modifications such as layer changes, and store this key in the liveCompositeMap.
     *   - A key down event on the key address of the decider key. We need to do a manual lookup initially so we can update the liveCompositeMap.
     * 
     * After this is complete we set the state correctly. All future events on these keys, until they are released, will read from the Key value from the liveCompositeMap.
     *
     */
    state_ = VolleyState::SKIP;
    handleKeyswitchEvent(Key_NoKey, trigger_key_addr_, WAS_PRESSED | INJECTED);
    handleKeyswitchEvent(secondary_mode_key_, trigger_key_addr_, IS_PRESSED);
    handleKeyswitchEvent(Layer.lookupOnActiveLayer(key_addr), key_addr, IS_PRESSED);
    state_ = VolleyState::SECONDARY_FUNCTION_ACTIVE;

    return EventHandlerResult::EVENT_CONSUMED;
}

Volley::ModeDeciderResult Volley::defaultModeDecider(Key &mapped_key, KeyAddr key_addr, KeyAddr trigger_key_addr) {
    if ((trigger_key_addr.col() < kColSplit) ^ (key_addr.col() < kColSplit)) {
        return ModeDeciderResult::PRIMARY_MODE;
    }

    return ModeDeciderResult::SECONDARY_MODE;
}

}  // namespace plugin
}  // namespace kaleidoscope

kaleidoscope::plugin::Volley Volley;
