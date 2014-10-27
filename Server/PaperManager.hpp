#ifndef PAPER_MANAGER_H
#define PAPER_MANAGER_H

#include "../DataAll/DiscussionPost.hpp"
#include "../DataAll/Paper.hpp"
#include "../DataAll/Review.hpp"
#include "../Database/Database.hpp"

class PaperManager {
public:
    PaperManager() { }

    PaperManager(Paper* icurrentPaper, 
        Database* idatabase)
    { 
        currentPaper = icurrentPaper;
        database = idatabase;
    }

    ~PaperManager() 
    { 
        if(currentPaper != nullptr)
            delete currentPaper;
    }
    
    Paper* getCurrentPaper() {return currentPaper;}
    void setCurrentPaper(Paper* icurrentPaper) {currentPaper = icurrentPaper;}
    Database* getDatabase() {return database;}
    void setDatabase(Database* idatabase) {database = idatabase;}
    void addPaper();
    void modifyPaper(int, const std::string&);
    void modifyPdf(int, int, const std::string&);
    //bool deleteDiscPost(int);
    void modifyDiscPost(int);
    //bool deleteReview(int);
    void addReview(Review);
    void fetchReview(int);
    void modifyReview(Review);
    void fetchDiscussion();
    void fetchRebuttal(int);
    void createDiscussionPost(DiscussionPost);
    //bool deletePaper(int);
    void sendPaper(); //just send a paper
    void sendPaperSummaryBatch(int); //all papers for a conf
    void sendAuthoredPaperSummaries(int, int); //
    void sendPaperSummariesToReview(int, int); //all papers for a reviewer in a conference
    void sendPapersAccepted(int);
    void addPaperAccepted(int);

private:
    void fetchPaper(int);
    Paper* currentPaper = nullptr;
    Database* database = nullptr;
};
#endif
