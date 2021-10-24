#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <lttng/tracef.h>
#include "submodule/submodule.h"


int main(int argc, char* argv[])
{
  std::vector<std::thread> thread_pool;

  int iterations = 10;
  int sleep_duration = 1000000; //ns

  int sum = sub_add(10, 20);
  std::cout << "sum = " << sum << std::endl;
  
  if (argc > 1)
      iterations = atoi(argv[1]);

  if (argc > 2)
      sleep_duration = atoi(argv[2]);

  for (int i = 0; i < iterations; i++)
  {
      tracef("LTTNG: Iteration %d", i);
      if (sleep_duration > 0) // minium sleep time seems to be ~50 us when calling sleep
      {
          std::this_thread::sleep_for(std::chrono::nanoseconds(sleep_duration));
      }
  }

  std::cout << iterations <<" iterations completed. sleep " << sleep_duration << " ns\n";
  return 0;
}
