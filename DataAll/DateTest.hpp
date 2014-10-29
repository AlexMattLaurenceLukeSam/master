#ifndef DATETEST_HPP
#define	DATETEST_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Date.hpp"

class DateTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE (DateTest);
    CPPUNIT_TEST (testEquals);
    CPPUNIT_TEST (testSetBit);
    CPPUNIT_TEST (testSetBitAndCount);
    CPPUNIT_TEST_SUITE_END ();
private:
	Date a;
	Date b;
public:
	void setUp();
	void tearDown();
protected:
	void testEqualDates();
	void testMonthAheadDayBehind();
	void testYearAheadMonthBehind();
	void testYearBehindDayAhead();

};
/*
 * File:   DateTest.hpp
 * Author: torchcar
 *
 * Created on 26 February 2009, 1:20 PM
 */




#endif	/* DATETEST_HPP */
