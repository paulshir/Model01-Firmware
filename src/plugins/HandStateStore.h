#pragma once

#include <Kaleidoscope.h>

#define COLS_SPLIT COLS/2
#define SCANBIT(row,col) ((uint32_t)1 << ((row) * 8 + (7 - (col))))

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