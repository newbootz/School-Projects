//
//  HW3ViewController.h
//  HW3
//
//  Created by JesGalvan on 9/16/14.
//  Copyright (c) 2014 CS378HW3. All rights reserved.
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
