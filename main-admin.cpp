#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "Database/Database.hpp"
#include "Server/User.hpp"
#include "DataAll/Conference.hpp"
#include "DataAll/Paper.hpp"
#include "Algorithm/Algo.hpp"

#include <vector>

void adminMainMenu();
void createUser();
void createConf();
void changeUsername();
void changePassword();
void changeConf();

Database db;

int main(int arc, char *argv[])
{
    std::string AdminUsername = "";
    std::string AdminPassword = "";
    std::string AdminUsernameCheck = "admin";
    std::string AdminPasswordCheck = "admin";

    if (!db.isOK())
    {
            std::cout << "Failed to open database file" << std::endl;
            exit(1);
    }

    std::cout << "Admin client" << std::endl << std::endl;

    std::cout << "Enter Admin username: ";
    std::cin >> AdminUsername;
    
    std::cout << std::endl << "Enter Admin password: ";
    std::cin >> AdminPassword;

    bool loginSuccess = false;
    if (AdminUsername == AdminUsernameCheck)
    {
        if (AdminPassword == AdminPasswordCheck)
            loginSuccess = true;
    }
    
    if (loginSuccess)
        adminMainMenu();

    return 0;
}

void adminMainMenu()
{
    int selection = -1;
    std::cout << std::endl << std::endl << "ADMIN MAIN MENU" << std::endl << std::endl;
    
    std::cout << "Please select option:" << std::endl;
    std::cout << "1. Create User" << std::endl;
    std::cout << "2. Create Conference" << std::endl;
    std::cout << "3. Change a Users username" << std::endl;
    std::cout << "4. Change a Users password" << std::endl;
    std::cout << "5. Change a Conference details" << std::endl;
    std::cout << "6. Quit" << std::endl;
    std::cin >> selection;

    if (selection == 1)
    {
        std::cout << "Create User selected" << std::endl;
        createUser();
    }
    else if (selection == 2)
    {
        std::cout << "Create Conference selected" << std::endl;
        createConf();
    }
    else if (selection == 3)
    {
        std::cout << "Change a Users username selected" << std::endl;
        changeUsername();
    }
    else if (selection == 4)
    {
        std::cout << "Change a Users password selected" << std::endl;
        changePassword();
    }
    else if (selection == 5)
    {
        std::cout << "Change a Conferences details selected" << std::endl;
        changeConf();
    }
    else if (selection == 6)
    {
        std::cout << "Quit selected, Quitting..." << std::endl;
        return;
    }
    else
    {
        std::cout << "Incorrect Input, Quitting..." << std::endl;
        return;
    }
}

void createUser()
{
    std::string username;
    std::string password;
    std::string name;
    std::string email;
    std::string organisation;
    std::string phone;
    std::vector<std::string> keywords;
    UserType_t userType = AUTHOR;

    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter email: ";
    std::cin >> email;
    std::cout << "Enter organisation: ";
    std::cin >> organisation;
    std::cout << "Enter phone: ";
    std::cin >> phone;

    int keywordsInput = 1;
    while (keywordsInput == 1)
    {
        std::cout << "Select: " << std::endl;
        std::cout << "1. Add keyword" << std::endl;
        std::cout << "2. No more keywords" << std::endl;
        std::cin >> keywordsInput;

        if (keywordsInput == 1)
        {
            std::string keyword = "";
            std::cout << "Keyword: ";
            std::cin >> keyword;
            keywords.push_back(keyword);
        }
    }

    User user(
	username,
	name,
	email,
	organisation,
	phone,
	password,
	keywords,
        userType);

    bool userExists = db.existsUserName(username);

    std::cout << "User was ";
    if (!userExists)
    {
        db.createUser(user);
        std::cout << "created successfully" << std::endl;
    }
    else
        std::cout << "not created" << std::endl;

    adminMainMenu();
}

