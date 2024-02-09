#include "okimutex.hxx"

namespace okibank {

okimutex::okimutex() : locked(false) {
}

void okimutex::lock() {
  while (this->locked)
    ;

  this->locked = true;
}

bool okimutex::try_lock() noexcept {
  return !locked.exchange(true, std::memory_order_acquire);
}

void okimutex::unlock() noexcept {
  this->locked = false;
}

} // namespace okibank