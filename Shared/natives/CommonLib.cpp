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
    }
}
CommonLib::~CommonLib() {
    sqlite3_close(_database);
}

int CommonLib::processDoors(const char* xml) {
    return -1;
}

int CommonLib::processPersons(const char* xml) {
    char* errMsg;
    string statement = string("CREATE TABLE IF NOT EXISTS Persons (person_number TEXT UNIQUE NOT NULL, person_name TEXT NOT NULL);");
    if (sqlite3_exec(_database, statement.c_str(), NULL, NULL, &errMsg) != SQLITE_OK) {
        cout<<"Cannot create a table"<<endl;
        return -1;
    }
    
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

Person* CommonLib::getPersons() {
    Person *result;
    result = (Person*) malloc (sizeof(Person)*3);
    Person *output = result;
    sqlite3_stmt *statement;
    if ( sqlite3_prepare(_database, string("SELECT * FROM Persons").c_str(), -1, &statement, 0 ) == SQLITE_OK )
    {
    
        //int ctotal = sqlite3_column_count(statement);
        while ( true )
        {
            int res = sqlite3_step(statement);
            
            if ( res == SQLITE_ROW )
            {
                 char *name = ( char*)sqlite3_column_text(statement, 0);
                int size = strlen(name);
                result->name = ( char*) malloc(size);
                
                strcpy(result->name , name);
                //result[el].number = sqlite3_column_text(statement, 0);
            
                result++;
            
            }
            else if ( res == SQLITE_DONE || res==SQLITE_ERROR)
            {
                cout << "done " << endl;
                return output;
            }
        }
    }
    
    return NULL;
}
