//
//  RMSViewController.h
//  TestPageVC
//
//  Created by Robert Seitsinger on 9/18/14.
//  Copyright (c) 2014 Infinity Software. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RMSViewController : UIViewController <UIPageViewControllerDataSource>
@property (strong, nonatomic) UIPageViewController *pageViewController;
@property (strong, nonatomic) NSArray *pageTitles;
@property (strong, nonatomic) NSArray *pageImages;

@property (weak, nonatomic) IBOutlet UIButton *btnStartAgain;

- (IBAction)startShow:(id)sender;

@end
