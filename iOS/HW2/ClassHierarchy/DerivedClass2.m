//
//  DerivedClass2.m
//  ClassHierarchy
//
//  Created by JesGalvan on 9/13/14.
//  Copyright (c) 2014 CS378HW2. All rights reserved.
//

#import "DerivedClass2.h"
@interface DerivedClass2 ()

@property (nonatomic, strong) NSString* company;
@property (nonatomic, strong) NSString* job;

@end


@implementation DerivedClass2


//standard init method
-(id) init
{
    self = [super init];
    if(self)
    {
        self.company = @"";
        self.job = @"";
    }
    return self;
}
//custom init method that accepts arguments, calls base class init and sets properties in this class too
-(id)initWithEmployeetInfo:(NSString*)person_name : (NSNumber*)person_age : (NSString*)employee_company : (NSString*)employee_job
{
    //calling custom init method for base class to set properties, then sets properties for this class
    self = [[DerivedClass2 alloc] initWithPersonInfo : person_name : person_age ];
    self.company = employee_company;
    self.job = employee_job;
    
    return self;
}
//changes employee company
-(void)setCompany:(NSString*)newCompany
{
    _company =  newCompany;
}
//changes employee job
-(void)setJob:(NSString *)newJob
{
    _job = newJob;
}
//returns employee company
-(NSString*)getCompany
{
    return _company;
}
//returns employee company
-(NSString*)getJob
{
    return _job;
}


@end
