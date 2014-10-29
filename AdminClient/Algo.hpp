/*
	Algo to be run on server side at bool variable change "allocationDateBool"
	See below for arguments
	
	//takes in paperID, conferenceID, and numReqReviewers for paper
*/

//Algo:
//PaperForReview Class has a paper and calculates a score for all the potential reviewers. This is then stored in an
//array (of structs) which has the reviewerID and associated score for that reviewer.

//USE: Create new PaperForReview with consturctor
//	Use getter function to return reviewers
//	reviewers with a reviewer ID of -1 => not a reviewer


//returns vector of reviewerIDs from getter

#include "Database.hpp"

#include <algorithm>
#include <iostream>
#include <vector>


struct ReviewerBid
{
    ReviewerBid() 
    { 
        score = 0; 
        reviewerID = 0; 
    }
	int score;
	int reviewerID;
};

class PaperForReview
{
public:
        PaperForReview();
	PaperForReview(int, int, int, Database*);
	~PaperForReview();

	void findMinScore();
	void setNewReviewer(int, int);
    void addNewReviewerUnderReqNum(int, int);
	void checkNewReviewer(int, int);
	void addAuthor(int);
	void conflictingReviewers();
	void algo(int, int);
	void fillVectors(int);
	void pushReviewers();
    int calculateScore(int, int);
    void setReviewerBids(const std::vector<ReviewerBid>& ireviewerBids) {reviewerBids = ireviewerBids;}
    void setMinScore(int iminScore) {minScore = iminScore;}
    int getMinScore() {return minScore;}

private:
	Database* db;
	int paperID;
	int conferenceID;
    int minScore;
	int numOfReqReviewrs;
	std::vector<ReviewerBid> reviewerBids;
	std::vector<int> authors;
	std::vector<std::string> involvedOrganisation;
	std::vector<int> conflictingReviewersVec;
};
