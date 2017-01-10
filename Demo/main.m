//
//  main.m
//  Demo
//
//  Created by TozyZuo on 2017/1/10.
//  Copyright © 2017年 TozyZuo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NSArray+Extension.h"
#import "NSDictionary+Extension.h"


NSArrayExtensionDeclare(NSData, data)
NSArrayExtensionSynthesize(NSData, data)

NSDictionaryExtensionDeclare(NSData, data)
NSDictionaryExtensionSynthesize(NSData, data)

@interface MyObject : NSObject
@end
@implementation MyObject
@end

NSArrayExtensionDeclare(MyObject, myObject)
NSArrayExtensionSynthesize(MyObject, myObject)

NSDictionaryExtensionDeclare(MyObject, myObject)
NSDictionaryExtensionSynthesize(MyObject, myObject)


int main(int argc, const char * argv[]) {

    @autoreleasepool {
        NSArray *a1 = @[@1, @2, @"3.14", @[@11, @22, @"abc"], @{@"1": @1, @2: @"2"}];

        NSString *str = a1.dictionaryAtIndex[1].stringForKey[@"key"];
        str = [a1 stringAtIndex:1];
        str = [a1 stringAtIndex:1 default:@""];

        NSArray *a2 = a1.arrayAtIndex[0];
        NSArray *a3 = a1.arrayAtIndex[10];

        NSString *s1 = a1.arrayAtIndex[3].stringAtIndex[2];
        NSNumber *n1 = a1.arrayAtIndex[3].numberAtIndex[2];
        NSNumber *n2 = a1.arrayAtIndex[3].numberAtIndex[1];

        NSString *s2 = a1.stringAtIndex[1];
        NSString *s3 = a1.stringAtIndex[2];

        NSNumber *n3 = a1.numberAtIndex[0];
        NSNumber *n4 = a1.numberAtIndex[2];

        NSDictionary *d1 = a1.dictionaryAtIndex[0];
        NSDictionary *d2 = a1.dictionaryAtIndex[a1.count - 1];

        NSString *s4 = a1.dictionaryAtIndex[4].stringForKey[@"1"];
        NSString *s5 = a1.dictionaryAtIndex[4].stringForKey[@1];

        NSNumber *n5 = a1.dictionaryAtIndex[4].numberForKey[@"2"];
        NSNumber *n6 = a1.dictionaryAtIndex[4].numberForKey[@2];

        NSData *data = a1.dataAtIndex[0];
        data = [a1 dataAtIndex:0];
        data = [a1 dataAtIndex:0 default:[NSData data]];

        NSDictionary *dic = a1.dictionaryAtIndex[0];
//        dic = (NSDictionary *)@[];

        data = [dic dataForKey:@""];
        data = dic.dataForKey[@""];
        data = a1.dataAtIndex[1];
        data = [a1.dictionaryAtIndex[0] dataForKey:@""];
        data = [a1.dictionaryAtIndex[0] dataForKey:@"" default:[NSData data]];

        MyObject *myObject = a1.myObjectAtIndex[1];
        myObject = a1.dictionaryAtIndex[8].arrayForKey[@""].myObjectAtIndex[8];

        myObject = @[[[MyObject alloc] init]].myObjectAtIndex[0];

        NSArray<MyObject *> *a4 = @[];
        NSString *s6 = a4.stringAtIndex[0];
        myObject = a1.myObjectAtIndex[1];
        s6 = a4.firstObject;
//        s6 = a4[0]; // crash

        NSDictionary<NSString *, NSArray<MyObject *> *> *d3 = @{@"key": a4};
        d3 = dic;
        myObject = d3[@"key"].firstObject;
//        myObject = d3[@"key"][0]; // crash
        myObject = d3[@""];
        a4 = d3[@1];
        myObject = d3.myObjectForKey[@""];
//        s6 = d3.arrayForKey[@""][0]; // crash, no warning
        s6 = d3.arrayForKey[@1].firstObject; // no warning
        
    }
    
    return 0;
}
