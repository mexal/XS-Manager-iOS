//  CommonLib.h
//  XS-Manager
//
//  Created by Ivan Kravchenko on 15/07/14.
//  Copyright (c) 2014 DORMA. All rights reserved.
//
#ifndef _PERF_CPLUSPLUS_
#define _PERF_CPLUSPLUS_

#include <string.h>
#include <stdlib.h>

class CommonLib
{
public:
    static int processDoors(std::string* xml);
    static int processPersons(std::string* xml);
    static int processPermissions(std::string* xml);
    static bool bindDoorToDevice(std::string* doorNumber, std::string* deviceUUID);
};

#endif //_PERF_CPLUSPLUS_