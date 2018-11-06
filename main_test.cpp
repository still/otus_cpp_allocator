#include "lib.h"

#define BOOST_TEST_MODULE project_test

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_allocator)
{
    auto p1 = make_pair(5, 120UL);
    BOOST_CHECK(factorial(p1.first) == p1.second);

    auto p2 = make_pair(0, 1UL);
    BOOST_CHECK(factorial(p2.first) == p2.second);

    auto p3 = make_pair(1, 1UL);
    BOOST_CHECK(factorial(p3.first) == p3.second);
}

BOOST_AUTO_TEST_SUITE_END()
