#include <iostream>
#include <vector>
#include <string>

void test_move(std::string& a) {
    /* Transfer the sources of a varialbe */
    std::vector<std::string> str_vct;

    std::cout << "a before std::move: " << a.c_str() << std::endl;

    str_vct.push_back(std::move(a));

    std::cout << "a after std::move: " << a.c_str() << std::endl;
    std::cout << "str_vct[0]: " << str_vct[0].c_str() << std::endl;
}

int32_t main() {
    std::string a = "XXX";
    test_move(a);
    return 0;
}