//
//  CommonsObjc.m
//  XS-Manager
//
//  Created by Ivan Kravchenko on 15/07/14.
//  Copyright (c) 2014 DORMA. All rights reserved.
//
#import "CommonsObjc.h"
#import "CommonLib.h"

@implementation CommonsObjc

+(int)processPersons:(NSString *)fromString {
    int result = CommonLib::processPersons((std::string)fromString);
    return result;
}
@end
