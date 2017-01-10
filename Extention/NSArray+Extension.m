//
//  NSArray+Extension.m
//
//  Created by TozyZuo.
//

#import "NSArray+Extension.h"

@interface NSArrayExtensionNSStringGetter ()
@property (nonatomic, weak) NSArray *array;
@end

@implementation NSArrayExtensionNSStringGetter

+ (instancetype)alloc
{
    NSAssert(0, @"Should't call this by user!");
    return nil;
}

+ (instancetype)realAlloc
{
    return [super alloc];
}

+ (instancetype)getterWithArray:(NSArray *)array
{
    return [[self realAlloc] initWithArray:array];
}

- (instancetype)initWithArray:(NSArray *)array
{
    if (array) {
        self = [super init];
        self.array = array;
    }
    return self;
}

- (NSString *)objectAtIndexedSubscript:(NSUInteger)index
{
    return [self.array stringAtIndex:index];
}

@end

@implementation NSArray (ExtensionNSString)

- (NSArrayExtensionNSStringGetter *)stringAtIndex
{
    return [NSArrayExtensionNSStringGetter getterWithArray:self];
}

- (NSString *)stringAtIndex:(NSUInteger)index
{
    return [self stringAtIndex:index default:nil];
}

- (NSString *)stringAtIndex:(NSUInteger)index default:(NSString *)string
{
    if (index < self.count) {
        id object = self[index];
        if ([object isKindOfClass:[NSString class]]) {
            return object;
        } else {
            NSArrayExtensionAssert(@"%s type error! require NSString but %@", __PRETTY_FUNCTION__, [object class]);
            return string;
        }
    }
    NSArrayExtensionAssert(@"index %lu beyond bounds %@", index, self.count ? [NSString stringWithFormat:@"[0 .. %lu]", self.count - 1] : @"for empty array");
    return string;
}

@end

@implementation NSObject (NSArrayExtensionNSString)

- (NSArrayExtensionNSStringGetter *)stringAtIndex
{
    NSArrayExtensionAssert(@"-[%@ %@]: unrecognized selector sent to instance %p", self.class, NSStringFromSelector(_cmd), self);
    return nil;
}

- (NSString *)stringAtIndex:(NSUInteger)index
{
    NSArrayExtensionAssert(@"-[%@ %@]: unrecognized selector sent to instance %p", self.class, NSStringFromSelector(_cmd), self);
    return nil;
}

- (NSString *)stringAtIndex:(NSUInteger)index default:(NSString *)string
{
    NSArrayExtensionAssert(@"-[%@ %@]: unrecognized selector sent to instance %p", self.class, NSStringFromSelector(_cmd), self);
    return nil;
}

@end


NSArrayExtensionSynthesize(NSNumber, number)
NSArrayExtensionSynthesize(NSArray, array)
NSArrayExtensionSynthesize(NSDictionary, dictionary)
