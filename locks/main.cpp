#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

struct tas_lock {
    std::atomic<bool> lock_ = {false};
    int bbx_lock_ = 0;

    void lock() { while(lock_.exchange(true, std::memory_order_acquire)); }

    void lock_fast() {
        for (;;) {
            if (!lock_.exchange(true, std::memory_order_acquire)) {
                break;
            }
            while (lock_.load(std::memory_order_relaxed));
        }
    }

    void lock_bbx() {
        do {
            int expected = 0;
            if (__atomic_compare_exchange_n(&bbx_lock_, &expected, 1,
                                            0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
                break;
            }
        }
        while (1);
    }
    void unlock_bbx() {
        bbx_lock_ = 0;
    }
                
    void unlock() { lock_.store(false, std::memory_order_release); }
};

static tas_lock lock;
static int counter = 0;
void Threadfunc()
{
    for (int i = 0; i < 10000; i++)
    {
        lock.lock_fast();
        //lock.lock_bbx();
        counter++;
        //std::cout << "Thread id " << std::this_thread::get_id() << ", counter " << counter << std::endl;
        lock.unlock();
        //lock.unlock_bbx();
    }
}

int main()
{
    std::vector<std::thread> thread_pool;

    for (int i = 0; i < 50; i++)
    {
        thread_pool.push_back(std::thread(Threadfunc));
    }

    for (auto &t: thread_pool)
    {
        //std::cout << "joining " << t.get_id() << std::endl;
        t.join();
    }

    std::cout << "counter = " << counter << std::endl;

    return 0;
}
