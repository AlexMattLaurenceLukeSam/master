createPaper(Paper paper, std::string pdf) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* insertPaper = "INSERT IGNORE INTO Paper(leadAuthorID, confID, keywordID, paperTitle, paperAbstract, paper) VALUES(?, ?, (SELECT keywordID FROM Keywords WHERE keyword=?), ?, ?, ?)";
	const char* getPaperID = "SELECT LAST_INSERT_ID()";
	const char* insertAuthors = "INSERT IGNORE INTO paperAuthors(paperID, authorID) VALUES(?, ?)";

	const char* insertKeywords = "INSERT IGNORE INTO PaperKeywords VALUES(?, (SELECT keywordID FROM Keywords WHERE keyword=?))";

        // =======================================
        // Paper
        sql::PreparedStatement *pstmt = NULL;
        pstmt = dbcon->prepareStatement(insertPaper);
        pstmt->setInt(1, paper.leadAuthorID);
        pstmt->setInt(2, paper.confID);
        pstmt->setString(3, paper.confKeyword);
        pstmt->setString(4, paper.title);
        pstmt->setString(5, paper.abstract);
        pstmt->setString(6, pdf);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Store paperID
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPaperID);

	rs = pstmt->executeQuery();
	bool haveRecord = rs->next();

        int paperID = rs->getInt(1);

	if( paperID == 0)
		return;

        delete rs;
        delete pstmt;

        // =======================================
        // Paper Authors
        pstmt = dbcon->prepareStatement(insertAuthors);

	std::vector<PersonalInfo>::const_iterator it;
	for (it = paper.authors.begin(); it != paper.authors.end(); it ++)
	{
		PersonalInfo pInfo = *it;	

		pstmt->setInt(1, paperID);
		pstmt->setInt(2, pInfo.infoID);

	        pstmt->executeUpdate();
	}
	delete pstmt;

        // =======================================
        // Keywords
      	if (paper.keywords.size() > 0)
      	{
      		pstmt = dbcon->prepareStatement(insertKeywords);
		    std::vector<std::string>::const_iterator it;
      		for (it = paper.keywords.begin(); it != paper.keywords.end(); it ++)
		    {
		    	std::string word = *it;	

            		if (!this->existsKeyword(word))
		    	{
		    		this->addKeyword(word);
		    	}
		    	
		    	pstmt->setInt(1, paperID);
		    	pstmt->setString(2, word);

      	    	        pstmt->executeUpdate();
		    }
      		delete pstmt;

      	}

}

void Database::updatePaper(Paper paper) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* updatePaper = "UPDATE Paper SET leadAuthorID=?, confID=?, keywordID=(SELECT keywordID FROM Keywords WHERE keyword=?), paperTitle=?, paperAbstract=? WHERE paperID=?";
        const char* deleteAuthors = "DELETE FROM paperAuthors WHERE paperID=?";
	const char* insertAuthors = "INSERT IGNORE INTO paperAuthors(paperID, authorID) VALUES(?, ?)";

        const char* deleteKeywords = "DELETE FROM PaperKeywords WHERE paperID=?";
	const char* insertKeywords = "INSERT IGNORE INTO PaperKeywords VALUES(?, (SELECT keywordID FROM Keywords WHERE keyword=?))";

        // =======================================
        // Paper
        sql::PreparedStatement *pstmt = NULL;
        pstmt = dbcon->prepareStatement(updatePaper);
        pstmt->setInt(1, paper.leadAuthorID);
        pstmt->setInt(2, paper.confID);
        pstmt->setString(3, paper.confKeyword);
        pstmt->setString(4, paper.title);
        pstmt->setString(5, paper.abstract);
        pstmt->setInt(6, paper.paperID);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Authors Delete
        pstmt = dbcon->prepareStatement(deleteAuthors);
        pstmt->setInt(1, paper.paperID);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Paper Authors
        pstmt = dbcon->prepareStatement(insertAuthors);

	std::vector<PersonalInfo>::const_iterator it;
	for (it = paper.authors.begin(); it != paper.authors.end(); it ++)
	{
		PersonalInfo pInfo = *it;	

		pstmt->setInt(1, paper.paperID);
		pstmt->setInt(2, pInfo.infoID);

	        pstmt->executeUpdate();
	}
	delete pstmt;

        // =======================================
        // Keywords Delete
        pstmt = dbcon->prepareStatement(deleteKeywords);
        pstmt->setInt(1, paper.paperID);

        pstmt->executeUpdate();

        delete pstmt;

        // =======================================
        // Keywords Insert
      	if (paper.keywords.size() > 0)
      	{
      		pstmt = dbcon->prepareStatement(insertKeywords);
		    std::vector<std::string>::const_iterator it;
      		for (it = paper.keywords.begin(); it != paper.keywords.end(); it ++)
		    {
		    	std::string word = *it;	
            		if (!this->existsKeyword(word))
		    	{
		    		this->addKeyword(word);
		    	}
		    	pstmt->setInt(1, paper.paperID);
		    	pstmt->setString(2, word);

      	    	        pstmt->executeUpdate();
		    }
      		delete pstmt;
      	}
}

