//
//  NSArray+Extension.h
//
//  Created by TozyZuo.
//
//  http://TozyZuo.github.io

/**************************************************************************

 INTRODUCTION:

    This tool is used to get correct object from NSArray.

 BACKGROUND:
 
 The risky code:
    
    NSString *string = array[1][@"key"];
 
    Issues:1.array may NOT be a NSArray object
           2.array.count > 1 ???
           3.array[1] may NOT be a NSDictionary object
           4.array[1][@"key"] may NOT be a NSString object

    Conclusion:Any one of the issues could cause app crash.
 
    About issue4, @see NSDictionary+Extension.h.
 
 The safe code:

    NSString *string = nil;
    if ([array isKindOfClass:[NSArray class]] &&
        array.count > 1)
    {
        NSDictionary *dictionary = array[1];
        if ([dictionary isKindOfClass:[NSDictionary class]]) {
            id value = dictionary[@"key"];
            if ([value isKindOfClass:[NSString class]]) {
                string = value;
            }
        }
    }

    The Code is safe, but coding cost and reading cost will be raised.

 USAGE:
 
    NSString *string = array[1][@"key"];
                     ↓
    NSString *string = array.dictionaryAtIndex[1][@"key"];
 
    That's it! Just add ".dictionaryAtIndex" between "array" and "[1]".
 
    Use macro "EnableNSArrayExtensionAssert" to enable/disable the assert.
 
 ADVANTAGE:
 
    1.Do NOT care about wheather "array" is a NSArray.
      Return nil if "array" is NOT a NSArray.
    2.Do NOT care about wheather index is correct.
      Return nil if beyound bounds.
    3.Do NOT care about wheather "array[1]" is a NSDictionary.
      Return nil if "array[1]" is NOT a NSDictionary.
 
 CUSTOM CLASS:
 
    Use macro to make your custom class enable. The following is a demo that show
    you how it works.

**************************************************************************/



#import <Foundation/Foundation.h>


#define EnableNSArrayExtensionAssert


// Assert switch
#ifdef EnableNSArrayExtensionAssert
#define NSArrayExtensionAssert(...) NSAssert(0, __VA_ARGS__)
#else
#define NSArrayExtensionAssert(...) NSLog(__VA_ARGS__)
#endif


#define NSArrayExtensionDeclare(type, name)                             \
@interface NSArrayExtension##type##Getter : NSObject                    \
- (type *)objectAtIndexedSubscript:(NSUInteger)index;                   \
@end                                                                    \
@interface NSArray (Extension##type)                                    \
@property (readonly) NSArrayExtension##type##Getter *name##AtIndex;     \
- (type *)name##AtIndex:(NSUInteger)index;                              \
- (type *)name##AtIndex:(NSUInteger)index default:(type *)name;         \
@end

#define NSArrayExtensionSynthesize(type, name)                          \
@interface NSArrayExtension##type##Getter ()                            \
@property (nonatomic, weak) NSArray *array;                             \
@end                                                                    \
@implementation NSArrayExtension##type##Getter                          \
+ (instancetype)alloc                                                   \
{                                                                       \
    NSAssert(0, @"Should't call this by user!");                        \
    return nil;                                                         \
}                                                                       \
+ (instancetype)realAlloc                                               \
{                                                                       \
    return [super alloc];                                               \
}                                                                       \
+ (instancetype)getterWithArray:(NSArray *)array                        \
{                                                                       \
    return [[self realAlloc] initWithArray:array];                      \
}                                                                       \
- (instancetype)initWithArray:(NSArray *)array                          \
{                                                                       \
    if (array) {                                                        \
        self = [super init];                                            \
        self.array = array;                                             \
    }                                                                   \
    return self;                                                        \
}                                                                       \
- (type *)objectAtIndexedSubscript:(NSUInteger)index                    \
{                                                                       \
    return [self.array name##AtIndex:index];                            \
}                                                                       \
@end                                                                    \
@implementation NSArray (Extension##type)                               \
- (NSArrayExtension##type##Getter *)name##AtIndex                       \
{                                                                       \
    return [NSArrayExtension##type##Getter getterWithArray:self];       \
}                                                                       \
- (type *)name##AtIndex:(NSUInteger)index                               \
{                                                                       \
    return [self name##AtIndex:index default:nil];                      \
}                                                                       \
- (type *)name##AtIndex:(NSUInteger)index default:(type *)name          \
{                                                                       \
    if (index < self.count) {                                           \
        id object = self[index];                                        \
        if ([object isKindOfClass:[type class]]) {                      \
            return object;                                              \
        } else {                                                        \
            NSArrayExtensionAssert(@"%s type error! require %s but %@", __PRETTY_FUNCTION__, #type, [object class]);\
            return name;                                                \
        }                                                               \
    }                                                                   \
    NSArrayExtensionAssert(@"index %lu beyond bounds %@", index, self.count ? [NSString stringWithFormat:@"[0 .. %lu]", self.count - 1] : @"for empty array");\
    return name;                                                        \
}                                                                       \
@end                                                                    \
@implementation NSObject (NSArrayExtension##type)                       \
- (NSArrayExtension##type##Getter *)name##AtIndex                       \
{                                                                       \
    NSArrayExtensionAssert(@"-[%@ %@]: unrecognized selector sent to instance %p", self.class, NSStringFromSelector(_cmd), self);                              \
    return nil;                                                         \
}                                                                       \
- (type *)name##AtIndex:(NSUInteger)index                               \
{                                                                       \
    NSArrayExtensionAssert(@"-[%@ %@]: unrecognized selector sent to instance %p", self.class, NSStringFromSelector(_cmd), self);                              \
    return nil;                                                         \
}                                                                       \
- (type *)name##AtIndex:(NSUInteger)index default:(type *)name          \
{                                                                       \
    NSArrayExtensionAssert(@"-[%@ %@]: unrecognized selector sent to instance %p", self.class, NSStringFromSelector(_cmd), self);                              \
    return nil;                                                         \
}                                                                       \
@end


/**
    Demo

    NSArrayExtensionDeclare(NSString, string)

    The following are the source codes after macro expansion.
 */
@interface NSArrayExtensionNSStringGetter : NSObject
- (NSString *)objectAtIndexedSubscript:(NSUInteger)index;
@end
@interface NSArray (ExtensionNSString)
@property (readonly) NSArrayExtensionNSStringGetter *stringAtIndex;
- (NSString *)stringAtIndex:(NSUInteger)index;
- (NSString *)stringAtIndex:(NSUInteger)index default:(NSString *)string;
@end


//NSArrayExtensionDeclare(NSString, string)
NSArrayExtensionDeclare(NSNumber, number)
NSArrayExtensionDeclare(NSArray, array)
NSArrayExtensionDeclare(NSDictionary, dictionary)

