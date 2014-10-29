#ifndef ALGO_HPP
#define	ALGO_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Algo.hpp"

class AlgoTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE (AlgoTest);
    CPPUNIT_TEST (testFindMinScore);
    CPPUNIT_TEST (testSetNewReviewer);
    CPPUNIT_TEST_SUITE_END ();
private:
PaperForReview a;
public:
	void setUp();
	void tearDown();
protected:
void testMinScore();
void testSetNewReviewer();

};
/*
 * File:   AlgoTest.hpp
 * Author: torchcar
 *
 * Created on 26 February 2009, 1:20 PM
 */




#endif	/* ALGO_HPP */
