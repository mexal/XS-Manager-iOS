//
//  CommonsObjc.h
//  XS-Manager
//
//  Created by Ivan Kravchenko on 15/07/14.
//  Copyright (c) 2014 DORMA. All rights reserved.
//

#include <Foundation/Foundation.h>
#import "DRMPerson.h"
#import "DRMDoor.h"

@interface CommonsObjc : NSObject

+(int) processPersons: (NSString*) fromString;
+(int) processDoors: (NSString*) fromString;
+(NSArray* ) getPersons;
+(NSArray* ) getDoors;

+(NSString *) filePath;
@end
