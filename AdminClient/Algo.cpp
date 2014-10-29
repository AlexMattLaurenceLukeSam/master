#include "Algo.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

PaperForReview::PaperForReview()
{
	db = NULL;  	
}

PaperForReview::PaperForReview(int newPaperID, int confID, int numReviewers, Database* database)
{
	paperID = newPaperID;
	conferenceID = confID;
	db = database;
	
	numOfReqReviewrs = numReviewers;
	
	reviewerBids.resize(numOfReqReviewrs);
	
	for(int i=0; i< numOfReqReviewrs; i++)
	{
		reviewerBids[i].score = -1;
		reviewerBids[i].reviewerID = -1;
	}
	
	fillVectors(paperID);
	
	algo(paperID, conferenceID);
	
	pushReviewers();
}

void PaperForReview::pushReviewers()
{
	for(int i=0; i < reviewerBids.size(); i++)
	{
		if(reviewerBids[i].score > 1)
		{
            db->assignPaper(paperID, reviewerBids[i].reviewerID, conferenceID);
			//Push new Reviewer to the database
			//db->reviewerAssigned(paperID,ReviewerBid.reviewerID
		}
	}

}

void PaperForReview::checkNewReviewer(int newScore, int newReviewerID)
{
    if(reviewerBids.size() < numOfReqReviewrs)
    {
        // Add reviewer
        addNewReviewerUnderReqNum(newScore, newReviewerID);
    }
    else if(newScore > minScore)
	{
        // Update reviewer
		setNewReviewer(newScore, newReviewerID);
	}
}

void PaperForReview::addNewReviewerUnderReqNum(int newScore, int newReviewer)
{
    ReviewerBid bid;
    bid.score = newScore;
    bid.reviewerID = newReviewer;

    reviewerBids.push_back(bid);
    
    if(newScore < minScore)
        minScore = newScore;
}

void PaperForReview::findMinScore()
{
	int tempScore = -1;
	for(int i=0; i<numOfReqReviewrs; i++)
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
	for(int i=0; i< numOfReqReviewrs; i++)
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
    std::vector<int>::const_iterator it2;
    for(it2=authors.begin(); it2!=authors.end(); it2++)
    {
        std::vector<int> papersForAuthor = db->getPapersForAuthor(*it2);

        std::vector<int>::const_iterator iter;
        for(iter=papersForAuthor.begin(); iter!=papersForAuthor.end(); iter++)
        {
            std::vector<int> temp = db->getAuthorsForPaper(*iter);
	        conflictingReviewersVec.insert(conflictingReviewersVec.end(), temp.begin(), temp.end());
        }
    }
}



//TODO: matching keywords from database returns
int PaperForReview::calculateScore(int userID, int paperID)
{
	int score = 1;

    std::vector<std::string> keysForPaper = db->getKeywordsForPaper(paperID);
    std::vector<std::string> keysForUser = db->getKeywordsForUser(userID);

	//(5)&(6)for each keyword match
    std::vector<std::string>::const_iterator it;
    for(it=keysForPaper.begin(); it!=keysForPaper.end(); it++)
    {
        std::vector<std::string>::const_iterator iter;
        for(iter=keysForUser.begin(); iter!=keysForUser.end(); iter++)
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

    std::vector<int>::const_iterator it;
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
    		else if(reviewersPreference == 2)
    		{
    			score = calculateScore(UserID, paperID) * 1000;
    			checkNewReviewer(score, UserID);
    		}
    		else if(reviewersPreference != 3)
    		{
    			score = calculateScore(UserID, paperID);
    			checkNewReviewer(score, UserID);
    		}
    	}
    }
}


//TODO: populate vectors from data base
//TODO: call conflicting reviewers

void PaperForReview::fillVectors(int paperID)
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
