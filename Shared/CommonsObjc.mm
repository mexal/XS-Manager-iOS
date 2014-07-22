#import "CommonsObjc.h"
#import "CommonLib.h"
#import "sqlite3.h"
#import <Foundation/Foundation.h>

@implementation CommonsObjc

+(NSString *) filePath
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentDirectory = [paths objectAtIndex:0];
    return [documentDirectory stringByAppendingPathComponent:@"xsmanager.sqlite"];
}

+(int)processPersons:(NSString *)fromString {
    CommonLib* lib = new CommonLib([[self filePath] UTF8String]);
    int result = lib->processPersons([fromString UTF8String]);
    delete lib;
    return result;
}

+(NSArray*)getPersons {
    CommonLib* lib = new CommonLib([[self filePath] UTF8String]);
    int length = lib->getPersonsLength();
    if (length == 0) {
        delete lib;
        return nil;
    }
    Person* result = (Person*)malloc(sizeof(Person) * length);
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
    delete lib;
    
    return arr;
}

+(int)processDoors:(NSString *)fromString {
    CommonLib* lib = new CommonLib([[self filePath] UTF8String]);
    int result = lib->processDoors([fromString UTF8String]);
    delete lib;
    return result;
}

+(NSArray*)getDoors {
    CommonLib* lib = new CommonLib([[self filePath] UTF8String]);
    int length = lib->getDoorsLength();
    if (length == 0) {
        delete lib;
        return nil;
    }
    Door* result = (Door*)malloc(sizeof(Door) * length);
    lib->getDoors(result);
    NSMutableArray *arr = [NSMutableArray new];
    for (int i = 0; i < length; i++) {
        DRMDoor* p = [DRMDoor new];
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
    delete lib;
    
    return arr;
}

+(int)processPermissions:(NSString *)fromString {
    CommonLib* lib = new CommonLib([[self filePath] UTF8String]);
    int result = lib->processPermissions([fromString UTF8String]);
    delete lib;
    return result;
}

+(NSArray*)getPermissions {
    CommonLib* lib = new CommonLib([[self filePath] UTF8String]);
    int length = lib->getPermissionsLength();
    if (length == 0) {
        delete lib;
        return nil;
    }
    Permission* result = (Permission*)malloc(sizeof(Permission) * length);
    lib->getPermissions(result);
    NSMutableArray *arr = [NSMutableArray new];
    for (int i = 0; i < length; i++) {
        DRMPermission* p = [DRMPermission new];
        p.doorNumber = [NSString stringWithUTF8String:(result + i)->doorNumber];
        p.personNumber = [NSString stringWithUTF8String:(result + i)->personNumber];
        [arr addObject:p];
        delete result->doorNumber;
        result->doorNumber = NULL;
        delete result->personNumber;
        result->personNumber = NULL;
    }
    delete result;
    result = NULL;
    delete lib;
    
    return arr;
}
@end
