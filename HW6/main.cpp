#include "Format.h"

#include <iostream>


int main() {
    std::cout << format("{1}+{1} = {0}", 2, "one");
    return 0;
}
