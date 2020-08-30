#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE StringTest
#include <boost/test/unit_test.hpp>
#include "String.h"

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(FirstTest)
{
    String string;
    BOOST_REQUIRE(string.test() == 42);
}


BOOST_AUTO_TEST_CASE(SecondTest)
{
    String string;
    BOOST_REQUIRE(string.test() != 42);
}

BOOST_AUTO_TEST_SUITE_END()
