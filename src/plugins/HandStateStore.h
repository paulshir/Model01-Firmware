#pragma once

#include <Kaleidoscope.h>

#define COLS_SPLIT COLS/2

namespace paulshir {
class HandStateStore {
 public:
  HandStateStore();
  void setState(byte row, byte col);
  void unsetState(byte row, byte col);
  void clearState();
  bool getState(byte row, byte col);
  bool isClear();

 private:
  uint32_t left_hand_;
  uint32_t right_hand_;
};
}  // namespace paulshir