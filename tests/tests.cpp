#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE StringTest
#include <boost/test/unit_test.hpp>
#include "String.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(test_default_constructor)
{
    String s;
    BOOST_CHECK(s == "");
    BOOST_CHECK(s.length() == 0);
}

BOOST_AUTO_TEST_CASE(test_cstr_constructor)
{
    const char* some_str = "Test";
    String s1(some_str);
    BOOST_CHECK(s1 == some_str);

    try {
        String s2(nullptr);
    } catch (std::exception& e) {
        BOOST_CHECK(std::strcmp(e.what(), "String: Invalid construct argument\n"));
    }
}

BOOST_AUTO_TEST_CASE(test_copy_constructor)
{
    String valid_s("Test");
    String s1(valid_s);
    BOOST_CHECK(s1 == valid_s);
    BOOST_CHECK(s1.length() == valid_s.length());

    try {
        String invalid_s(nullptr);
        String s2(s1);
    } catch (std::exception& e) {
        BOOST_CHECK(std::strcmp(e.what(), "String: Invalid construct argument\n"));
    }
}

BOOST_AUTO_TEST_CASE(test_move_constructor)
{
    String s1("Test");
    String s2(std::move(s1));
    BOOST_CHECK(s2.empty());
    BOOST_CHECK(s1 != s2);
    BOOST_CHECK(s2 == "Test");
}

BOOST_AUTO_TEST_CASE(test_eq_operator)
{
    String s1 = "Test";
    String s2 = s1;
    BOOST_CHECK(s1 == s2);
}

BOOST_AUTO_TEST_CASE(test_plus_operator)
{
    String s1 = "Hello ";
    String s2 = "World!";
    String s3 = s1 + s2;
    BOOST_CHECK(s3 == "Hello World!");

    String s4 = "Hello ";
    const char* cstr = "World!";

    String s5 = s4 + cstr;
    BOOST_CHECK(s5 == "Hello World!");

    String s6 = cstr + s4;
    BOOST_CHECK(s6 == "World!Hello ");
}

BOOST_AUTO_TEST_SUITE_END()
