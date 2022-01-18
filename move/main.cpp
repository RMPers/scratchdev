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
        std::cout << "copy assignement constructor(const&)\n";
        return *this;
    }
    Myclass(Myclass &&_x) : a(_x.a) {
        _x.a = 0;
        std::cout << "move constructor(int&&)\n";
    }
    Myclass &operator=(const Myclass &&_x) {
        a = _x.a;
        std::cout << "move assignement constructor(const&&)\n";
        return *this;
    }

    int a;
};

Myclass foo(Myclass x);

Myclass bar(Myclass &x);

int main() {
    Myclass a{10}; // Create and initalize a.a = 10 using direct
    std::cout << "a=" << a.a << "!\n\n";

    Myclass b(std::move(a)); // Creates b using move constructor which steals value from a.
    std::cout << "a=" << a.a << "!\n";
    std::cout << "b=" << b.a << "!\n\n";

    Myclass aref = a;
    Myclass bvar{aref}; // Creates bvar using copy constructor (same as bvar{a})
    bvar = b; // Copies bvar using copy assignement constructor.
    std::cout << "bvar=" << bvar.a << "!\n\n";
    a.a = 100;

    bvar = std::move(a); // assigns bvar using move assignement constructor
    std::cout << "bvar=" << bvar.a << "!\n\n";
    
    Myclass c = foo(b); // pass b as lvalue which will trigger copy construction of x. Copy construction on return
    std::cout << "b=" << b.a << "!\n";
    std::cout << "c=" << c.a << "!\n\n";

    c = bar(b); // pass b as lvalue ref which omit copy construction of x. bar
                // will work directly on b. Move assignement on return
    std::cout << "b=" << b.a << "!\n";
    std::cout << "c=" << c.a << "!\n\n";

    int &&z{42}; // declare a rvalue ref z referring to 42
    auto &&zref = z; // zref becomes lvalue ref (int&)
    std::cout << "zref=" << zref << "\n";
    return 0;
}

Myclass foo(Myclass x) {
    Myclass y(x.a + 10);
    x.a = 5;
    return y;
}

Myclass bar(Myclass &x) {
    Myclass y(x.a + 10);
    x.a = 5;
    return y;
}
