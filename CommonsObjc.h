//
//  CommonsObjc.h
//  XS-Manager
//
//  Created by Ivan Kravchenko on 15/07/14.
//  Copyright (c) 2014 DORMA. All rights reserved.
//

#include <Foundation/Foundation.h>

@interface CommonsObjc : NSObject
+(int) processPersons: (NSString*) fromString;
+(NSString *) filePath;
@end
