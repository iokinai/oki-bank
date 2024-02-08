#include <atomic>

namespace okibank {
struct okimutex {
private:
  std::atomic<bool> locked;

public:
  okimutex();
  okimutex(const okimutex &) = delete;
  okimutex(okimutex &&) = delete;
  void lock();
  bool try_lock() noexcept;
  void unlock() noexcept;
};
} // namespace okibank