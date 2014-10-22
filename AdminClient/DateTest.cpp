//#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MODULE CompareTest
#include <boost/test/unit_test.hpp>
//#include "C:\Users\Lucha\Documents\Boost\boost\test\unit_test.hpp"
#include "Date.hpp"

//BOOST_AUTO_TEST_SUITE(CompareTest)
BOOST_AUTO_TEST_CASE(EqualDates) {
  Date a;
  Date b;
  BOOST_CHECK(a.compare(b));
  BOOST_CHECK(!b.compare(a));
}

BOOST_AUTO_TEST_CASE(MonthAheadDayBehind) {
  Date a;
  a.day = 1;
  Date b(0,1,0);
  BOOST_CHECK(!a.compare(b));
  BOOST_CHECK(b.compare(a));
}

BOOST_AUTO_TEST_CASE(YearAheadMonthBehind) {
  Date a;
  a.month = 1;
  Date b(0,0,1);
  BOOST_CHECK(!a.compare(b));
  BOOST_CHECK(b.compare(a));
}

BOOST_AUTO_TEST_CASE(YearBehindDayAhead) {
  Date a;
  a.year = 1;
  Date b(1,0,0);
  BOOST_CHECK(a.compare(b));
  BOOST_CHECK(!b.compare(a));
}
