#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "util.h"

BOOST_AUTO_TEST_SUITE(getarg_tests)

static void
ResetArgs(const std::string& strArg)
{
    std::vector<std::string> vecArg;
    boost::split(vecArg, strArg, boost::is_space(), boost::token_compress_on);

    // Insert dummy executable name:
    vecArg.insert(vecArg.begin(), "testbitcoin");

    // Convert to char*:
    std::vector<const char*> vecChar;
    BOOST_FOREACH(std::string& s, vecArg)
        vecChar.push_back(s.c_str());

    ParseParameters(vecChar.size(), &vecChar[0]);
}

BOOST_AUTO_TEST_CASE(boolarg)
{
    ResetArgs("-selit");
    BOOST_CHECK(GetBoolArg("-selit"));
    BOOST_CHECK(GetBoolArg("-selit", false));
    BOOST_CHECK(GetBoolArg("-selit", true));

    BOOST_CHECK(!GetBoolArg("-fo"));
    BOOST_CHECK(!GetBoolArg("-fo", false));
    BOOST_CHECK(GetBoolArg("-fo", true));

    BOOST_CHECK(!GetBoolArg("-selito"));
    BOOST_CHECK(!GetBoolArg("-selito", false));
    BOOST_CHECK(GetBoolArg("-selito", true));

    ResetArgs("-selit=0");
    BOOST_CHECK(!GetBoolArg("-selit"));
    BOOST_CHECK(!GetBoolArg("-selit", false));
    BOOST_CHECK(!GetBoolArg("-selit", true));

    ResetArgs("-selit=1");
    BOOST_CHECK(GetBoolArg("-selit"));
    BOOST_CHECK(GetBoolArg("-selit", false));
    BOOST_CHECK(GetBoolArg("-selit", true));

    // New 0.6 feature: auto-map -nosomething to !-something:
    ResetArgs("-noselit");
    BOOST_CHECK(!GetBoolArg("-selit"));
    BOOST_CHECK(!GetBoolArg("-selit", false));
    BOOST_CHECK(!GetBoolArg("-selit", true));

    ResetArgs("-noselit=1");
    BOOST_CHECK(!GetBoolArg("-selit"));
    BOOST_CHECK(!GetBoolArg("-selit", false));
    BOOST_CHECK(!GetBoolArg("-selit", true));

    ResetArgs("-selit -noselit");  // -selit should win
    BOOST_CHECK(GetBoolArg("-selit"));
    BOOST_CHECK(GetBoolArg("-selit", false));
    BOOST_CHECK(GetBoolArg("-selit", true));

    ResetArgs("-selit=1 -noselit=1");  // -selit should win
    BOOST_CHECK(GetBoolArg("-selit"));
    BOOST_CHECK(GetBoolArg("-selit", false));
    BOOST_CHECK(GetBoolArg("-selit", true));

    ResetArgs("-selit=0 -noselit=0");  // -selit should win
    BOOST_CHECK(!GetBoolArg("-selit"));
    BOOST_CHECK(!GetBoolArg("-selit", false));
    BOOST_CHECK(!GetBoolArg("-selit", true));

    // New 0.6 feature: treat -- same as -:
    ResetArgs("--selit=1");
    BOOST_CHECK(GetBoolArg("-selit"));
    BOOST_CHECK(GetBoolArg("-selit", false));
    BOOST_CHECK(GetBoolArg("-selit", true));

    ResetArgs("--noselit=1");
    BOOST_CHECK(!GetBoolArg("-selit"));
    BOOST_CHECK(!GetBoolArg("-selit", false));
    BOOST_CHECK(!GetBoolArg("-selit", true));

}

BOOST_AUTO_TEST_CASE(stringarg)
{
    ResetArgs("");
    BOOST_CHECK_EQUAL(GetArg("-selit", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-selit", "eleven"), "eleven");

    ResetArgs("-selit -bar");
    BOOST_CHECK_EQUAL(GetArg("-selit", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-selit", "eleven"), "");

    ResetArgs("-selit=");
    BOOST_CHECK_EQUAL(GetArg("-selit", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-selit", "eleven"), "");

    ResetArgs("-selit=11");
    BOOST_CHECK_EQUAL(GetArg("-selit", ""), "11");
    BOOST_CHECK_EQUAL(GetArg("-selit", "eleven"), "11");

    ResetArgs("-selit=eleven");
    BOOST_CHECK_EQUAL(GetArg("-selit", ""), "eleven");
    BOOST_CHECK_EQUAL(GetArg("-selit", "eleven"), "eleven");

}

BOOST_AUTO_TEST_CASE(intarg)
{
    ResetArgs("");
    BOOST_CHECK_EQUAL(GetArg("-selit", 11), 11);
    BOOST_CHECK_EQUAL(GetArg("-selit", 0), 0);

    ResetArgs("-selit -bar");
    BOOST_CHECK_EQUAL(GetArg("-selit", 11), 0);
    BOOST_CHECK_EQUAL(GetArg("-bar", 11), 0);

    ResetArgs("-selit=11 -bar=12");
    BOOST_CHECK_EQUAL(GetArg("-selit", 0), 11);
    BOOST_CHECK_EQUAL(GetArg("-bar", 11), 12);

    ResetArgs("-selit=NaN -bar=NotANumber");
    BOOST_CHECK_EQUAL(GetArg("-selit", 1), 0);
    BOOST_CHECK_EQUAL(GetArg("-bar", 11), 0);
}

BOOST_AUTO_TEST_CASE(doubledash)
{
    ResetArgs("--selit");
    BOOST_CHECK_EQUAL(GetBoolArg("-selit"), true);

    ResetArgs("--selit=verbose --bar=1");
    BOOST_CHECK_EQUAL(GetArg("-selit", ""), "verbose");
    BOOST_CHECK_EQUAL(GetArg("-bar", 0), 1);
}

BOOST_AUTO_TEST_CASE(boolargno)
{
    ResetArgs("-noselit");
    BOOST_CHECK(!GetBoolArg("-selit"));
    BOOST_CHECK(!GetBoolArg("-selit", true));
    BOOST_CHECK(!GetBoolArg("-selit", false));

    ResetArgs("-noselit=1");
    BOOST_CHECK(!GetBoolArg("-selit"));
    BOOST_CHECK(!GetBoolArg("-selit", true));
    BOOST_CHECK(!GetBoolArg("-selit", false));

    ResetArgs("-noselit=0");
    BOOST_CHECK(GetBoolArg("-selit"));
    BOOST_CHECK(GetBoolArg("-selit", true));
    BOOST_CHECK(GetBoolArg("-selit", false));

    ResetArgs("-selit --noselit");
    BOOST_CHECK(GetBoolArg("-selit"));

    ResetArgs("-noselit -selit"); // selit always wins:
    BOOST_CHECK(GetBoolArg("-selit"));
}

BOOST_AUTO_TEST_SUITE_END()
