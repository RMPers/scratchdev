#include <iostream>
#include <cmath>
#include <string>

int main (void)
{
    auto c1 = 10;
    std::cout << "c1 = " << c1 << std::endl;

    int c2 = 10;
    std::cout << "c2 = " << c2 << std::endl;

    float r = std::log(77);
    std::cout << "r = " << r << std::endl;

    std::string str{"hello world!"};
    std::cout << str << std::endl;

    int op1 = 7;
    int op2 = 42;
    int res = op1 * op2;
    std::cout << "mult res = " << res << std::endl;

    for (int i = 0; i<5; i++){
        op1 = op1 + i;
    }
    std::cout << "add res = " << op1 << std::endl;

    return 0;
}
