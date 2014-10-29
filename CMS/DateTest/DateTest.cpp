#include "DateTest.hpp"
#include "../CMS/Date.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION (DateTest);

void DateTest::setUp()
{
	// Put the dates back to standard state

	a.setDay(0);
	a.setMonth(0);
	a.setYear(0);
	b.setDay(0);
	b.setMonth(0);
	b.setYear(0);
}

void DateTest::tearDown()
{
	// Nothing to do
}

void DateTest::testEqualDates()
{
	CPPUNIT_ASSERT(a.compare(b)); //compare returns true if b is before or at the same date as a
	CPPUNIT_ASSERT(b.compare(a));
}

void DateTest::testMonthAheadDayBehind()
{
  a.setDay(1);
  b.setMonth(1);
  CPPUNIT_ASSERT(!a.compare(b)); //b is after a - should be false
  CPPUNIT_ASSERT(b.compare(a)); //a is after b - should be true
}

void DateTest::testYearAheadMonthBehind() {
  a.setMonth(1);
  b.setYear(1);
  CPPUNIT_ASSERT(!a.compare(b));
  CPPUNIT_ASSERT(b.compare(a));
}

void DateTest::testYearBehindDayAhead() {
  a.setYear(1);
  b.setDay(1);
  CPPUNIT_ASSERT(a.compare(b));
  CPPUNIT_ASSERT(!b.compare(a));
}


void DateTest::testYearEqualMonthAhead() {
  a.setYear(1);
  b.setMonth(1);
  b.setYear(1);
  CPPUNIT_ASSERT(!a.compare(b)); //b is after a
  CPPUNIT_ASSERT(b.compare(a));
}

void DateTest::testYearEqualMonthEqualDayAhead() {
  a.setMonth(1);
  a.setYear(1);
  b.setDay(1);
  b.setMonth(1);
  b.setYear(1);
  CPPUNIT_ASSERT(!a.compare(b)); //b is after a
  CPPUNIT_ASSERT(b.compare(a));
}
