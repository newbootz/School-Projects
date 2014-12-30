//
//  HW3ViewController.m
//  TestPageVC
//
//  Created by JesGalvan on 9/27/14.
//  Copyright (c) 2014 Infinity Software. All rights reserved.
//

#import "HW3ViewController.h"

@interface HW3ViewController ()

@end

@implementation HW3ViewController

- (void)viewDidLoad
{
    NSLog(@"HW3ViewController viewDidLoad");
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    DataModel * datamodel = [[DataModel alloc]init];
    
    datamodel.delegate = self;
    
    self.name.delegate = self;
    self.city.delegate = self;
    
    //self references the viewcontroller or view your textField is on
    //self.yourUITextFieldObject.delegate = self;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)modifedData:(NSString *)data
{
    NSLog(@"HW3ViewController modifiedData");
    
    /*This method should use GCD to modify the <message label> UI element (so it should
     use the main UI queue) with the string passed in; after delaying 5 seconds.*/
    sleep(5);
    [[NSOperationQueue mainQueue] addOperationWithBlock:^{
        
        //Do any updates to your label here
        self.label.text = data;
        
    }];
    
    NSLog(@"Exiting modifiedData");
}

- (IBAction)button:(id)sender {
    NSLog(@"HW3ViewController button handler");
    [self.name resignFirstResponder];
    [self.city resignFirstResponder];
    /*The button handler should get the name and city values from the text fields and, if both
     are not empty, call the DataModel saveWithName:AndCity: method, passing in the two
     values.
     If either name or city is empty, update the message label text to say “You must enter a
     value for *both* name and city”.*/
    if (self.name.text && self.name.text.length > 0 && self.city.text && self.city.text.length > 0 )
    {
        
        DataModel * datamodel = [[DataModel alloc]init];
        datamodel.delegate = self;
        [datamodel saveWithName: self.name.text AndCity: self.city.text];
        
        
        
        
        
    }
    else
    {
        
        //NSLog(@"You must enter a value for *both* name and city");
        self.label.text = @"You must enter a value for *both* name and city";
        
        
    }
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    NSLog(@"HW3ViewController.m remove textfield");
    [textField resignFirstResponder];
    
    return YES;
}
@end
