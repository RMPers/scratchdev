#include <memory>

struct tas_lock {
  std::atomic<bool> lock_ = {false};

  void lock() { while(lock_.exchange(true)); }

  void unlock() { lock_.store(false); }
};
