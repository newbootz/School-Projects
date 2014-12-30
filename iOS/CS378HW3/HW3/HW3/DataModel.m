//
//  DataModel.m
//  HW3
//
//  Created by JesGalvan on 9/16/14.
//  Copyright (c) 2014 CS378HW3. All rights reserved.
//

#import "DataModel.h"

@implementation DataModel

-(void)saveWithName:(NSString *)name AndCity:(NSString *)city
{
    /*This method should call the delegate modifiedData method, passing in a string formatted with the passed in name and city, to be <name> - <city>.*/
    NSLog(@"DataModel.m saveWithName");
    NSLog(@" %@ - %@ ",name, city);
    
    
    [self.delegate modifedData:[NSString stringWithFormat:@"%@ - %@",name, city]];
    NSLog(@"Exiting saveWithName");
}

@end
