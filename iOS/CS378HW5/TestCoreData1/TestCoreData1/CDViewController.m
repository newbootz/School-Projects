//
//  CDViewController.m
//  TestCoreData1
//
//  Created by Robert Seitsinger on 9/30/14.
//  Copyright (c) 2014 Infinity Software. All rights reserved.
//

#import "CDViewController.h"
#import "CDAppDelegate.h"

@interface CDViewController ()
@property (weak, nonatomic) IBOutlet UITableView *tableView;
@property (nonatomic, strong) NSMutableArray *nameList;
@property (nonatomic, strong) NSMutableArray *phoneList;

@end

@implementation CDViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    [self loadModelData];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)loadModelData
{
    self.nameList = [[NSMutableArray alloc] init];
    self.phoneList = [[NSMutableArray alloc] init];
    
    CDAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
    NSManagedObjectContext *context = appDelegate.managedObjectContext;
    NSEntityDescription *entityDescription = [NSEntityDescription entityForName:@"Contact" inManagedObjectContext:context];
    NSFetchRequest *request = [[NSFetchRequest alloc] init];
    [request setEntity:entityDescription];
    
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"(name = %@)", @"Infinity Software"];
    [request setPredicate:predicate];
    
    // Fetch (read) the data
    NSError *error;
    NSArray *objects = [context executeFetchRequest:request error:&error];
    
    if ([objects count] == 0) {
        NSLog(@"No Matches");
    } else {
        NSManagedObject *item = nil;
        
        for (int i = 0; i < [objects count]; i++) {
            item = objects[i];
            [self.nameList addObject:[item valueForKey:@"name"]];
            [self.phoneList addObject:[item valueForKey:@"phone"]];
        }
    }
    
}

- (IBAction)addItem:(UIBarButtonItem *)sender {
    CDAppDelegate *appDelegate = [[UIApplication sharedApplication] delegate];
    NSManagedObjectContext *context = appDelegate.managedObjectContext;
    
    NSManagedObject *newContact = [NSEntityDescription insertNewObjectForEntityForName:@"Contact" inManagedObjectContext:context];
    [newContact setValue:@"Infinity Software" forKey:@"name"];
    [newContact setValue:@"512-123-4567" forKey:@"phone"];
    
    // Save changes to the persistent store
    NSError *error;
    [context save:&error];
    
    [self.nameList addObject:@"Infinity Software"];
    [self.phoneList addObject:@"512-123-4567"];
    
    // Cause table reload - which ends up calling the cellFor... method to load the table cells
    [self.tableView reloadData];
}

// UiTableViewController data source and delegate methods

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return [self.nameList count];
}

 - (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
 {
     UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cellid" forIndexPath:indexPath];
     
     // Configure the cell...
     cell.textLabel.text = [self.nameList objectAtIndex:indexPath.row];
     cell.detailTextLabel.text = [self.phoneList objectAtIndex:indexPath.row];
     
     return cell;
 }

@end
