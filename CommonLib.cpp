//
//  CommonLib.cpp
//  XS-Manager
//
//  Created by Ivan Kravchenko on 15/07/14.
//  Copyright (c) 2014 DORMA. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "tinyxml2.h"
#include <iostream>
#include "sqlite3.h"

#include "CommonLib.h"

using namespace tinyxml2;
using namespace std;

CommonLib::CommonLib(sqlite3* database) {
    _database = database;
}
CommonLib::~CommonLib() {
}

int CommonLib::processDoors(const char* xml) {
    return -1;
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
