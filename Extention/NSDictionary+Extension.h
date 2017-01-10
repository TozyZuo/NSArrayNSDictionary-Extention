//
//  NSDictionary+Extension.h
//
//  Created by TozyZuo.
//
//  http://TozyZuo.github.io

/**************************************************************************

 INTRODUCTION:
 
    This tool is used to get correct object from NSDictionary.

 BACKGROUND:

 The risky code:

    NSString *string = dictionary[@"key"][0];

    Issues:1.dictionary may NOT be a NSDictionary object
           2.dictionary[@"key"] may NOT be a NSArray object
           3.[dictionary[@"key"] count] > 0 ???
           4.dictionary[@"key"][0] may NOT be a NSString object

    Conclusion:Any one of the issues could cause app crash.

    About issue3, issue4, @see NSArray+Extension.h.

 The safe code:

    NSString *string = nil;
    if ([dictionary isKindOfClass:[NSDictionary class]]) {
        NSArray *array = dictionary[@"key"];
        if ([array isKindOfClass:[NSArray class]] &&
            array.count)
        {
            id object = array[0];
            if ([object isKindOfClass:[NSString class]]) {
                string = object;
            }
        }
    }

 The Code is safe, but coding cost and reading cost will be raised.

 USAGE:

    NSString *string = dictionary[@"key"][0];
                     ↓
    NSString *string = dictionary.arrayForKey[@"key"].firstObject;

    That's it! Just add ".arrayForKey" between "dictionary" and "[@"key"]".

    Use macro "EnableNSDictionaryExtensionAssert" to enable/disable the assert.

 ADVANTAGE:

    1.Do NOT care about wheather "dictionary" is a NSDictionary.
    Return nil if "dictionary" is NOT a NSDictionary.
    2.Do NOT care about wheather "dictionary[@"key"]" is a NSArray.
    Return nil if "dictionary[@"key"]" is NOT a NSArray.

 CUSTOM CLASS:

    Use macro to make your custom class enable. The following is a demo that show
    you how it works.

 ***************************************************************************/



#import <Foundation/Foundation.h>


#define EnableNSDictionaryExtensionAssert


// Assert switch
#ifdef EnableNSDictionaryExtensionAssert
#define NSDictionaryExtensionAssert(...) NSAssert(0, __VA_ARGS__)
#else
#define NSDictionaryExtensionAssert(...) NSLog(__VA_ARGS__)
#endif


// NSDictionaryExtensionDeclare
#define NSDictionaryExtensionDeclare(type, name)                                \
@interface NSDictionaryExtension##type##Getter<__covariant KeyType> : NSObject  \
- (type *)objectForKeyedSubscript:(KeyType)key;                                 \
@end                                                                            \
@interface NSDictionary<__covariant KeyType, __covariant ObjectType> (Extension##type)\
@property (readonly) NSDictionaryExtension##type##Getter<KeyType> *name##ForKey;\
- (type *)name##ForKey:(KeyType)aKey;                                           \
- (type *)name##ForKey:(KeyType)aKey default:(type *)name;                      \
@end


// NSDictionaryExtensionSynthesize
#define NSDictionaryExtensionSynthesize(type, name)                             \
@interface NSDictionaryExtension##type##Getter ()                               \
@property (nonatomic, weak) NSDictionary *dictionary;                           \
@end                                                                            \
@implementation NSDictionaryExtension##type##Getter                             \
+ (instancetype)alloc                                                           \
{                                                                               \
    NSAssert(0, @"Should't call this by user!");                                \
    return nil;                                                                 \
}                                                                               \
+ (instancetype)realAlloc                                                       \
{                                                                               \
    return [super alloc];                                                       \
}                                                                               \
+ (instancetype)getterWithDictionary:(NSDictionary *)dictionary                 \
{                                                                               \
    return [[self realAlloc] initWithDictionary:dictionary];                    \
}                                                                               \
- (instancetype)initWithDictionary:(NSDictionary *)dictionary                   \
{                                                                               \
    if (dictionary) {                                                           \
        self = [super init];                                                    \
        self.dictionary = dictionary;                                           \
    }                                                                           \
    return self;                                                                \
}                                                                               \
- (type *)objectForKeyedSubscript:(id)key                                       \
{                                                                               \
    return [self.dictionary name##ForKey:key];                                  \
}                                                                               \
@end                                                                            \
@implementation NSDictionary (Extension##type)                                  \
- (NSDictionaryExtension##type##Getter *)name##ForKey                           \
{                                                                               \
    return [NSDictionaryExtension##type##Getter getterWithDictionary:self];     \
}                                                                               \
- (type *)name##ForKey:(id)aKey                                                 \
{                                                                               \
    return [self name##ForKey:aKey default:nil];                                \
}                                                                               \
- (type *)name##ForKey:(id)aKey default:(type *)name                            \
{                                                                               \
    id object = self[aKey];                                                     \
    if (object) {                                                               \
        if ([object isKindOfClass:[type class]]) {                              \
            return object;                                                      \
        } else {                                                                \
            NSDictionaryExtensionAssert(@"%s type error! require %s but %@", __PRETTY_FUNCTION__, #type, [object class]);\
        }                                                                       \
    }                                                                           \
    return name;                                                                \
}                                                                               \
@end                                                                            \
@implementation NSObject (NSDictionaryExtension##type)                          \
- (NSDictionaryExtension##type##Getter *)name##ForKey                           \
{                                                                               \
    NSDictionaryExtensionAssert(@"-[%@ %@]: unrecognized selector sent to instance %p", self.class, NSStringFromSelector(_cmd), self);                                    \
    return nil;                                                                 \
}                                                                               \
- (type *)name##ForKey:(id)aKey                                                 \
{                                                                               \
    NSDictionaryExtensionAssert(@"-[%@ %@]: unrecognized selector sent to instance %p", self.class, NSStringFromSelector(_cmd), self);                                    \
    return nil;                                                                 \
}                                                                               \
- (type *)name##ForKey:(id)aKey default:(type *)name                            \
{                                                                               \
    NSDictionaryExtensionAssert(@"-[%@ %@]: unrecognized selector sent to instance %p", self.class, NSStringFromSelector(_cmd), self);                                    \
    return nil;                                                                 \
}                                                                               \
@end


/**
    Demo

    NSDictionaryExtensionDeclare(NSString, string)

    The following are the source codes after macro expansion.
 */
@interface NSDictionaryExtensionNSStringGetter<__covariant KeyType> : NSObject
- (NSString *)objectForKeyedSubscript:(KeyType)key;
@end
@interface NSDictionary<__covariant KeyType, __covariant ObjectType> (ExtensionNSString)
@property (readonly) NSDictionaryExtensionNSStringGetter<KeyType> *stringForKey;
- (NSString *)stringForKey:(KeyType)aKey;
- (NSString *)stringForKey:(KeyType)aKey default:(NSString *)string;
@end


//NSDictionaryExtensionDeclare(NSString, string)
NSDictionaryExtensionDeclare(NSNumber, number)
NSDictionaryExtensionDeclare(NSArray, array)
NSDictionaryExtensionDeclare(NSDictionary, dictionary)
