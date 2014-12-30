//
//  DerivedClass2.h
//  ClassHierarchy
//
//  Created by JesGalvan on 9/13/14.
//  Copyright (c) 2014 CS378HW2. All rights reserved.
//

#import "BaseClass.h"

@interface DerivedClass2 : BaseClass


//methods for DerivedClass2, includes custom init that accepts arguments for Base class
-(id)initWithEmployeetInfo:(NSString*)person_name : (NSNumber*)person_age : (NSString*)employee_company : (NSString*)employee_job;
-(void)setCompany:(NSString*)newCompany;
-(void)setJob:(NSString*)newJob;
-(NSString*)getCompany;
-(NSString*)getJob;
@end
