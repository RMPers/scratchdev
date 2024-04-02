#include <memory>
#include <iostream>

void take_unique(std::unique_ptr<int> p) {
  std::cout << "p = " << p << std::endl;
  std::cout << "p points to " << *p << std::endl;
}

int main (void) {
  std::cout << "Hello smartpointers!" << std::endl;

  int* a = new int(10);
  std::unique_ptr<int> a_ptr = std::unique_ptr<int>(a);
  std::cout << "a = " << a << std::endl;
  std::cout << "a_ptr = " << a_ptr << std::endl;
  std::cout << "ptr a points to " << *a_ptr << std::endl;
  *a_ptr = 20;
  std::cout << "ptr a points to " << *a_ptr << std::endl;

  // Here we pass the unique_ptr to a function which is supposed to consume it.
  // Omitting the std::move will give compile error.
  take_unique(std::move(a_ptr));

  // Now the 'a_ptr' is no longer managing 'a'
  std::cout << "a_ptr = " << a_ptr << std::endl;
  // Next line would trigger 'Segmentation fault'
  //std::cout << "ptr a points to " << *a_ptr << std::endl;
    
  return EXIT_SUCCESS;
}
