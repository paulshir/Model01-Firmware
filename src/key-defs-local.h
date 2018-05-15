/* -*- mode: c++ -*-
 * key-defs-local.h -- Some local key definitions
 * Copyright (C) 2018  Paul Shirley
 *
 * See "LICENSE" for license details
 */
#pragma once

#include <Kaleidoscope.h>
#include <Kaleidoscope-Ranges.h>

namespace paulshir {
namespace ranges {

enum : uint16_t {
  FIRST = kaleidoscope::ranges::KALEIDOSCOPE_SAFE_START + 255,
  MIRROR,
  SAFE_START
};

}
}

#define Key_Prog      Key_NoKey
#define Key_Hyper     Key_RightGui
// #define Key_Hyper     LSHIFT(LALT(LGUI(Key_LeftControl)))
#define MacOS_Sleep   LSHIFT(LCTRL(Key_Power))
#define Key_Mirror    (Key) {.raw = paulshir::ranges::MIRROR}
