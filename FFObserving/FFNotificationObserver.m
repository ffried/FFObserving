//
//  FFNotificationObserver.m
//
//  Created by Florian Friedrich on 02.04.14.
//  Copyright (c) 2014 Florian Friedrich. All rights reserved.
//

#import "FFNotificationObserver.h"
#import "NSOperationQueue+FFAdditions.h"

@interface FFNotificationObserver ()
@property (nonatomic, copy) NSString *note;
@property (nonatomic, weak) id object;
@property (nonatomic, strong) NSNotificationCenter *center;

@property (nonatomic, copy) FFNotificationObserverBlock block;
@property (nonatomic, weak) id target;
@property (nonatomic, assign) SEL selector;

- (void)receivedNotification:(NSNotification *)note;
@end

@implementation FFNotificationObserver

#pragma mark - Class methods
+ (instancetype)observerForNotification:(NSString *)note
                                 object:(id)object
                              withBlock:(FFNotificationObserverBlock)block
{
    return [[self alloc] initWithNotification:note object:object andBlock:block];
}

+ (instancetype)observerForNotification:(NSString *)note
                                 object:(id)object
                               inCenter:(NSNotificationCenter *)center
                                onQueue:(NSOperationQueue *)queue
                              withBlock:(FFNotificationObserverBlock)block
{
    return [[self alloc] initWithNotification:note
                                       object:object
                                     inCenter:center
                                      onQueue:queue
                                     andBlock:block];
}

+ (instancetype)observerForNotification:(NSString *)note
                                 object:(id)object
                             withTarget:(id)target
                            andSelector:(SEL)selector
{
    return [[self alloc] initWithNotification:note object:object target:target selector:selector];
}

+ (instancetype)observerForNotification:(NSString *)note
                                 object:(id)object
                               inCenter:(NSNotificationCenter *)center
                                onQueue:(NSOperationQueue *)queue
                             withTarget:(id)target
                            andSelector:(SEL)selector
{
    return [[self alloc] initWithNotification:note
                                       object:(id)object
                                     inCenter:center
                                      onQueue:queue
                                       target:target
                                     selector:selector];
}

#pragma mark - Initializer
- (instancetype)init { return [self initWithNotification:nil object:nil andBlock:nil]; }

- (instancetype)initWithNotification:(NSString *)note
                              object:(id)object
                            andBlock:(FFNotificationObserverBlock)block
{
    return [self initWithNotification:note object:object inCenter:nil onQueue:nil andBlock:block];
}

- (instancetype)initWithNotification:(NSString *)note
                              object:(id)object
                            inCenter:(NSNotificationCenter *)center
                             onQueue:(NSOperationQueue *)queue
                            andBlock:(FFNotificationObserverBlock)block
{
    self = [super init];
    if (self) {
        self.note = note;
        self.object = object;
        self.center = center ?: [NSNotificationCenter defaultCenter];
        self.queue = queue ?: [NSOperationQueue currentQueue];
        self.block = block;
        
        [self.center addObserver:self selector:@selector(receivedNotification:) name:self.note object:object];
    }
    return self;
}

- (instancetype)initWithNotification:(NSString *)note
                              object:(id)object
                              target:(id)target
                            selector:(SEL)selector
{
    return [self initWithNotification:note
                               object:object
                             inCenter:nil
                              onQueue:nil
                               target:target
                             selector:selector];
}

- (instancetype)initWithNotification:(NSString *)note
                              object:(id)object
                            inCenter:(NSNotificationCenter *)center
                             onQueue:(NSOperationQueue *)queue
                              target:(id)target
                            selector:(SEL)selector
{
    self = [self initWithNotification:note object:object inCenter:center onQueue:queue andBlock:nil];
    if (self) {
        self.target = target;
        self.selector = selector;
        __weak __typeof(self) weakself = self;
        self.block = ^(FFNotificationObserver *observer, NSNotification *note, NSDictionary *userInfo) {
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
                    // Otherwise hand the note to the target too
                    if (args == 3) {
                        [target performSelector:selector withObject:note];
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
    [self.center removeObserver:self name:self.note object:self.object];
}

#pragma mark - Properties
- (void)setQueue:(NSOperationQueue *)queue
{
    if (![_queue isEqual:queue]) {
        _queue = queue ?: [NSOperationQueue currentQueue];
    }
}

#pragma mark - Internals
- (void)receivedNotification:(NSNotification *)note
{
    if (self.block) {
        __weak __typeof(self) weakself = self;
        [self.queue addOperationWithBlock:^{
            __strong __typeof(weakself) strongself = weakself;
            if (!strongself.block) return;
            strongself.block(strongself, note, note.userInfo);
        } waitUntilFinished:![self.queue isCurrentQueue]];
    }
}

- (void)dealloc
{
    [self unregister];
}

@end
