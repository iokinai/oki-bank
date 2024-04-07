#ifndef THREAD_OKIJTHREAD_HXX
#define THREAD_OKIJTHREAD_HXX

#include <thread>

namespace okibank {

class okijthread {
private:
  std::thread thread;

public:
  template <class Function>
  explicit okijthread(Function &&f) : thread(std::thread(f)) {
    this->thread.join();
  }

  okijthread(okijthread &&) = delete;
  okijthread(const okijthread &) = delete;

  std::thread::id get_id() const noexcept;
  const std::thread &get_std_thread() const noexcept;
};

} // namespace okibank

#endif