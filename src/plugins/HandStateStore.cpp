#include "HandStateStore.h"

namespace paulshir {

HandStateStore::HandStateStore() {
  this->HandStateStore::left_hand_ = 0;
  this->HandStateStore::right_hand_ = 0;
}

void HandStateStore::setState(byte row, byte col) {
  if (col < COLS_SPLIT) {
    left_hand_ |= SCANBIT(row, col);
  } else {
    right_hand_ |= SCANBIT(row, col - COLS_SPLIT);
  }
}

void HandStateStore::unsetState(byte row, byte col) {
  if (col < COLS_SPLIT) {
    left_hand_ &= ~SCANBIT(row, col);
  } else {
    right_hand_ &= ~SCANBIT(row, col - COLS_SPLIT);
  }
}

void HandStateStore::clearState() {
  left_hand_ = 0;
  right_hand_ = 0;
}

bool HandStateStore::getState(byte row, byte col) {
  if (col < COLS_SPLIT) {
    return left_hand_ & SCANBIT(row, col);
  } else {
    return right_hand_ & SCANBIT(row, col - COLS_SPLIT);
  }
}

bool HandStateStore::isClear() {
  return left_hand_ == 0 && right_hand_ == 0;
}

}  // namespace kaleidoscope
