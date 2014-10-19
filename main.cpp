#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#include "MyRecord.h"
#include "MyRecordStore.h"

#include <vector>

typedef MyRecord* RecordPtr;
std::vector<RecordPtr> g_theRecords;

//std::string getImage(std::string filename);

static void createData();

int main(int arc, char *argv[])
{
        createData();
        MyRecordStore astore;
        if (!astore.isOK())
        {
                std::cout << "Failed to open database file" << std::endl;
                exit(1);
        }

        vector<RecordPtr>::const_iterator it;
        for(it=g_theRecords.begin(); it!=g_theRecords.end(); it++)
        {
                RecordPtr ptr = (*it);
                const char* key = ptr->getID().c_str();
                astore.put(key, ptr);
                std::cout << "Wrote record " << key << std::endl;
        }
        return EXIT_SUCCESS;
}

//static std::string getImage(std::string filename)
//{
//      // Qt library has its own string class, convert STL string
//      QString qtfilename(filename.c_str());
//      QImage animage;
//      bool readimage = animage.load(qtfilename);
//      if (!readimage)
//      {
//              std::cout << "Image load failed for " << filename << std::endl << "Bye" << std::endl;
//              exit(1);
//      }
//
//      QImage resized = animage.scaledToWidth(50, Qt::FastTransformation);
//
//      QByteArray ba;
//      QBuffer buf(&ba);
//      resized.save(&buf, "JPG");
//      
//      QByteArray coded = ba.toBase64();
//      std::string result(coded); // relying on QByteArray operator char*
//      return result;
//}

static void createData()
{
        // Hard code procedural creation of a few records so that can
        // have some data to show in the Qt based GUI
        RecordPtr next;
        std::string id;
        std::string name;
        std::string aRole;
        std::string imagestr;
        std::string file;

        // You will need to adjust filenames etc to match the image files
        // that you provide
        {
                id = "tom";
                name = "Thomas";
                file = "./images/om.jpg";
//              imagestr = getImage(file);
                next = new MyRecord(id);
                next->setName(name);
//              next->setImage(imagestr);
                aRole = "Boss";
                next->addRole(aRole);
                aRole="Manager";
                next->addRole(aRole);
                std::string email = "boos_tom@ourcompany.com.au";
                next->setEmail(email);
                std::string phones = "Phones";
                std::string mbl = "Mobile";
                std::string phnnum = "04666666666";
                next->addKeyValue(phones, mbl, phnnum);
                std::string others = "Other";
                std::string key = "Height";
                std::string value = "1.89m";
                next->addKeyValue(others, key, value);
                key = "Golf Handicap";
                value = "6";
                next->addKeyValue(others, key, value);
                g_theRecords.push_back(next);
        }
        {
                id = "dick";
                name = "Dick";
                file = "./images/dick.jpg";
//              imagestr = getImage(file);
                next = new MyRecord(id);
                next->setName(name);
//              next->setImage(imagestr);
                aRole="Accountant";
                next->addRole(aRole);
                std::string info = "Dick was recruited from starbucks and so knows how to set up \na company so that pays no tax";
                next->setInfo(info);
                std::string email = "clever_dick@ourcompany.com.au";
                next->setEmail(email);
                std::string phones = "Phones";
                std::string mbl = "Mobile";
                std::string phnnum = "04666667666";
                next->addKeyValue(phones, mbl, phnnum);
                g_theRecords.push_back(next);
        }
}