void createConf()
{
    bool active;
    std::string title;
    std::string topic;
    std::string description;
    std::string location;
    std::vector<std::string> keywords;
    int paperDeadlineD;
    int paperDeadlineM;
    int paperDeadlineY;
    int allocationDateD;
    int allocationDateM;
    int allocationDateY;
    int reviewDeadlineSoftD;
    int reviewDeadlineSoftM;
    int reviewDeadlineSoftY;
    int reviewDeadlineHardD;
    int reviewDeadlineHardM;
    int reviewDeadlineHardY;
    int discussionDeadlineD;
    int discussionDeadlineM;
    int discussionDeadlineY;
    int reviewersPerPaper;
    int postWordLimit;
    bool beforeDate = true;

    std::cout << "Is it active? true/false: ";
    std::cin >> active;
    std::cout << "Enter title: ";
    std::cin >> title;
    std::cout << "Enter topic: "; 
    std::cin >> topic;
    std::cout << "Enter description: "; 
    std::cin >> description;
    std::cout << "Enter location: ";
    std::cin >> location;

    int keywordsInput = 1;
    while (keywordsInput == 1)
    {
        std::cout << "Select: " << std::endl;
        std::cout << "1. Add keyword" << std::endl;
        std::cout << "2. No more keywords" << std::endl;
        std::cin >> keywordsInput;

        if (keywordsInput == 1)
        {
            std::string keyword = "";
            std::cout << "Keyword: ";
            std::cin >> keyword;
            keywords.push_back(keyword);
        }
    }

    std::cout << "Enter paper deadline day: ";
    std::cin >> paperDeadlineD;
    std::cout << "Enter paper deadline month: ";
    std::cin >> paperDeadlineM;
    std::cout << "Enter paper deadline year: ";
    std::cin >> paperDeadlineY;
    std::cout << "Enter allocation date day: ";
    std::cin >> allocationDateD;
    std::cout << "Enter allocation date month: ";
    std::cin >> allocationDateM;
    std::cout << "Enter allocation date year: ";
    std::cin >> allocationDateY;
    std::cout << "Enter review deadline soft day: ";
    std::cin >> reviewDeadlineSoftD;
    std::cout << "Enter review deadline soft month: ";
    std::cin >> reviewDeadlineSoftM;
    std::cout << "Enter review deadline soft year: ";
    std::cin >> reviewDeadlineSoftY;
    std::cout << "Enter review deadline hard day: ";
    std::cin >> reviewDeadlineHardD;
    std::cout << "Enter review deadline hard month: ";
    std::cin >> reviewDeadlineHardM;
    std::cout << "Enter review deadline hard year: ";
    std::cin >> reviewDeadlineHardY;
    std::cout << "Enter discussion deadline day: ";
    std::cin >> discussionDeadlineD;
    std::cout << "Enter discussion deadline month: ";
    std::cin >> discussionDeadlineM;
    std::cout << "Enter discussion deadline year: ";
    std::cin >> discussionDeadlineY;
    std::cout << "Enter reviewers per paper: ";
    std::cin >> reviewersPerPaper;
    std::cout << "Enter post word limit: ";
    std::cin >> postWordLimit;

    Date paperDeadline(paperDeadlineD, paperDeadlineM, paperDeadlineY);
    Date allocationDate(allocationDateD, allocationDateM, allocationDateY);
    Date reviewDeadlineSoft(reviewDeadlineSoftD, reviewDeadlineSoftM, reviewDeadlineSoftY); 
    Date reviewDeadlineHard(reviewDeadlineHardD, reviewDeadlineHardM, reviewDeadlineHardY);
    Date discussionDeadline(discussionDeadlineD, discussionDeadlineM, discussionDeadlineY);

    Conference conf(
        active,
	title,
	topic,
	description,
	location,
	keywords,
	beforeDate,
	paperDeadline,
	beforeDate,
	allocationDate,
	beforeDate,
	reviewDeadlineSoft,
	beforeDate,
	reviewDeadlineHard,
	beforeDate,
	discussionDeadline,
	reviewersPerPaper,
	postWordLimit
	);


    bool confExists = db.existsConfName(title);

    std::cout << "Conference was ";
    if (!confExists)
    {
        db.createConf(conf);
        std::cout << "created successfully" << std::endl;
    }
    else
        std::cout << "not created" << std::endl;

    adminMainMenu();
}

