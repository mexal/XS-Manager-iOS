#include <Foundation/Foundation.h>
#import "DRMPerson.h"
#import "DRMDoor.h"
#import "DRMPermission.h"

@interface CommonsObjc : NSObject

+(int) processPersons: (NSString*) fromString;
+(int) processDoors: (NSString*) fromString;
+(int) processPermissions:(NSString *)fromString;
+(NSArray* ) getPersons;
+(NSArray* ) getDoors;
+(NSArray* ) getPermissions;

+(NSString *) filePath;
@end
