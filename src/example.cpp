#include "String.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
    std::vector<String> v;

    String s;
    while (std::cin >> s) {
       v.push_back(s);
    }

    std::sort(v.begin(), v.end());
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<String> {std::cout, "\n"});
    std::cout << std::endl;
}