void changeUsername()
{
    std::string currentUN;
    std::string newUN;
    std::cout << "Enter username to change: ";
    std::cin >> currentUN;

    bool userExists = db.existsUserName(currentUN);
    
    if (userExists)
    {
        std::cout << "Enter new username: ";
        std::cin >> newUN;
        bool newUserExists = db.existsUserName(currentUN);

        if (!newUserExists)
        {
            db.adminChangeUserName(currentUN, newUN);
            std::cout << "Username changed successfully" << std::endl;
        }
        else
            std::cout << "Username not changed as already existed";
    }
    else
        std::cout << "User doesn't exist" << std::endl;

    adminMainMenu();
}

void changePassword()
{
    std::string username;
    std::string password;
    std::cout << "Enter username to change password for: ";
    std::cin >> username;

    bool userExists = db.existsUserName(username);
    
    if (userExists)
    {
        std::cout << "Enter new password: ";
        std::cin >> password;

        db.adminChangePassword(username, password);

        std::cout << "Password changed" << std::endl;
    }
    else
        std::cout << "User doesn't exist" << std::endl;

    adminMainMenu();
}

void changeConf()
{
    bool active;
    std::string title;
    std::string topic;
    std::string description;
    std::string location;
    std::vector<std::string> keywords;
    int paperDeadlineD;
    int paperDeadlineM;
    int paperDeadlineY;
    int allocationDateD;
    int allocationDateM;
    int allocationDateY;
    int reviewDeadlineSoftD;
    int reviewDeadlineSoftM;
    int reviewDeadlineSoftY;
    int reviewDeadlineHardD;
    int reviewDeadlineHardM;
    int reviewDeadlineHardY;
    int discussionDeadlineD;
    int discussionDeadlineM;
    int discussionDeadlineY;
    int reviewersPerPaper;
    int postWordLimit;
    bool beforeDate = true;

    std::cout << "Enter Conference name: " << std::endl;
    std::cin >> title;

    bool confExists = db.existsConfName(title);
    if (confExists)
    {
        Conference conf = db.fetchConference(title);
        std::cout << "Current Conference details are:" << std::endl;
        std::cout << "Title: " << conf.title << std::endl;
        std::cout << "Active: ";
        if (conf.isActive)
            std::cout << "yes" << std::endl;
        else
            std::cout << "no" << std::endl;
        std::cout << "Topic: " << conf.topic << std::endl;
        std::cout << "Description: " << conf.description << std::endl;
        std::cout << "Location: " << conf.location << std::endl;

        std::cout << "Keywords: " << std::endl;
        std::vector<std::string>::const_iterator it;
        for(it=conf.keywords.begin(); it!=conf.keywords.end(); it++)
        {
            std::cout << "\t" << *it << std::endl; 
        }

        std::cout << "Before paper deadline? "; 
        if (conf.isBeforePaperDeadline)
            std::cout << "yes" << std::endl;
        else
            std::cout << "no" << std::endl;
        std::cout << "Date: " << conf.paperDeadline.convertToString(); 
        
        std::cout << "Before allocation date? ";
        if (conf.isBeforeAllocationDate)
            std::cout << "yes" << std::endl;
        else
            std::cout << "no" << std::endl;
        std::cout << "Date: " << conf.allocationDate.convertToString(); 

        std::cout << "Before soft review deadline? ";
        if (conf.isBeforeSoftReviewDeadline)
            std::cout << "yes" << std::endl;
        else
            std::cout << "no" << std::endl;
        std::cout << "Date: " << conf.reviewDeadlineSoft.convertToString(); 

        std::cout << "Before hard review deadline? ";
        if (conf.isBeforeHardReviewDeadline)
            std::cout << "yes" << std::endl;
        else
            std::cout << "no" << std::endl;
        std::cout << "Date: " << conf.reviewDeadlineHard.convertToString(); 

        std::cout << "Before discussion deadline? ";
        if (conf.isBeforeDiscussDeadline)
            std::cout << "yes" << std::endl;
        else
            std::cout << "no" << std::endl;
        std::cout << "Date: " << conf.discussDeadline.convertToString(); 

        std::cout << "Reviewers per paper: " << conf.reviewersPerPaper;
        std::cout << "Word limit per post: " << conf.postWordLimit;

        std::cout << "Please enter new Conference details" << std::endl;
        std::cout << "Must re enter all details that aren't changing also!!" << std::endl << std::endl;


        std::cout << "Is it active? true/false: ";
        std::cin >> active;
        std::cout << "Enter title: ";
        std::cin >> title;
        std::cout << "Enter topic: "; 
        std::cin >> topic;
        std::cout << "Enter description: "; 
        std::cin >> description;
        std::cout << "Enter location: ";
        std::cin >> location;

        int keywordsInput = 1;
        while (keywordsInput == 1)
        {
            std::cout << "Select: " << std::endl;
            std::cout << "1. Add keyword" << std::endl;
            std::cout << "2. No more keywords" << std::endl;
            std::cin >> keywordsInput;

            if (keywordsInput == 1)
            {
                std::string keyword = "";
                std::cout << "Keyword: ";
                std::cin >> keyword;
                keywords.push_back(keyword);
            }
        }

        std::cout << "Enter paper deadline day: ";
        std::cin >> paperDeadlineD;
        std::cout << "Enter paper deadline month: ";
        std::cin >> paperDeadlineM;
        std::cout << "Enter paper deadline year: ";
        std::cin >> paperDeadlineY;
        std::cout << "Enter allocation date day: ";
        std::cin >> allocationDateD;
        std::cout << "Enter allocation date month: ";
        std::cin >> allocationDateM;
        std::cout << "Enter allocation date year: ";
        std::cin >> allocationDateY;
        std::cout << "Enter review deadline soft day: ";
        std::cin >> reviewDeadlineSoftD;
        std::cout << "Enter review deadline soft month: ";
        std::cin >> reviewDeadlineSoftM;
        std::cout << "Enter review deadline soft year: ";
        std::cin >> reviewDeadlineSoftY;
        std::cout << "Enter review deadline hard day: ";
        std::cin >> reviewDeadlineHardD;
        std::cout << "Enter review deadline hard month: ";
        std::cin >> reviewDeadlineHardM;
        std::cout << "Enter review deadline hard year: ";
        std::cin >> reviewDeadlineHardY;
        std::cout << "Enter discussion deadline day: ";
        std::cin >> discussionDeadlineD;
        std::cout << "Enter discussion deadline month: ";
        std::cin >> discussionDeadlineM;
        std::cout << "Enter discussion deadline year: ";
        std::cin >> discussionDeadlineY;
        std::cout << "Enter reviewers per paper: ";
        std::cin >> reviewersPerPaper;
        std::cout << "Enter post word limit: ";
        std::cin >> postWordLimit;

        Date paperDeadline(paperDeadlineD, paperDeadlineM, paperDeadlineY);
        Date allocationDate(allocationDateD, allocationDateM, allocationDateY);
        Date reviewDeadlineSoft(reviewDeadlineSoftD, reviewDeadlineSoftM, reviewDeadlineSoftY); 
        Date reviewDeadlineHard(reviewDeadlineHardD, reviewDeadlineHardM, reviewDeadlineHardY);
        Date discussionDeadline(discussionDeadlineD, discussionDeadlineM, discussionDeadlineY);

        std::cout << "Enter reviewers per paper: ";
        std::cin >> reviewersPerPaper;
        std::cout << "Enter post word limit: ";
        std::cin >> postWordLimit;

        Conference confInput(
            active,
            title,
            topic,
            description,
            location,
            keywords,
            conf.isBeforePaperDeadline,
            paperDeadline,
            conf.isBeforeAllocationDate,
            allocationDate,
            conf.isBeforeSoftReviewDeadline,
            reviewDeadlineSoft,
            conf.isBeforeHardReviewDeadline,
            reviewDeadlineHard,
            conf.isBeforeDiscussDeadline,
            discussionDeadline,
            reviewersPerPaper,
            postWordLimit
            );

        db.updateConf(confInput);

        std::cout << "Conference was created successfully" << std::endl;
    }
    else
        std::cout << "Conference doesn't exist" << std::endl;
    
    adminMainMenu();
}

