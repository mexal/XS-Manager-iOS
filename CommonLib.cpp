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

#include "CommonLib.h"

using namespace tinyxml2;
using namespace std;

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
    
    XMLElement *levelElement = doc.FirstChildElement("Persons");
    for (XMLElement* child = levelElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
    {
        const char* number = child->Attribute("number");
        const char* name = child->Attribute("name");
        cout<<"Person number:"<<number<<",name:"<<name<<endl;
    }
    
//    const char* title = doc.FirstChildElement( "Persons" )->FirstChildElement( "Person" )->FirstAttribute()->Value();
//    printf( "Person number (1): %s\n", title );
    
//    // Text is just another Node to TinyXML-2. The more
//    // general way to get to the XMLText:
//    XMLText* textNode = doc.FirstChildElement( "PLAY" )->FirstChildElement( "TITLE" )->FirstChild()->ToText();
//    title = textNode->Value();
//    printf( "Name of play (2): %s\n", title );
    return -1;
}

int CommonLib::processPermissions(const char* xml ) {
    return -1;
}

bool CommonLib::bindDoorToDevice(const char* doorNumber, const char* deviceUUID) {
    return false;
}