void Database::addPaperAccepted(int paperID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* insertAccepted = "INSERT INTO AcceptedPapers VALUES(?, ?)";

        // =======================================
        // Paper Accepted
        sql::PreparedStatement *pstmt = NULL;

	pstmt = dbcon->prepareStatement(insertAccepted);
        pstmt->setInt(1, confID);
        pstmt->setInt(2, paperID);

        pstmt->executeUpdate();

	delete pstmt;
}

std::vector<int> Database::fetchPaperAccepted(int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getAccepted = "SELECT paperID FROM AcceptedPapers WHERE confID=?";

        // =======================================
        // Paper Accepted
	std::vector<int> vec;

        sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;

	pstmt = dbcon->prepareStatement(getAccepted);
        pstmt->setInt(1, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
		int paperID = rs->getInt(1);
                vec.push_back(paperID);
        }

	delete pstmt;
	delete rs;
        return vec;
}

Review Database::fetchReview(int paperID, int reviewerID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getReview = "SELECT * FROM Review WHERE (paperID=? and reviewerID=? and confID=?)";
        // =======================================
        // Review
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getReview);
	pstmt->setInt(1, paperID);
	pstmt->setInt(2, reviewerID);
	pstmt->setInt(3, confID);

	rs = pstmt->executeQuery();

	bool haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return Review();
	}

        int reportID = rs->getInt(1);
        int overall = rs->getInt(5);
        int confidence = rs->getInt(6);
        int relevance = rs->getInt(7);
        int originality = rs->getInt(8);
        int significance = rs->getInt(9);
        int presentation = rs->getInt(10);
        int techQuality = rs->getInt(11);
        int evaluation = rs->getInt(12);
        std::string commentsStrength = rs->getString(13);
        std::string commentsWeakness = rs->getString(14);
        std::string commentsSuggestions = rs->getString(15);
        std::string commentsShortPaper = rs->getString(16);
        std::string commentsBestAward = rs->getString(17);

	Review review(reportID,
		paperID, 
		reviewerID, 
		overall, 
		confidence, 
		relevance, 
		originality, 
		significance, 
		presentation, 
		techQuality, 
		evaluation, 
		commentsStrength, 
		commentsWeakness, 
		commentsSuggestions, 
		commentsShortPaper, 
		commentsBestAward);

        delete rs;
        delete pstmt;

	return review;
}

void Database::modifyReview(Review review, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* insertReview = "INSERT INTO Review(paperID, reviewerID, confID, overall, confidence, relevance, originality, significance, presentation, techQuality, evaluation, commentsStrength, commentsWeakness, commentsSuggestions, commentsShortPaper, commentsBestAward) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"; 
	const char* updateReview = "UPDATE Review SET paperID=?, reviewerID=?, confID=?, overall=?, confidence=?, relevance=?, originality=?, significance=?, presentation=?, techQuality=?, evaluation=?, commentsStrength=?, commentsWeakness=?, commentsSuggestions=?, commentsShortPaper=?, commentsBestAward=? WHERE reportID=?"; 
        // =======================================
        // Reviews
        sql::PreparedStatement *pstmt = NULL;

	pstmt = dbcon->prepareStatement(insertReview);

	if (review.reportID==0)
	{
		pstmt = dbcon->prepareStatement(insertReview);

		pstmt->setInt(1, review.paperID);
		pstmt->setInt(2, review.reviewerID);
		pstmt->setInt(3, confID);
		pstmt->setInt(4, review.overall);
		pstmt->setInt(5, review.confidence);
		pstmt->setInt(6, review.relevance);
		pstmt->setInt(7, review.originality);
		pstmt->setInt(8, review.significance);
		pstmt->setInt(9, review.presentation);
		pstmt->setInt(10, review.techQuality);
		pstmt->setInt(11, review.evaluation);
		pstmt->setString(12, review.commentsStrength);
		pstmt->setString(13, review.commentsWeakness);
		pstmt->setString(14, review.commentsSuggestions);
		pstmt->setString(15, review.commentsShortPaper);
		pstmt->setString(16, review.commentsBestAward);

		pstmt->executeUpdate();
	}
	else
	{
		pstmt = dbcon->prepareStatement(updateReview);

		pstmt->setInt(1, review.paperID);
		pstmt->setInt(2, review.reviewerID);
		pstmt->setInt(3, confID);
		pstmt->setInt(4, review.overall);
		pstmt->setInt(5, review.confidence);
		pstmt->setInt(6, review.relevance);
		pstmt->setInt(7, review.originality);
		pstmt->setInt(8, review.significance);
		pstmt->setInt(9, review.presentation);
		pstmt->setInt(10, review.techQuality);
		pstmt->setInt(11, review.evaluation);
		pstmt->setString(12, review.commentsStrength);
		pstmt->setString(13, review.commentsWeakness);
		pstmt->setString(14, review.commentsSuggestions);
		pstmt->setString(15, review.commentsShortPaper);
		pstmt->setString(16, review.commentsBestAward);
		pstmt->setInt(17, review.reportID);

		pstmt->executeUpdate();
	}
	delete pstmt;
}

