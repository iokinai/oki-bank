#include "okijthread.hxx"

namespace okibank {
std::thread::id okijthread::get_id() const noexcept {
  return this->thread.get_id();
}
const std::thread &okijthread::get_std_thread() const noexcept {
  return this->thread;
}
} // namespace okibank