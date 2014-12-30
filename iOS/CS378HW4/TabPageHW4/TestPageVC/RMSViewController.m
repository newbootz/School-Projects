//
//  RMSViewController.m
//  TestPageVC
//
//  Created by Robert Seitsinger on 9/18/14.
//  Copyright (c) 2014 Infinity Software. All rights reserved.
//

#import "RMSViewController.h"
#import "RMSPageContentViewController.h"

@interface RMSViewController ()

@end

@implementation RMSViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.

    // Set our data model
    _pageTitles = @[@"Christ the Redeemer Statue", @"Great Wall of China", @"Roman Colosseum", @"Petra, Jordan", @"Machu Picchu", @"Chichen Itza", @"Taj Mahal", @"Great Pyramids of Giza"];
    _pageImages = @[@"wonders1.png", @"wonders2.png", @"wonders3.png", @"wonders4.png", @"wonders5.png", @"wonders6.png", @"wonders7.png", @"wonders8.png"];
    
    // Create page view controller
    self.pageViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"PageViewController"];
    self.pageViewController.dataSource = self;
    
    // Set the view controllers the page view controller will manage
    RMSPageContentViewController *startingViewController = [self viewControllerAtIndex:0];
    NSArray *viewControllers = @[startingViewController];
    [self.pageViewController setViewControllers:viewControllers direction:UIPageViewControllerNavigationDirectionForward animated:NO completion:nil];
    
    // Change the size of page view controller
    self.pageViewController.view.frame = CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height - 100);
    
    [self addChildViewController:_pageViewController];
    [self.view addSubview:_pageViewController.view];
    [self.pageViewController didMoveToParentViewController:self];
    
    // round button corners - even though they won't be seen unless we set the button background color different
    // but - the newer UI design calls for no visible button boundaries
    _btnStartAgain.layer.cornerRadius = 10;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)startShow:(id)sender {
    RMSPageContentViewController *startingViewController = [self viewControllerAtIndex:0];
    NSArray *viewControllers = @[startingViewController];
    [self.pageViewController setViewControllers:viewControllers direction:UIPageViewControllerNavigationDirectionReverse animated:NO completion:nil];
}

#pragma mark - Page View Controller Data Source

- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerBeforeViewController:(UIViewController *)viewController
{
    NSUInteger index = ((RMSPageContentViewController*) viewController).pageIndex;
    
    NSLog(@"BeforeVC: index:%d", index);
    
    if ((index == 0) || (index == NSNotFound)) {
        return nil;
    }
    
    index--;
    
    return [self viewControllerAtIndex:index];
}

- (UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerAfterViewController:(UIViewController *)viewController
{
    NSUInteger index = ((RMSPageContentViewController*) viewController).pageIndex;
    
    NSLog(@"AfterVC: index:%d", index);
    
    if (index == NSNotFound) {
        return nil;
    }
    
    index++;
    if (index == [self.pageTitles count]) {
        return nil;
    }
    
    return [self viewControllerAtIndex:index];
}

- (RMSPageContentViewController *)viewControllerAtIndex:(NSUInteger)index
{
    if (([self.pageTitles count] == 0) || (index >= [self.pageTitles count])) {
        return nil;
    }
    
    // Create a new content view controller
    RMSPageContentViewController *pageContentViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"PageContentController"];

    // Set image, title and page index
    pageContentViewController.imageFile = self.pageImages[index];
    pageContentViewController.titleText = self.pageTitles[index];
    pageContentViewController.pageIndex = index;
    
    return pageContentViewController;
}

// Tell the OS how many pages we have
- (NSInteger)presentationCountForPageViewController:(UIPageViewController *)pageViewController
{
    return [self.pageTitles count];
}

// Tell the OS which page to start with
- (NSInteger)presentationIndexForPageViewController:(UIPageViewController *)pageViewController
{
    return 0;
}

@end
