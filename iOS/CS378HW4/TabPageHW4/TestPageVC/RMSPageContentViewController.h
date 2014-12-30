//
//  RMSPageContentViewController.h
//  TestPageVC
//
//  Created by Robert Seitsinger on 9/18/14.
//  Copyright (c) 2014 Infinity Software. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RMSPageContentViewController : UIViewController
@property (weak, nonatomic) IBOutlet UIImageView *imgBackground;
@property (weak, nonatomic) IBOutlet UILabel *lblTitle;

@property NSUInteger pageIndex;
@property NSString *titleText;
@property NSString *imageFile;

@end
