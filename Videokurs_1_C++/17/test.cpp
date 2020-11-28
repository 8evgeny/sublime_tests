#define BOOST_TEST_MODULE test_module

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

    BOOST_AUTO_TEST_CASE(test_valid_version)
    {
        BOOST_CHECK(0 > 0);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_fopen)

    BOOST_AUTO_TEST_CASE(test_qwe_version)
    {
        BOOST_CHECK(0 > 0);
        BOOST_CHECK_EQUAL(2, 3);
        BOOST_REQUIRE(0 > 0);
    }

    BOOST_AUTO_TEST_CASE(test_qwe2_version)
    {
        BOOST_CHECK(0 > 0);
    }

BOOST_AUTO_TEST_SUITE_END()
