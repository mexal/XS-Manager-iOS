
//  CommonsObjc.m
//  XS-Manager
//
//  Created by Ivan Kravchenko on 15/07/14.
//  Copyright (c) 2014 DORMA. All rights reserved.
//
#import "CommonsObjc.h"
#import "CommonLib.h"
#import "sqlite3.h"
#import <Foundation/Foundation.h>
#import "DRMPerson.h"

@implementation CommonsObjc

+(int)processPersons:(NSString *)fromString {
    CommonLib* lib = new CommonLib([[self filePath] UTF8String]);
    int result = lib->processPersons([fromString UTF8String]);
    delete lib;
    return result;
}

+(NSString *) filePath
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory = [paths objectAtIndex:0];
    return [documentDirectory stringByAppendingPathComponent:@"xsmanager.sqlite"];
}

+(NSArray*)getPersons {
    CommonLib* lib = new CommonLib([[self filePath] UTF8String]);
    int length = lib->getPersonsLength();
    if (length == 0) {
        return nil;
    }
    Person* result = (Person*)calloc(sizeof(Person) * length, sizeof(Person) * length);
    lib->getPersons(result);
    NSMutableArray *arr = [NSMutableArray new];
    for (int i = 0; i < length; i++) {
        DRMPerson* p = [DRMPerson new];
        p.number = [NSString stringWithUTF8String:(result + i)->number];
        p.name = [NSString stringWithUTF8String:(result + i)->name];
        [arr addObject:p];
        delete result->number;
        result->number = NULL;
        delete result->name;
        result->name = NULL;
    }
    delete result;
    result = NULL;
    
    return arr;
}
@end
