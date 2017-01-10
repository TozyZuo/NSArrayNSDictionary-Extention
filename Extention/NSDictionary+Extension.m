//
//  NSDictionary+Extension.m
//
//  Created by TozyZuo.
//

#import "NSDictionary+Extension.h"


@interface NSDictionaryExtensionNSStringGetter ()
@property (nonatomic, weak) NSDictionary *dictionary;
@end

@implementation NSDictionaryExtensionNSStringGetter

+ (instancetype)alloc
{
    NSAssert(0, @"Should't call this by user!");
    return nil;
}

+ (instancetype)realAlloc
{
    return [super alloc];
}

+ (instancetype)getterWithDictionary:(NSDictionary *)dictionary
{
    return [[self realAlloc] initWithDictionary:dictionary];
}

- (instancetype)initWithDictionary:(NSDictionary *)dictionary
{
    if (dictionary) {
        self = [super init];
        self.dictionary = dictionary;
    }
    return self;
}

- (NSString *)objectForKeyedSubscript:(id)key
{
    return [self.dictionary stringForKey:key];
}

@end

@implementation NSDictionary (ExtensionNSString)

- (NSDictionaryExtensionNSStringGetter *)stringForKey
{
    return [NSDictionaryExtensionNSStringGetter getterWithDictionary:self];
}

- (NSString *)stringForKey:(id)aKey
{
    return [self stringForKey:aKey default:nil];
}

- (NSString *)stringForKey:(id)aKey default:(NSString *)name
{
    id object = self[aKey];
    if (object) {
        if ([object isKindOfClass:[NSString class]]) {
            return object;
        } else {
            NSDictionaryExtensionAssert(@"%s type error! require NSString but %@", __PRETTY_FUNCTION__, [object class]);
        }
    }
    return name;
}

@end

@implementation NSObject (NSDictionaryExtensionNSString)

- (NSDictionaryExtensionNSStringGetter *)stringForKey
{
    NSDictionaryExtensionAssert(@"-[%@ %@]: unrecognized selector sent to instance %p", self.class, NSStringFromSelector(_cmd), self);
    return nil;
}

- (NSString *)stringForKey:(id)aKey
{
    NSDictionaryExtensionAssert(@"-[%@ %@]: unrecognized selector sent to instance %p", self.class, NSStringFromSelector(_cmd), self);
    return nil;
}

- (NSString *)stringForKey:(id)aKey default:(NSString *)name
{
    NSDictionaryExtensionAssert(@"-[%@ %@]: unrecognized selector sent to instance %p", self.class, NSStringFromSelector(_cmd), self);
    return nil;
}

@end



NSDictionaryExtensionSynthesize(NSNumber, number)
NSDictionaryExtensionSynthesize(NSArray, array)
NSDictionaryExtensionSynthesize(NSDictionary, dictionary)
