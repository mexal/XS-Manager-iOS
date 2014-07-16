//  CommonLib.h
//  XS-Manager
//
//  Created by Ivan Kravchenko on 15/07/14.
//  Copyright (c) 2014 DORMA. All rights reserved.
//
#ifndef _PERF_CPLUSPLUS_
#define _PERF_CPLUSPLUS_

class CommonLib
{
public:
    static int processDoors(const char* xml);
    static int processPersons(const char* xml);
    static int processPermissions(const char* xml);
    static bool bindDoorToDevice(const char* doorNumber, const char* deviceUUID);
};

#endif //_PERF_CPLUSPLUS_