//
//  HW3ViewController.h
//  TestPageVC
//
//  Created by JesGalvan on 9/27/14.
//  Copyright (c) 2014 Infinity Software. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DataModel.h"
@interface HW3ViewController : UIViewController <DataModelProtocol, UITextFieldDelegate>
//@interface HW3ViewController : UIViewController <UITextFieldDelegate>

@property (strong, nonatomic) IBOutlet UILabel *label;

- (IBAction)button:(id)sender;

@property (strong, nonatomic) IBOutlet UITextField *name;

@property (strong, nonatomic) IBOutlet UITextField *city;


@end