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

#include <algorithm>
#include <iostream>
#include <vector>


struct ReviewerBid
{
	int score;
	int reviewerID;
};

class PaperForReview
{
public:
	PaperForReview(int, int, int,Database*);
	~PaperForReview();

	int findMinScore();
	void setNewReviewer(int, int);
    void addNewReviewerUnderReqNum(int, int);
	void checkNewReviewer(int, int);
	void addAuthor(int);
	void conflictingReviewers();
	void algo();
	void fillVectors();
	void pushReviewers();

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

std::vector<int> pushReviewers()
{
	for(int i=0; i<reviewerBids.size(); i++)
	{
		if(reviewerBids.score[i] > 1)
		{
            db->assignPaper(paperID, reviewerBids.reviewerID, conferenceID);
			//Push new Reviewer to the database
			//db->reviewerAssigned(paperID,ReviewerBid.reviewerID
		}
	}

}

void PaperForReview::checkNewReviewer(int newScore, int newReviewerID)
{
    if(reviewerBids.size() < NumOfReqReviewers)
    {
        // Add reviewer
        addNewReviewerUnderReqNum(newScore, newReviewerID);
    }
    else if(newscore > minScore)
	{
        // Update reviewer
		setNewReviewer(newScore, newReviewerID);
	}
}

void PaperForReview::addNewReviewerUnderReqNum(int newScore, int newReviewer)
{
    ReviewerBid bid(newScore, newReviewer);

    reviewerBids.push_back(bid);
    
    if(newScore < minScore)
        minScore = newScore
}

void PaperForReview::findMinScore()
{
	int tempScore = -1;
	for(int i=0; i<NumOfReqReviewers; i++)
	{
        if(tempScore == -1)
            tempScore = reviewerBids[i].score;
        else if(reviewerBids[i].score < tempScore)
			tempScore = reviewerBids[i].score;
	}
	minScore = tempScore;
}

void PaperForReview::setNewReviewer(int newScore, int newReviewer)
{
	for(int i=0; i< NumOfReqReviewers; i++)
	{
		if(reviewerBids[i].score == minScore)
		{
			reviewerBids[i].score = newScore;
			reviewerBids[i].reviewerID =  newReviewer;
            findMinScore();
		}
	}
}

PaperForReview::~PaperForReview()
{
    db = NULL;
}

PaperForReview::PaperForReview(int newPaperID, int confID, int numReviewers, Database* database)
{
	paperID = newPaperID
	conferenceID = confID;
	db = database;
	
	numOfReqReviewrs = numReviewers;
	
	reviewerBids.resize(numOfReqReviewrs)
	
	for(int i=0; i< numOfReqReviewrs; i++)
	{
		reviewerBids[i].score = -1;
		reviewerBids[i].reviewerID = -1;
	}
	
	fillVectors(paperID);
	
	algo(PaperID, confID);
	
	pushReviewers();
}

//TODO
//populate clonflicting reviewers vector further from database queries
void PaperForReview::conflictingReviewers()
{
	//authors
	conflictingReviewersVec.insert(conflictingReviewersVec.end(), authors.begin(), authors.end());

	//(3)usersFromSameOrganisation
		//ForEachAuthor:   SelectOrganisation
			//SelectAllUsersFromEachOrganisation
				//PushBack^
    std::vector<std::string>::const_iterator it;
    for(it=involvedOrganisation.begin(); it!=involvedOrganisation.end(); it++)
    {
        std::vector<int> reviewersForOrg = db->getReviewersForOrganisation(*it);
	    conflictingReviewersVec.insert(conflictingReviewersVec.end(), reviewersForOrg.begin(), reviewersForOrg.end());
    }
        
	//pastCoAuthors
		//(4)ForEachAuthor:   selectAllPapers into papersForAuthor
			//Select All authors for each paper in papersForAuthor and place into temp
				//pushBack into conflictingReviewersVec
    std::vector<int>::const_iterator it;
    for(it=authors.begin(); it!=authors.end(); it++)
    {
        std::vector<int> papersForAuthor = db->getPapersForAuthor(*it);

        std::vector<int>::const_iterator iter;
        for(iter=papersForAuthor.begin(); iter!=papersForAuthor.end(); it++)
        {
            std::vector<int> temp = db->getAuthorsForPaper(*it);
	        conflictingReviewersVec.insert(conflictingReviewersVec.end(), temp.begin(), temp.end());
        }
    }
}



//TODO: matching keywords from database returns
int calculateScore(int userID, int paperID)
{
	int score = 1;

    std::vector<std::string> keysForPaper = db->getKeywordsForPaper(paperID);
    std::vector<std::string> keysForUser = db->getKeywordsForUser(userID);

	//(5)&(6)for each keyword match
    std::vector<std::string>::const_iterator it;
    for(it=keysForPaper.begin(); it!=keysForPaper.end(); it++)
    {
        std::vector<std::string>::const_iterator iter;
        for(iter=keysForUser.begin(); iter!=keysForUser.end(); it++)
        {
            if (*it == *iter)
		        ++score;
        }
    }

	return score;

}


//TODO:get reviewer pref
void PaperForReview::algo(int paperID, int conferenceID)
{
	std::vector<int> userIDs;
	
	//(7) fill userIDs with reviewers from conference
    userIDs = db->getReviewersForConf(conferenceID);
    int UserID;	

    std::vector<int>::const_iterator iter;
    for(it=userIDs.begin(); it!=userIDs.end(); it++)
    {
        UserID = *it;
     	int score = 0;
        if (std::find(conflictingReviewersVec.begin(), conflictingReviewersVec.end(), UserID) != conflictingReviewersVec.end())
        {
    		int reviewersPreference = 0;
    				// 1=yes
    				//2=maybe
                    //3=no
    				//4=conflict
    
            //(8)GET PREF FROM DATABASE fetchreviewerPreference(userID, paperID);
    		reviewersPreference = db->getReviewerPreference(UserID, conferenceID, paperID);			
    
    		if(reviewersPreference == 1)
    		{
    			score = calculateScore(UserID, paperID) * 1000000;
    			checkNewReviewer(score, UserID);
    		}
    		elseif(reviewersPreference == 2)
    		{
    			score = calculateScore(UserID, paperID) * 1000;
    			checkNewReviewer(score, UserID);
    		}
    		elseif(reviewersPreference != 3)
    		{
    			score = calculateScore(UserID, paperID);
    			checkNewReviewer(score, UserID);
    		}
    	}
    }
}


//TODO: populate vectors from data base
//TODO: call conflicting reviewers

void fillVectors(int paperID)
{

	// (1)select all Authors where paper==paperID
		//addAuthors to paper
    authors = db->getAuthorsForPaper(paperID);

	// (2)select organisation for each author
		//add involved organisation
    
    std::vector<int>::const_iterator it;
    for(it=authors.begin(); it!=authors.end(); it++)
    {
        std::string temp = db->getOrganisationForAuthor(*it);
        if(!temp.empty())
            involvedOrganisation.push_back(temp);
    }
	
	//CONFLICTING HERE
	conflictingReviewers();
}


//MAY NEED TO FILTER FOR CONFERENCE ASWELL
//(1)select author
		//Where Paper ID = ?
		
//(2)select organisation
		//where author = ?
		

//(3) select author
		//where organisation = ?
		
//(4) select paperIDs
		//where Author =?
		
//(5) select keywords
		//where paperID = ?
		
//(6) select keywords
		//where userID = ?
		
//(7) select pcs(reviewrs)
		//where conferfence = ?
		
//(8) select reviewerPreferance
		//where reviewerID = ? and paperID = ? 

