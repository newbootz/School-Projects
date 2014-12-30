//
//  BaseClass.m
//  ClassHierarchy
//
//  Created by JesGalvan on 9/13/14.
//  Copyright (c) 2014 CS378HW2. All rights reserved.
//

#import "BaseClass.h"
@interface BaseClass ()

@property (nonatomic, strong) NSString* name;
@property (nonatomic, strong) NSNumber* age;

@end
@implementation BaseClass

//standard init method
-(id) init
{
    self = [super init];
    if(self)
    {
        self.name = @"";
        self.age = 0;
    }
    return self;
}

//custom init method
-(id)initWithPersonInfo:(NSString*)person_name : (NSNumber*)person_age
{
    self = [super init];
    self.name = person_name;
    self.age = person_age;
    return self;
}

//method that returns persons age
-(NSNumber*)getAge
{
    return _age;
}

//method that gets persons age
-(NSString*)getName
{
    return _name;
}

//method that changes persons name
-(void)setName:(NSString*)newName
{
    //might need to change ?
    _name = newName;
}

//method that changes persons age
-(void)setAge:(NSNumber*)newAge
{
    _age = newAge;
}

@end
