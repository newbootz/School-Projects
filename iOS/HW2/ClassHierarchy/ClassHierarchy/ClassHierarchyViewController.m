//
//  ClassHierarchyViewController.m
//  ClassHierarchy
//
//  Created by JesGalvan on 9/13/14.
//  Copyright (c) 2014 CS378HW2. All rights reserved.
//

#import "ClassHierarchyViewController.h"
#import "BaseClass.h"
#import "DerivedClass1.h"
#import "DerivedClass2.h"


@interface ClassHierarchyViewController ()

@end

@implementation ClassHierarchyViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nb.
    
    //Creating instances by using custom init for each class
    BaseClass* b1 = [[BaseClass alloc] initWithPersonInfo:@"JESUS1" :[NSNumber numberWithInt:20]];
    DerivedClass1* d1 = [[DerivedClass1 alloc] initWithStudentInfo:@"JESUS2" :[NSNumber numberWithInt:21] : @"The University of Texas at Austin" : @"Computer Science"];
    DerivedClass2* d2 = [[DerivedClass2 alloc] initWithEmployeetInfo:@"JESUS3": [NSNumber numberWithInt:22] :@"IBM": @"Developer"];
    
    //changing properties of BaseClass instance
    NSLog(@"BaseClass: name: %@ age: %@", b1.getName, b1.getAge);
    NSLog(@"Changing properties of BaseClass");
    [b1 setAge:[NSNumber numberWithInt:10]];
    [b1 setName:@"CHANGED_NAME"];
    NSLog(@"BaseClass: name: %@ age: %@", b1.getName, b1.getAge);
    
    NSLog(@"");
    NSLog(@"");
    
    //Changing properties of DerivedClass1 instance
    NSLog(@"DerivedClass1: name: %@ age: %@ college: %@ major: %@", d1.getName, d1.getAge , d1.getCollege , d1.getMajor);
    NSLog(@"Changing properties of DerivedClass1");
    [d1 setCollege:@"CHANGED_COLLEGE"];
    [d1 setMajor:@"CHANGED_MAJOR"];
    NSLog(@"DerivedClass1: name: %@ age: %@ college: %@ major: %@", d1.getName, d1.getAge , d1.getCollege , d1.getMajor);
    
    NSLog(@"");
    NSLog(@"");
    
    //Changing properties of DerivedClass2 instance
    NSLog(@"DerivedClass2: name: %@ age: %@ company: %@ job: %@", d2.getName, d2.getAge , d2.getCompany , d2.getJob);
    NSLog(@"Changing properties of DerivedClass1");
    [d2 setCompany:@"CHANGED_COMPANY"];
    [d2 setJob:@"CHANGED_JOB"];
    NSLog(@"DerivedClass2: name: %@ age: %@ company: %@ job: %@", d2.getName, d2.getAge , d2.getCompany , d2.getJob);
   
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
