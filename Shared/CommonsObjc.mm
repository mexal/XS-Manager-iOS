#import "CommonsObjc.h"
#import "CommonLib.h"
#import "sqlite3.h"
#import <Foundation/Foundation.h>

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
        delete lib;
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
    Door* result = (Door*)calloc(sizeof(Door) * length, sizeof(Door) * length);
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
@end
