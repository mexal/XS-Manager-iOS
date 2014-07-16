//
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

@implementation CommonsObjc

+(int)processPersons:(NSString *)fromString {
    sqlite3 *_database;
    if (sqlite3_open([[self filePath] UTF8String], &_database) != SQLITE_OK) {
        NSLog(@"Failed to create a database");
        return -1;
    }
    
    char* errMsg;
    NSString* statement = @"CREATE TABLE IF NOT EXISTS Persons (person_number TEXT, person_name TEXT);";
    if (sqlite3_exec(_database, [statement UTF8String], NULL, NULL, &errMsg) != SQLITE_OK) {
        NSLog(@"Failed to create persons table");
        return -1;
    }
    
    const char *str = [fromString UTF8String];
    CommonLib* lib = new CommonLib(_database);
    int result = lib->processPersons(str);
    return result;
}

+(NSString *) filePath
{
    NSArray *paths=NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory=[paths objectAtIndex:0];
    return [documentDirectory stringByAppendingPathComponent:@"xsmanager.sqlite"];
}
@end
