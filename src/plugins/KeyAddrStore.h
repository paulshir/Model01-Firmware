#pragma once

#include <Kaleidoscope.h>

constexpr uint16_t scanbit(uint16_t offset) { return (uint16_t)1 << offset; }
static_assert(scanbit(0) == (uint16_t) 1, "Bit check");
static_assert(scanbit(1) == (uint16_t) 2, "Bit check");
static_assert(scanbit(2) == (uint16_t) 4, "Bit check");
static_assert(Kaleidoscope.device().matrix_rows == 4, "Expected 4 rows");

namespace paulshir {
class KeyAddrStore {
 public:
  KeyAddrStore();
  void store(KeyAddr keyAddr);
  void remove(KeyAddr keyAddr);
  void clear();
  bool isStored(KeyAddr keyAddr);
  bool isClear();

 private:
  uint16_t store_[Kaleidoscope.device().matrix_rows];
};
}  // namespace paulshir