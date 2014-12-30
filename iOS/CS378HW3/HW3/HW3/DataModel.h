//
//  DataModel.h
//  HW3
//
//  Created by JesGalvan on 9/16/14.
//  Copyright (c) 2014 CS378HW3. All rights reserved.
//

#import <Foundation/Foundation.h>
/*a protocol named DataModelProtocol in the DataModel header file.*/
@protocol DataModelProtocol <NSObject>
/*required method (void)modifiedData*/
@required
/*The view controller will be the delegate for the DataModelProtocol.*/
-(void)modifedData:(NSString *)data;
@end

@interface DataModel : NSObject
{
    id <DataModelProtocol> _delegate;
}
/*public method signature*/
-(void)saveWithName:(NSString *)name AndCity:(NSString *)city;
/*Public property for a delegate of type DataModelProtocol.*/
@property (nonatomic,strong) id <DataModelProtocol>delegate;

@end
