//
//  DerivedClass1.m
//  ClassHierarchy
//
//  Created by JesGalvan on 9/13/14.
//  Copyright (c) 2014 CS378HW2. All rights reserved.
//

#import "DerivedClass1.h"

@interface DerivedClass1 ()

@property (nonatomic, strong) NSString* college;
@property (nonatomic, strong) NSString* major;

@end

@implementation DerivedClass1

//standard init method
-(id) init
{
    self = [super init];
    if(self)
    {
        self.college = @"";
        self.major = @"";
    }
    return self;
}
//custom init method, accepts arguments for this class and base class
-(id)initWithStudentInfo:(NSString*)person_name : (NSNumber*)person_age : (NSString*)student_college : (NSString*)student_major
{
    //calling base class init and then setting properties for this class
    self = [[DerivedClass1 alloc] initWithPersonInfo : person_name : person_age ];
    self.college = student_college;
    self.major = student_major;
    
    return self;
}
//changes student college
-(void)setCollege:(NSString*)newCollege
{
    _college =  newCollege;
}
//changes student major
-(void)setMajor:(NSString*)newMajor
{
    _major = newMajor;
}
//returns student college
-(NSString*)getCollege
{
    return _college;
}
//returns student major
-(NSString*)getMajor
{
    return _major;
}


@end
