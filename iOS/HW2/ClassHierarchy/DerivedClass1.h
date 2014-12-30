//
//  DerivedClass1.h
//  ClassHierarchy
//
//  Created by JesGalvan on 9/13/14.
//  Copyright (c) 2014 CS378HW2. All rights reserved.
//

#import "BaseClass.h"

@interface DerivedClass1 : BaseClass

//methods for DerivedClass1, includes custom init that accepts argument that calls custom init for BaseClass
-(id)initWithStudentInfo:(NSString*)person_name : (NSNumber*)person_age : (NSString*)student_college : (NSString*)student_major;
-(void)setCollege:(NSString*)newCollege;
-(void)setMajor:(NSString*)newMajor;
-(NSString*)getCollege;
-(NSString*)getMajor;
@end
