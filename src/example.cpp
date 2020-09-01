#include "String.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
    String s;
    std::cin >> s;
    std::cout << s;

    return 0;

    std::vector<String> v;

    while (std::cin >> s) {
       v.push_back(s);
    }

    std::sort(v.rbegin(), v.rend());

    std::copy(std::begin(v), std::end(v), std::ostream_iterator<String> {std::cout, "\n"});
    std::cout << std::endl;
}
