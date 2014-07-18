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
    CommonLib* lib = new CommonLib([[self filePath] UTF8String]);
    return lib->processPersons([fromString UTF8String]);
}

+(NSString *) filePath
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory = [paths objectAtIndex:0];
    return [documentDirectory stringByAppendingPathComponent:@"xsmanager.sqlite"];
}

+(NSArray *)getPersons {
    CommonLib* lib = new CommonLib([[self filePath] UTF8String]);
    Person** persons = lib->getPersons();
//    NSArray* array = [[NSArray alloc] init];
//    for (int i = 0; i < count(persons); i++) {
//    }
    return nil;
}
@end