Discussion Database::fetchDiscussion(int paperID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getDiscussion = "SELECT comment, reviewerID, commentID FROM ReviewerDiscussion WHERE (paperID=? and confID=?)";
        // =======================================
        // Discussion
        std::list<DiscussionPost> discussion;
	
        sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;

	pstmt = dbcon->prepareStatement(getDiscussion);
	pstmt->setInt(1, paperID);
	pstmt->setInt(2, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
		std::string comment = rs->getString(1);
		int reviewerID = rs->getInt(2);
		int commentID = rs->getInt(3);
		DiscussionPost discuss(comment, reviewerID, commentID);
                discussion.push_back(discuss);
        }

        delete rs;
        delete pstmt;
}

DiscussionPost Database::fetchRebuttal(int paperID, int userID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getDiscussionPost = "SELECT comment, reviewerID, commentID FROM ReviewerDiscussion WHERE (paperID=? and reviewerID=? and confID=?)";

        // =======================================
        // Discussion Post
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getDiscussionPost);
	pstmt->setInt(1, paperID);
	pstmt->setInt(2, userID);
	pstmt->setInt(3, confID);

	rs = pstmt->executeQuery();

	bool haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return DiscussionPost();
	}

	std::string comment = rs->getString(1);
	int reviewerID = rs->getInt(2);
	int commentID = rs->getInt(3);
	DiscussionPost discuss(comment, reviewerID, commentID);

        delete rs;
        delete pstmt;
	
	return discuss;
}

void Database::createDiscussionPost(DiscussionPost discussionPost, int paperID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* insertDiscussPost = "INSERT INTO ReviewerDiscussion(paperID, confID, reviewerID, comment) VALUES(?, ?, ?, ?)";
        // =======================================
        // Discussion
        sql::PreparedStatement *pstmt = NULL;

	pstmt = dbcon->prepareStatement(insertDiscussPost);
	
	pstmt->setInt(1, paperID);
	pstmt->setInt(2, confID);
	pstmt->setInt(3, discussionPost.reviewerID);
	pstmt->setString(4, discussionPost.comment);

	pstmt->executeUpdate();

	delete pstmt;
}

std::vector<int> Database::getAuthorsForPaper(int paperID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getAuthors = "SELECT authorID FROM paperAuthors WHERE paperID=?";

        // =======================================
        // Authors
	std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getAuthors);
	pstmt->setInt(1, paperID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
		int authorID = rs->getInt(1);
                vec.push_back(authorID);
        }

        delete rs;
        delete pstmt;
	
	return vec;
}

std::string Database::getOrganisationForAuthor(int infoID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getOrg = "SELECT organisation FROM PersonalInfo WHERE infoID=?";

        // =======================================
        // Org
	std::vector<std::string> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getOrg);
	pstmt->setInt(1, infoID);

	rs = pstmt->executeQuery();

	bool haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return std::string();
	}

	std::string org = rs->getString(1);

    delete rs;
    delete pstmt;
	
	return org;
}

std::vector<int> Database::getReviewersForOrganisation(std::string org) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getReviewers = "SELECT userID FROM UserType WHERE (userType = 'pc' and userID IN (SELECT userID FROM PersonalInfo WHERE (userID IS NOT NULL and organisation=?)))";

        // =======================================
        // Reviewers
	std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getReviewers);
	pstmt->setString(1, org);

	rs = pstmt->executeQuery();

        while (rs->next()) {
		int reviewerID = rs->getInt(1);
                vec.push_back(reviewerID);
        }

        delete rs;
        delete pstmt;
	
	return vec;
}

