//
//  RMSPageContentViewController.m
//  TestPageVC
//
//  Created by Robert Seitsinger on 9/18/14.
//  Copyright (c) 2014 Infinity Software. All rights reserved.
//

#import "RMSPageContentViewController.h"

@interface RMSPageContentViewController ()

@end

@implementation RMSPageContentViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.

    self.imgBackground.image = [UIImage imageNamed:self.imageFile];
    self.lblTitle.text = self.titleText;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
