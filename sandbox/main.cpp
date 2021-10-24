#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <lttng/tracef.h>

class Base {
  public:
  Base(){}
  explicit Base(int v)
    : value_(v)
  {}

  void PrintBase()
  {
    std::cout << "Value = " << value_ << std::endl;
  }
  private:
  int value_; 
};

class Derived : public Base {
  std::string name_;
  char* my_char_p;
  public:
  Derived() // using this constructure would implicitly call Base::Base()
    : name_("No name")
  {}
  Derived(std::string string)
    : Base::Base(5) // using this constructor would call Base::Base(int)
  {
    name_ = string;
    my_char_p = reinterpret_cast<char*>(std::malloc(10));
  }
  void PrintDerived()
  {
    std::cout << name_ << std::endl;
  }
  ~Derived()
  {
    std::free(my_char_p);
  }
};

void PrintGarbage()
{
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2.0s);
  std::cout << "Printing some garbage\n";
  tracef("Printing from thread");
}


int main(void)
{
  std::vector<std::thread> thread_pool;

  std::cout << "start program by hitting enter\n";
  std::cin.get();

  for (int i = 0; i < 10; i++)
  {
    //thread_pool.push_back(std::thread(PrintGarbage));
    thread_pool.push_back(std::thread(PrintGarbage));
    std::cout << "Created thread " << thread_pool.at(i).get_id() << "size of thread_pool=" << thread_pool.size() << std::endl;
    tracef("LTTNG: Created thread %d",thread_pool.at(i).get_id());
  }

  for (auto &t: thread_pool)
  {
    std::cout << "joining " << t.get_id() << std::endl;
    t.join();
  }

  std::cin.get();
  return 0;
}
