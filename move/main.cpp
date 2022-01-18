// Example program
#include <iostream>
#include <memory>
#include <string>

class Myclass {
public:
    Myclass() {
        a = 0;
        std::cout << "value constructor()\n";
    }
    Myclass(int _v) : a(_v) { std::cout << "direct constructor(int)\n"; }
    Myclass(const Myclass &_x) : a(_x.a) { std::cout << "copy constructor(const&)\n"; }
    Myclass &operator=(const Myclass &_x) {
        a = _x.a;
        std::cout << "copy assignement constructor(&)\n";
        return *this;
    }
    Myclass(Myclass &&_x) : a(_x.a) {
        _x.a = 0;
        std::cout << "move constructor(int&&)\n";
    }
    Myclass &operator=(const Myclass &&_x) {
        a = _x.a;
        std::cout << "move assignement constructor(&&)\n";
        return *this;
    }

    int a;
};

int foo(Myclass x);

int bar(Myclass &x);

int main() {
    Myclass a{10}; // Create and initalize a.a = 10 using direct
    std::cout << "a=" << a.a << "!\n\n";

    Myclass b(std::move(a)); // Creates b using move constructor which steals value from a.
    std::cout << "a=" << a.a << "!\n";
    std::cout << "b=" << b.a << "!\n\n";
    
    Myclass bvar{0}; // Creates bvar using direct constructor
    bvar = b; // Copies bvar using copy assignement constructor.
    std::cout << "bvar=" << bvar.a << "!\n\n";
    
    int c = foo(b); // pass b as lvalue which will trigger copy construction of x
    std::cout << "b=" << b.a << "!\n";
    std::cout << "c=" << c << "!\n\n";

    c = bar(b); // pass b as lvalue ref which omit copy construction of x. bar
                // will work directly on b
    std::cout << "b=" << b.a << "!\n";
    std::cout << "c=" << c << "!\n\n";

    int &&z{42}; // declare a rvalue ref z referring to 42
    auto &&zref = z; // zref becomes lvalue ref (int&)
    std::cout << "zref=" << zref << "\n";
    return 0;
}

int foo(Myclass x) {
    int y = x.a + 10;
    x.a = 5;
    return y;
}

int bar(Myclass &x) {
    int y = x.a + 10;
    x.a = 5;
    return y;
}