std::vector<int> Database::getPapersForAuthor(int authorID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getPapers = "SELECT paperID FROM paperAuthors WHERE authorID=?";

        // =======================================
        // Papers
	std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPapers);
	pstmt->setInt(1, authorID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
		int paperID = rs->getInt(1);
                vec.push_back(paperID);
        }

        delete rs;
        delete pstmt;
	
	return vec;
}

std::vector<std::string> Database::getKeywordsForPaper(int paperID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getPaperKeywords = "SELECT keyword FROM Keywords WHERE keywordID in (SELECT keywordID FROM PaperKeywords WHERE paperID=?)";

        // =======================================
        // Paper Keywords
        std::vector<std::string> keywords;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPaperKeywords);
	pstmt->setInt(1, paperID);
	rs = pstmt->executeQuery();

        while (rs->next()) {
                std::string keyword = rs->getString(1);
                keywords.push_back(keyword);
        }

        delete rs;
        delete pstmt;

	return keywords;
}

std::vector<std::string> Database::getKeywordsForUser(int userID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getUserKeywords = "SELECT keyword FROM Keywords WHERE keywordID in (SELECT expertiseID FROM ExpertiseArea WHERE userID=?)";

        // =======================================
        // Expertise Keywords
        std::vector<std::string> keywords;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getUserKeywords);
	pstmt->setInt(1, userID);
	rs = pstmt->executeQuery();

        while (rs->next()) {
                std::string keyword = rs->getString(1);
                keywords.push_back(keyword);
        }

        delete rs;
        delete pstmt;

	return keywords;
}

std::vector<int> Database::getReviewersForConf(int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getReviewers = "SELECT userID FROM UserType WHERE (userType='pc' and confID=?)";

        // =======================================
        // Reviewers
        std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getReviewers);
	pstmt->setInt(1, confID);
	rs = pstmt->executeQuery();

        while (rs->next()) {
                int userID = rs->getInt(1);
                vec.push_back(userID);
        }

        delete rs;
        delete pstmt;

	return vec;
}

int Database::getReviewerPreference(int userID, int confID, int paperID) throw (const char*)
{
	const char* getReviewerPreference = "SELECT preference FROM ReviewerPreference WHERE (userID=? and confID=? and paperID=?)";

        // =======================================
        // Reviewer Preference
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getReviewerPreference);
	pstmt->setInt(1, userID);
	pstmt->setInt(2, confID);
	pstmt->setInt(3, paperID);

	rs = pstmt->executeQuery();

	bool haveRecord = rs->next();
	if (!haveRecord)
	{
		delete rs;
		delete pstmt;
		return -1;
	}

    	int preference = rs->getInt(1);

        delete rs;
        delete pstmt;
	
	return preference;
}

void Database::assignPaper(int paperID, int reviewerID, int confID) throw (const char*)
{
    if (invalid)
            throw (noDB);

	const char* insertPaperAssigned = "INSERT INTO PaperAssigned(paperID, reviewerID, confID) VALUES(?, ?, ?)";

    // =======================================
    // Paper Assigned
    sql::PreparedStatement *pstmt = NULL;
    pstmt = dbcon->prepareStatement(insertPaperAssigned);
    pstmt->setInt(1, paperID);
    pstmt->setInt(2, reviewerID);
    pstmt->setInt(3, confID);

    pstmt->executeUpdate();

    delete pstmt;
}

std::vector<int> Database::fetchReviewersAssigned(int paperID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getReviewersIDs = "SELECT reviewerID FROM PaperAssigned WHERE (paperID=? and confID=?)";

        // =======================================
        // Reviewer ID
        std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getReviewersIDs);
	pstmt->setInt(1, paperID);
	pstmt->setInt(2, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
                int reviewerID = rs->getInt(1);
                vec.push_back(reviewerID);
        }

        delete rs;
        delete pstmt;

	return vec;
}

std::vector<int> Database::getPaperIDsForConf(int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getPaperIDs = "SELECT paperID FROM Paper WHERE confID=?";

        // =======================================
        // Paper ID
        std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPaperIDs);
	pstmt->setInt(1, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
                int paperID = rs->getInt(1);
                vec.push_back(paperID);
        }

        delete rs;
        delete pstmt;

	return vec;
}

std::vector<int> Database::getPaperIDsForAllocatedReviewer(int reviewerID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getPaperIDs = "SELECT paperID FROM PaperAssigned WHERE (reviewerID=? and confID)";

        // =======================================
        // Paper ID
        std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPaperIDs);
	pstmt->setInt(1, reviewerID);
	pstmt->setInt(2, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
                int paperID = rs->getInt(1);
                vec.push_back(paperID);
        }

        delete rs;
        delete pstmt;

	return vec;
}

