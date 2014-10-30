#include "AlgoTest.hpp"
#include "../Algo.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION (AlgoTest);

void AlgoTest::setUp()
{
// set minScore to zero and remove reviewerBids
	a.setMinScore(0);
	a.setNumOfReqReviewrs(5);
}

void AlgoTest::tearDown()
{
    std::vector<ReviewerBid> temp;
	a.setReviewerBids(temp);
}

void AlgoTest::testFindMinScore()
{
//CPPUNIT_ASSERT(false);
    a.setMinScore(2);
	CPPUNIT_ASSERT(a.getMinScore() == 2);
	std::vector<ReviewerBid> temp;
        ReviewerBid temp2;
	temp2.score = 3;
        temp2.reviewerID = 6;
        temp.push_back(temp2);
	temp2.score = 4;
        temp2.reviewerID = 6;
        temp.push_back(temp2);
	temp2.score = 2;
        temp2.reviewerID = 6;
        temp.push_back(temp2);
	temp2.score = 2;
        temp2.reviewerID = 6;
        temp.push_back(temp2);
	temp2.score = 1;
        temp2.reviewerID = 6;
        temp.push_back(temp2);
	a.setReviewerBids(temp);
	a.findMinScore();
	CPPUNIT_ASSERT(a.getMinScore() == 1);
}

void AlgoTest::testSetNewReviewer()
{
	std::vector<ReviewerBid> temp;

        ReviewerBid temp2;
	temp2.score = 3;
        temp2.reviewerID = 6;
        temp.push_back(temp2);
	temp2.score = 4;
        temp2.reviewerID = 6;
        temp.push_back(temp2);
	temp2.score = 2;
        temp2.reviewerID = 6;
        temp.push_back(temp2);
	temp2.score = 2;
        temp2.reviewerID = 6;
        temp.push_back(temp2);
	temp2.score = 1;
        temp2.reviewerID = 6;
        temp.push_back(temp2);
        a.setReviewerBids(temp);

	a.findMinScore();
	CPPUNIT_ASSERT(a.getMinScore() == 1);
	a.setNewReviewer(6, 6);
	a.findMinScore();
	CPPUNIT_ASSERT(a.getMinScore() != 1);
	CPPUNIT_ASSERT(a.getMinScore() == 2);
}
