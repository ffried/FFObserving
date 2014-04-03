//
//  FFObserver.m
//
//  Created by Florian Friedrich on 14.10.13.
//  Copyright (c) 2013 Florian Friedrich. All rights reserved.
//

#import "FFObserver.h"
#import "NSOperationQueue+FFAdditions.h"

#define FF_CONTEXT (__bridge void *)(self)
static NSKeyValueObservingOptions const FFObserverOptions = (NSKeyValueObservingOptionOld |
                                                             NSKeyValueObservingOptionNew);

@interface FFObserver ()
@property (nonatomic, weak) id target;
@property (nonatomic, assign) SEL selector;
@property (nonatomic, copy) FFObserverBlock block;

@property (nonatomic, weak) id observedObject;
@property (nonatomic, copy) NSString *keyPath;

@property (nonatomic) BOOL didUnregister;
@end


@implementation FFObserver

#pragma mark - Class Methods
+ (instancetype)observerWithObject:(id)object
                           keyPath:(NSString *)keyPath
                             block:(FFObserverBlock)block
                             queue:(NSOperationQueue *)queue
{
    return [[[self class] alloc] initWithObject:object
                                        keyPath:keyPath
                                          block:block
                                          queue:queue];
}

+ (instancetype)observerWithObject:(id)object
                           keyPath:(NSString *)keyPath
                            target:(id)target
                          selector:(SEL)selector
                             queue:(NSOperationQueue *)queue
{
    return [[[self class] alloc] initWithObject:object
                                        keyPath:keyPath
                                         target:target
                                       selector:selector
                                          queue:queue];
}

#pragma mark - Initializers
- (instancetype)initWithObject:(id)object
                       keyPath:(NSString *)keyPath
                         block:(FFObserverBlock)block
                         queue:(NSOperationQueue *)queue
{
    self = [super init];
    if (self) {
        self.observedObject = object;
        self.keyPath = keyPath;
        self.block = block;
        self.queue = queue ?: [NSOperationQueue currentQueue];
        [self.observedObject addObserver:self
                              forKeyPath:self.keyPath
                                 options:FFObserverOptions
                                 context:FF_CONTEXT];
    }
    return self;
}

- (instancetype)initWithObject:(id)object
                       keyPath:(NSString *)keyPath
                        target:(id)target
                      selector:(SEL)selector
                         queue:(NSOperationQueue *)queue
{
    self = [self initWithObject:object
                        keyPath:keyPath
                          block:nil
                          queue:queue];
    if (self) {
        // Define the missing vars
        self.target = target;
        self.selector = selector;
        
        // Set block
        __weak __typeof(self) weakself = self;
        self.block = ^(FFObserver *observer, id object, NSDictionary *changeDictionary) {
            __strong __typeof(weakself) strongself = weakself;
            id target = strongself.target;
            SEL selector = strongself.selector;
            // If target responds to selector
            if ([target respondsToSelector:selector]) {
                // Create NSMethodSignature from selector
                NSMethodSignature *signature = [target methodSignatureForSelector:selector];
                if (signature) { // If it really exists
                    NSUInteger args = signature.numberOfArguments; // Get number of arguments
                    //Disable warnings for the next few lines of code
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
                    // If there's no argument just perform the selector
                    if (args == 2) {
                        [target performSelector:selector];
                    }
                    // Otherwise hand the changeDictionary to the target too
                    if (args == 3) {
                        [target performSelector:selector withObject:changeDictionary];
                    }
                    // Re-enable warnings
#pragma clang diagnostic pop
                }
            }
        };
    }
    return self;
}

#pragma mark - Methods
- (void)unregister
{
    if (!self.didUnregister) {
        [self.observedObject removeObserver:self forKeyPath:self.keyPath context:FF_CONTEXT];
        self.block = nil;
        self.selector = nil;
        self.didUnregister = YES;
    }
}

#pragma mark - Properties
- (void)setQueue:(NSOperationQueue *)queue
{
    if (![_queue isEqual:queue]) {
        _queue = queue ?: [NSOperationQueue currentQueue];
    }
}

#pragma mark - Internals
- (void)observeValueForKeyPath:(NSString *)keyPath
                      ofObject:(id)object
                        change:(NSDictionary *)change
                       context:(void *)context
{
    BOOL contextMatches = (context == FF_CONTEXT);
    if (contextMatches) {
        BOOL objectMatches = (object == self.observedObject);
        if (self.block) {
            __weak __typeof(self) weakself = self;
            [self.queue addOperationWithBlock:^{
                __strong __typeof(weakself) strongself = weakself;
                strongself.block(strongself, ((objectMatches) ? strongself.observedObject : object), change);
            } waitUntilFinished:![self.queue isCurrentQueue]];
        }
    } else {
        [super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
    }
}

- (void)dealloc
{
    [self unregister];
}

@end
