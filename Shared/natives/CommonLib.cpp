#include <stdlib.h>
#include <string.h>
#include "tinyxml2.h"
#include <iostream>
#include "sqlite3.h"
#include <stdio.h>

#include "CommonLib.h" // Старайся свои .h подключать первыми, тогда не нужно будет подключать те либы, которые ты используешь в .h в .cpp повторно

using namespace tinyxml2;
using namespace std;

CommonLib::CommonLib(const char* fileName) {
    if (sqlite3_open(fileName, &_database) != SQLITE_OK) {
        cout<<"Cannot create a databse"<<endl;
        return;
    }
    
    createTable(string("CREATE TABLE IF NOT EXISTS Persons (person_number TEXT UNIQUE NOT NULL, person_name TEXT NOT NULL);").c_str());
    createTable(string("CREATE TABLE IF NOT EXISTS Doors (door_number TEXT UNIQUE NOT NULL, door_name TEXT NOT NULL);").c_str());
    createTable(string("CREATE TABLE IF NOT EXISTS Permissions (permission_door_number TEXT NOT NULL, permission_person_number TEXT NOT NULL, PRIMARY KEY (permission_door_number, permission_person_number));").c_str());
    createTable(string("CREATE TABLE IF NOT EXISTS Doors2Devices (dd_door_number TEXT UNIQUE NOT NULL, dd_device_uuid TEXT UNIQUE NOT NULL);").c_str());
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
        string str = string("INSERT INTO Doors (door_number, door_name) VALUES ( ") + string(number) + " , \'" + string(name) + "\' )"; // в C++ здесь, в отличии от Java лишнее копирование происходит. Можно просто так: string str("...");
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

int CommonLib::processPermissions(const char* xml) {
    XMLDocument doc;
    XMLError err = doc.Parse(xml);
    cout<<"Error:"<<err<<endl;
    if (err != 0) {
        return -1;
    }
    
    int count = 0;
    XMLElement *levelElement = doc.FirstChildElement("Permissions");
    for (XMLElement* child = levelElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
    {
        count++;
        const char* doorNumber = child->Attribute("doorNumber");
        const char* personNumber = child->Attribute("personNumber");
        cout<<"Permission doorNumber:"<<doorNumber<<", personNumber:"<<personNumber<<endl;
        string str = string("INSERT INTO Permissions (permission_door_number, permission_person_number) VALUES ( ") + string(doorNumber) + " , \'" + string(personNumber) + "\' )";
        const char* statement = str.c_str();
        char* sqlerr;
        if (sqlite3_exec(_database, statement, NULL, NULL, &sqlerr) != SQLITE_OK) {
            cout<<"Person not inserted:"<<sqlerr<<endl;
        } else {
            sqlite3_free(sqlerr);
            cout<<"Inserted person number:"<<doorNumber<<",name:"<<personNumber<<endl;
        }
    }
    return count;
}

int CommonLib::getPermissionsLength() {
    return getEntriesCount((char*)string("Permissions").c_str()); //  не нужно оборачивать в string, можно просто: return getEntriesCount("Permissions"); Но getEntriesCount должна принимать const char *. Её можно изменить спокойно, я посмотрел ниже
}

void CommonLib::getPermissions(Permission* result) {
    sqlite3_stmt *statement;
    if (sqlite3_prepare(_database, string("SELECT * FROM Permissions ORDER BY permission_door_number ASC").c_str(), -1, &statement, 0 ) == SQLITE_OK )
    {
        while ( true )
        {
            int res = sqlite3_step(statement);
            
            if ( res == SQLITE_ROW )
            {
                char *doorNumber = (char*)sqlite3_column_text(statement, 0);
                result->doorNumber = (char*) malloc(strlen(doorNumber));
                strcpy(result->doorNumber , (const char*)sqlite3_column_text(statement, 0));
                char *personNumber = (char*)sqlite3_column_text(statement, 1);
                result->personNumber = (char*) malloc(strlen(personNumber));
                strcpy(result->personNumber , (const char*)sqlite3_column_text(statement, 1));
                
                result++;
                
            }
            else if ( res == SQLITE_DONE || res==SQLITE_ERROR)
            {
                cout << "done " << endl;
                sqlite3_reset(statement);
                return;
            }
        }
    }

}

bool CommonLib::bindDoorToDevice(const char* doorNumber, const char* deviceUUID) {
    return false;
}

int CommonLib::getEntriesCount(char* tableName) { // лучше передавать const char *, у тебя же значение не меняется
    sqlite3_stmt *statement;
    if (sqlite3_prepare(_database, (string("SELECT COUNT(*) FROM ") + string(tableName)).c_str(), -1, &statement, 0 ) == SQLITE_OK )
    {
        if (sqlite3_step(statement) == SQLITE_ROW)
        {
            int result = sqlite3_column_int(statement, 0);
            sqlite3_reset(statement); // не уверен, но, похоже, это и для else ветки нужно вызвать
            return result;
        } else
        {
            return 0;
        }
    } else {
        return 0;
    }
}

int CommonLib::getPersonsLength() {
    return CommonLib::getEntriesCount((char*)string("Persons").c_str()); // то же что выше по поводу оборачивания строк, плюс CommonLib:: тоже не нужен вовсе, ты и так внутри этого класса
}

void CommonLib::getPersons(Person* result) {
    sqlite3_stmt *statement;
    if (sqlite3_prepare(_database, string("SELECT * FROM Persons").c_str(), -1, &statement, 0 ) == SQLITE_OK )
    {
        while ( true )
        {
            int res = sqlite3_step(statement);
            
            if ( res == SQLITE_ROW )
            {
                char *number = (char*)sqlite3_column_text(statement, 0);
                result->number = (char*) malloc(strlen(number)); // эту память нужно бы где-то освобождать. Лучше бы это делать в деструкторе Person, а в конструкторе выделять. И кто тебе сказал, что использовать сишный malloc - хорошая идея. Для С++ стоит использовать new.
                strcpy(result->number , (const char*)sqlite3_column_text(statement, 0)); // строки в стиле C должны заканчиваться нулём, поэтому нужно выделять размер строки + 1 и в последний байт ноль записывать, а то можно отгрести. Все функции для работы со строками в C ищут конец строки по нулю. С той же strlen сразу огребёшь 
                char *name = (char*)sqlite3_column_text(statement, 1);
                result->name = (char*) malloc(strlen(name));
                strcpy(result->name , (const char*)sqlite3_column_text(statement, 1));
                
                result++;
            
            }
            else if ( res == SQLITE_DONE || res==SQLITE_ERROR)
            {
                cout << "done " << endl;
                sqlite3_reset(statement);
                return;
            }
        }
    }
}

int CommonLib::getDoorsLength() {
    return getEntriesCount((char*)string("Doors").c_str());  // return getEntriesCount("Doors"); !!!!
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
                sqlite3_reset(statement);
                return;
            }
        }
    }

}