std::vector<int> Database::getPaperIDsForLeadAuthor(int leadAuthorID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getPaperIDs = "SELECT paperID FROM Paper WHERE (leadAuthorID=? and confID=?)";

        // =======================================
        // Paper ID
        std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getPaperIDs);
	pstmt->setInt(1, leadAuthorID);
	pstmt->setInt(2, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
                int paperID = rs->getInt(1);
                vec.push_back(paperID);
        }

        delete rs;
        delete pstmt;

	return vec;
}

std::vector<int> Database::getUserIDsForConf(int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getUserIDs = "SELECT userID FROM UserType WHERE confID=?";

        // =======================================
        // User ID
        std::vector<int> vec;
	sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getUserIDs);
	pstmt->setInt(1, confID);

	rs = pstmt->executeQuery();

        while (rs->next()) {
                int paperID = rs->getInt(1);
                vec.push_back(paperID);
        }

        delete rs;
        delete pstmt;

	return vec;
}


void Database::adminChangeUserName(std::string currentUN, std::string newUN) throw (const char*)
{
	const char* getUserID = "SELECT userID FROM UserAccount WHERE username = ?";
        const char* updateUserName = "UPDATE UserAccount SET username = ? WHERE userID=?";

        // =======================================
        // Store userID
        sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;
	
	pstmt = dbcon->prepareStatement(getUserID);
        pstmt->setString(1, currentUN);

	rs = pstmt->executeQuery();
	bool haveRecord = rs->next();

        int userID = rs->getInt(1);

        delete rs;
        delete pstmt;

        // =======================================
        // Personal Info Update

        pstmt = dbcon->prepareStatement(updateUserName);
        pstmt->setString(1, newUN);
        pstmt->setInt(2, userID);

        pstmt->executeUpdate();

        delete pstmt;
}

void Database::adminChangePassword(std::string username, std::string password) throw (const char*)
{
        const char* updatePassword = "UPDATE UserAccount SET password = ? WHERE username=?";

        // =======================================
        // Personal Info Update
        sql::PreparedStatement *pstmt = NULL;

        pstmt = dbcon->prepareStatement(updatePassword);
        pstmt->setString(1, password);
        pstmt->setString(2, username);

        pstmt->executeUpdate();

        delete pstmt;
}

UserType_t Database::adminFetchUserType(std::string username, std::string confTitle) throw (const char*)
{
//    const char* 
    std::string fetchUserType = "SELECT userType FROM UserType WHERE (userID=(SELECT userID FROM UserAccount WHERE username=?) and confID=(SELECT confID FROM Conference WHERE name=?))";
    
    // ============================================
    // User Type Update
    UserType_t userType;
    sql::PreparedStatement *pstmt = NULL;
    sql::ResultSet *rs = NULL;
    
    pstmt = dbcon->prepareStatement(fetchUserType.c_str());
    pstmt->setString(1, username);
    pstmt->setString(2, confTitle);
    
    rs = pstmt->executeQuery();
    bool haveRecord = rs->next();
    if (!haveRecord)
    {
        userType = NOUSER;
    }
    else
    {
        int e = rs->getInt(1);           
        if (e = 1)
            userType = AUTHOR;
        else if (e = 2)
            userType = REVIEWER;
        else if (e = 3)
            userType = PCCHAIR;
    }

    delete pstmt;
    delete rs;
    
    return userType;
}

void Database::adminChangeUserType(std::string username, std::string confTitle, UserType_t userType) throw (const char*)
{
    switch(userType)
    {
        case AUTHOR:
            setUserAsAuthorByNames(username, confTitle);
            break;
        case REVIEWER:
            setUserAsChairByNames(username, confTitle);
            break;
        case PCCHAIR:
            setUserAsPCByNames(username, confTitle);
            break;
    }
}

std::String fetchPDF(int paperID, int confID) throw (const char*)
{
        if (invalid)
                throw (noDB);

	const char* getAccepted = "SELECT paper FROM Paper WHERE (paperID=? and confID=?)";

        // =======================================
        // Paper 

        sql::PreparedStatement *pstmt = NULL;
	sql::ResultSet *rs = NULL;

	pstmt = dbcon->prepareStatement(getAccepted);
        pstmt->setInt(1, confID);

	rs = pstmt->executeQuery();

        bool haveRecord = rs->next();

        std::string pdf = rs->getString(1);

	delete pstmt;
	delete rs;

        return pdf;
}
