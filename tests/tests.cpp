#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE StringTest
#include <boost/test/unit_test.hpp>
#include "String.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(test_default_constructor)
{
    String s;
    BOOST_CHECK_EQUAL(s, "");
    BOOST_CHECK_EQUAL(s.length(), 0);
}

BOOST_AUTO_TEST_CASE(test_cstr_constructor)
{
    const char* some_str = "Test";
    String s1(some_str);
    BOOST_CHECK_EQUAL(s1, some_str);

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
    BOOST_CHECK_EQUAL(s1, valid_s);
    BOOST_CHECK_EQUAL(s1.length(), valid_s.length());

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
    BOOST_CHECK_NE(s1, s2);
    BOOST_CHECK_EQUAL(s2, "Test");
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
    BOOST_CHECK_EQUAL(s3, "Hello World!");

    String s4 = "Hello ";
    const char* cstr = "World!";

    String s5 = s4 + cstr;
    BOOST_CHECK_EQUAL(s5, "Hello World!");

    String s6 = cstr + s4;
    BOOST_CHECK_EQUAL(s6, "World!Hello ");
}

BOOST_AUTO_TEST_CASE(test_push_back)
{
    String s1("Hello "); // len=6 cap=7

    BOOST_CHECK_EQUAL(s1.size(), 7);
    BOOST_CHECK_EQUAL(s1.length(), 6);

    s1.push_back('m'); // len=7 cap=7
    s1.push_back('y'); // len=8 cap=7*2=14

    BOOST_CHECK_EQUAL(s1.length(), 8);
    BOOST_CHECK_EQUAL(s1.size(), 14);

    s1.push_back(' '); // len=9 cap=14
    s1.push_back('p'); // len=10 cap=14
    s1.push_back('o'); // len=11 cap=14
    s1.push_back('n'); // len=12 cap=14
    s1.push_back('y'); // len=13 cap=14
    s1.push_back('!'); // len=14 cap=14
    s1.push_back('!'); // len=15 cap=14*2=28

    BOOST_CHECK_EQUAL(s1.length(), 15);
    BOOST_CHECK_EQUAL(s1.size(), 28);
    BOOST_CHECK_EQUAL(s1, "Hello my pony!!");
}

BOOST_AUTO_TEST_CASE(test_reserve)
{
    String s1("TEST");

    BOOST_CHECK_EQUAL(s1.size(), 5);
    BOOST_CHECK_EQUAL(s1.length(), 4);
    BOOST_CHECK_EQUAL(s1, "TEST");

    const size_t new_size = 100;
    s1.reserve(new_size);

    BOOST_CHECK_EQUAL(s1.size(), new_size);
    BOOST_CHECK_EQUAL(s1.length(), 4);
    BOOST_CHECK_EQUAL(s1, "TEST");
}

BOOST_AUTO_TEST_CASE(test_reserve_for_moved_string)
{
    String s1;
    s1.reserve(10);

    BOOST_CHECK_EQUAL(s1.size(), 10);
    BOOST_CHECK_EQUAL(s1.length(), 0);

    String s2(std::move(s1));

    BOOST_CHECK_EQUAL(s2.size(), 10);
    BOOST_CHECK_EQUAL(s2.length(), 0);

    BOOST_CHECK_EQUAL(s1.size(), 0);
    BOOST_CHECK_EQUAL(s1.length(), 0);

    s1.push_back('H');
    s1.push_back('e');
    s1.push_back('l');
    s1.push_back('l');
    s1.push_back('o');
    s1.push_back('!');

    BOOST_CHECK_EQUAL(s1, "Hello!");
    BOOST_CHECK_EQUAL(s1.size(), 8);
    BOOST_CHECK_EQUAL(s1.length(), 6);
}

BOOST_AUTO_TEST_CASE(test_append)
{
    String s1("Hello, ");
    const char* s = "my little ";
    String S("Pony!");

    s1.append(s);
    BOOST_CHECK_EQUAL(s1, "Hello, my little ");

    s1.append(S);
    BOOST_CHECK_EQUAL(s1, "Hello, my little Pony!");
}

BOOST_AUTO_TEST_CASE(test_iterator)
{
    String s1("Hello");
    String s2, s3, s4, s5;

    for (String::const_iterator it = s1.begin(); it != s1.end(); it++) {
        s2.push_back(*it);
    }

    BOOST_CHECK_EQUAL(s1, s2);

    for (auto it = s1.begin(); it != s1.end(); it++) {
        s3.push_back(*it);
    }

    BOOST_CHECK_EQUAL(s1, s3);

    for (auto it = std::begin(s1); it != std::end(s1); it++) {
        s4.push_back(*it);
    }

    BOOST_CHECK_EQUAL(s1, s4);

    for (const auto c : s1) {
        s5.push_back(c);
    }

    BOOST_CHECK_EQUAL(s1, s5);
}


BOOST_AUTO_TEST_SUITE_END()
