//
//  BaseClass.h
//  ClassHierarchy
//
//  Created by JesGalvan on 9/13/14.
//  Copyright (c) 2014 CS378HW2. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface BaseClass : NSObject

//methods for BaseClass, includes custom init that accepts arguments
-(id)initWithPersonInfo:(NSString*)person_name : (NSNumber*)person_age;
-(NSNumber*)getAge;
-(NSString*)getName;
-(void)setName:(NSString*)newName;
-(void)setAge:(NSNumber*)newAge;

@end
