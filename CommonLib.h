//  CommonLib.h
//  XS-Manager
//
//  Created by Ivan Kravchenko on 15/07/14.
//  Copyright (c) 2014 DORMA. All rights reserved.
//
#ifndef _PERF_CPLUSPLUS_
#define _PERF_CPLUSPLUS_

#import "sqlite3.h"

class CommonLib
{
public:
    CommonLib(sqlite3* database);
    ~CommonLib();
    int processDoors(const char* xml);
    int processPersons(const char* xml);
    int processPermissions(const char* xml);
    bool bindDoorToDevice(const char* doorNumber, const char* deviceUUID);
private:
    sqlite3* _database;
};

#endif //_PERF_CPLUSPLUS_