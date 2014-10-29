#include "AlgoTest.hpp"
#include "Algo.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION (AlgoTest);

void AlgoTest::setUp()
{
// set minScore to zero and remvoe reviewerBids
	a.setMinScore(0);
	a.setNumOfReqReviewrs(5);
}

void AlgoTest::tearDown()
{
	a.setReviewerBids(std::vector<ReviewerBid>);
}

void AlgoTest::testFindMinScore()
{
	a.setMinScore(2);
	CPPUNIT_ASSERT(a.getMinScore() == 2);
	temp = std::vector<ReviewerBid>;
	for (unsigned int i = 0; i < numOfReqReviewrs; ++i)
	{
		temp[i].reviewerID = i;
	}
	temp[1].score = 3;
	temp[2].score = 4;
	temp[3].score = 2;
	temp[4].score = 2;
	temp[5].score = 1;
	a.setReviewerBids(temp);
	a.findMinScore();
	CPPUNIT_ASSERT(a.getMinScore() == 1);
}

void AlgoTest::testSetNewReviewer()
{
	temp = std::vector<ReviewerBid>;
	for (unsigned int i = 0; i < numOfReqReviewrs; ++i)
	{
		temp[i].reviewerID = i;
	}
	temp[1].score = 3;
	temp[2].score = 4;
	temp[3].score = 2;
	temp[4].score = 2;
	temp[5].score = 1;
	a.findMinScore();
	CPPUNIT_ASSERT(a.getMinScore() == 1);
	a.setNewReviewer(6, 6);
	a.findMinScore();
	CPPUNIT_ASSERT(a.getMinScore() != 1);
	CPPUNIT_ASSERT(a.getMinScore() == 2);
}
