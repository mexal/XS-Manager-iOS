#include <stdlib.h>
#include <string.h>
#include "tinyxml2.h"
#include <iostream>
#include "sqlite3.h"
#include <stdio.h>

#include "CommonLib.h"

using namespace tinyxml2;
using namespace std;

CommonLib::CommonLib(const char* fileName) {
    if (sqlite3_open(fileName, &_database) != SQLITE_OK) {
        cout<<"Cannot create a databse"<<endl;
        return;
    }
    
    createTable(string("CREATE TABLE IF NOT EXISTS Persons (person_number TEXT UNIQUE NOT NULL, person_name TEXT NOT NULL);").c_str());
    createTable(string("CREATE TABLE IF NOT EXISTS Doors (door_number TEXT UNIQUE NOT NULL, door_name TEXT NOT NULL);").c_str());
}
CommonLib::~CommonLib() {
    sqlite3_close(_database);
}
void CommonLib::createTable(const char *sql) {
    char* errMsg;
    if (sqlite3_exec(_database, sql, NULL, NULL, &errMsg) != SQLITE_OK) {
        cout<<"Cannot create a table:"<<endl;
        sqlite3_free(errMsg);
    }
}

int CommonLib::processDoors(const char* xml) {
    
    XMLDocument doc;
    XMLError err = doc.Parse(xml);
    cout<<"Error:"<<err<<endl;
    if (err != 0) {
        return -1;
    }
    
    int count = 0;
    XMLElement *levelElement = doc.FirstChildElement("Doors");
    for (XMLElement* child = levelElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
    {
        count++;
        const char* number = child->Attribute("number");
        const char* name = child->Attribute("name");
        cout<<"Door number:"<<number<<",name:"<<name<<endl;
        string str = string("INSERT INTO Doors (door_number, door_name) VALUES ( ") + string(number) + " , \'" + string(name) + "\' )";
        const char* statement = str.c_str();
        char* sqlerr;
        if (sqlite3_exec(_database, statement, NULL, NULL, &sqlerr) != SQLITE_OK) {
            cout<<"Door not inserted:"<<sqlerr<<endl;
        } else {
            sqlite3_free(sqlerr);
            cout<<"Inserted person number:"<<number<<", name:"<<name<<endl;
        }
    }
    return count;
}

int CommonLib::processPersons(const char* xml) {
    
    XMLDocument doc;
    XMLError err = doc.Parse(xml);
    cout<<"Error:"<<err<<endl;
    if (err != 0) {
        return -1;
    }
    
    int count = 0;
    XMLElement *levelElement = doc.FirstChildElement("Persons");
    for (XMLElement* child = levelElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
    {
        count++;
        const char* number = child->Attribute("number");
        const char* name = child->Attribute("name");
        cout<<"Person number:"<<number<<",name:"<<name<<endl;
        string str = string("INSERT INTO Persons (person_number, person_name) VALUES ( ") + string(number) + " , \'" + string(name) + "\' )";
        const char* statement = str.c_str();
        char* sqlerr;
        if (sqlite3_exec(_database, statement, NULL, NULL, &sqlerr) != SQLITE_OK) {
            cout<<"Person not inserted:"<<sqlerr<<endl;
        } else {
            sqlite3_free(sqlerr);
            cout<<"Inserted person number:"<<number<<",name:"<<name<<endl;
        }
    }
    return count;
}

int CommonLib::processPermissions(const char* xml ) {
    return -1;
}

bool CommonLib::bindDoorToDevice(const char* doorNumber, const char* deviceUUID) {
    return false;
}

int CommonLib::getEntriesCount(char* tableName) {
    sqlite3_stmt *statement;
    if (sqlite3_prepare(_database, (string("SELECT COUNT(*) FROM ") + string(tableName)).c_str(), -1, &statement, 0 ) == SQLITE_OK )
    {
        if (sqlite3_step(statement) == SQLITE_ROW)
        {
            return sqlite3_column_int(statement, 0);
        } else
        {
            return 0;
        }
    } else {
        return 0;
    }
}

int CommonLib::getPersonsLength() {
    return CommonLib::getEntriesCount((char*)string("Persons").c_str());
}

void CommonLib::getPersons(Person* result) {
    sqlite3_stmt *statement;
    if ( sqlite3_prepare(_database, string("SELECT * FROM Persons").c_str(), -1, &statement, 0 ) == SQLITE_OK )
    {
        while ( true )
        {
            int res = sqlite3_step(statement);
            
            if ( res == SQLITE_ROW )
            {
                char *number = (char*)sqlite3_column_text(statement, 0);
                result->number = (char*) malloc(strlen(number));
                strcpy(result->number , (const char*)sqlite3_column_text(statement, 0));
                char *name = (char*)sqlite3_column_text(statement, 1);
                result->name = (char*) malloc(strlen(name));
                strcpy(result->name , (const char*)sqlite3_column_text(statement, 1));
                
                result++;
            
            }
            else if ( res == SQLITE_DONE || res==SQLITE_ERROR)
            {
                cout << "done " << endl;
                return;
            }
        }
    }
}

int CommonLib::getDoorsLength() {
    return getEntriesCount((char*)string("Doors").c_str());
}

void CommonLib::getDoors(Door *result) {
    sqlite3_stmt *statement;
    if ( sqlite3_prepare(_database, string("SELECT * FROM Doors").c_str(), -1, &statement, 0 ) == SQLITE_OK )
    {
        while ( true )
        {
            int res = sqlite3_step(statement);
            
            if ( res == SQLITE_ROW )
            {
                char *number = (char*)sqlite3_column_text(statement, 0);
                result->number = (char*) malloc(strlen(number));
                strcpy(result->number , (const char*)sqlite3_column_text(statement, 0));
                char *name = (char*)sqlite3_column_text(statement, 1);
                result->name = (char*) malloc(strlen(name));
                strcpy(result->name , (const char*)sqlite3_column_text(statement, 1));
                
                result++;
                
            }
            else if ( res == SQLITE_DONE || res==SQLITE_ERROR)
            {
                cout << "done " << endl;
                return;
            }
        }
    }

}
