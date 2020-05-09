#include "KeyAddrStore.h"

namespace paulshir {

KeyAddrStore::KeyAddrStore() {
  this->KeyAddrStore::store_[Kaleidoscope.device().matrix_rows];
  this->clear();
}

void KeyAddrStore::store(KeyAddr keyAddr) {
  store_[keyAddr.row()] |= scanbit(keyAddr.col());
}

void KeyAddrStore::remove(KeyAddr keyAddr) {
  store_[keyAddr.row()] &= ~scanbit(keyAddr.col());
}

void KeyAddrStore::clear() {
  for (uint16_t i = 0; i < Kaleidoscope.device().matrix_rows; i++) {
    store_[i] = 0;
  }
}

bool KeyAddrStore::isStored(KeyAddr keyAddr) {
  return (store_[keyAddr.row()] & scanbit(keyAddr.col())) > 0;
}

bool KeyAddrStore::isClear() {
  for (uint16_t i = 0; i < Kaleidoscope.device().matrix_rows; i++) {
    if (store_[i] != 0) {
      return false;
    }
  }

  return true;
}

}  // namespace paulshir
