//
//  FFNotificationObserver.h
//
//  Created by Florian Friedrich on 02.04.14.
//  Copyright (c) 2014 Florian Friedrich. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#import <Foundation/Foundation.h>
#import "NSDesignatedInitializer.h"

@class FFNotificationObserver;
/**
 *  The block being called when a notification is received.
 *  @param observer The FFNotificationObserver instance.
 *  @param note     The NSNoticiation which was sent.
 *  @param userInfo The userInfo NSDictionary of the NSNotification.
 */
typedef void(^FFNotificationObserverBlock)(FFNotificationObserver *observer,
                                           NSNotification *note,
                                           NSDictionary *userInfo);

/**
 *  Observes a NSNotification in a NSNotificationCenter.
 *  Just use it, don't care about registering and unregistering.
 */
@interface FFNotificationObserver : NSObject

#pragma mark - Properties
/**
 *  The name of the notification for which the observer is registered.
 */
@property (nonatomic, copy, readonly) NSString *note;
/**
 *  The object which sends the notifications. Nil if the observer listens to notifications from any object.
 */
@property (nonatomic, weak, readonly) id object;
/**
 *  The notification center at which the observer is registered.
 */
@property (nonatomic, strong, readonly) NSNotificationCenter *center;
/**
 *  The queue on which the block or the selector will be called.
 */
@property (nonatomic, strong) NSOperationQueue *queue;

#pragma mark - Class methods
/**
 *  Creates a new observer for a notification name.
 *  @param note  The name of the notification to observe.
 *  @param block The block to be called when a notification with the observed name is posted.
 *  @return A new instance of FFNotificationObserver.
 */
+ (instancetype)observerForNotification:(NSString *)note
                                 object:(id)object
                              withBlock:(FFNotificationObserverBlock)block;
/**
 *  Creates a new observer for a notification name in a specific center and on a specific queue.
 *  @param note   The name of the notification to observe.
 *  @param center The NSNotificationCenter to watch for notifications with the given name.
 *  @param queue  The NSOperationQueue on which the block will be called.
 *  @param block  The block to be called when a notification with the observed name is posted.
 *  @return A new instance of FFNotificationObserver.
 */
+ (instancetype)observerForNotification:(NSString *)note
                                 object:(id)object
                               inCenter:(NSNotificationCenter *)center
                                onQueue:(NSOperationQueue *)queue
                              withBlock:(FFNotificationObserverBlock)block;
/**
 *  Creates a new observer for a notification name.
 *  @param note     The name of the notification to observe.
 *  @param target   The target of the selector.
 *  @param selector The selector to be called when a notification with the observed name is posted.
 *  @return A new instance of FFNotificationObserver.
 */
+ (instancetype)observerForNotification:(NSString *)note
                                 object:(id)object
                             withTarget:(id)target
                            andSelector:(SEL)selector;
/**
 *  Creates a new observer for a notification name in a specific center and on a specific queue.
 *  @param note     The name of the notification to observe.
 *  @param center   The NSNotificationCenter to watch for notifications with the given name.
 *  @param queue    The NSOperationQueue on which the block will be called.
 *  @param target   The target of the selector.
 *  @param selector The selector to be called when a notification with the observed name is posted.
 *  @return A new instance of FFNotificationObserver.
 */
+ (instancetype)observerForNotification:(NSString *)note
                                 object:(id)object
                               inCenter:(NSNotificationCenter *)center
                                onQueue:(NSOperationQueue *)queue
                             withTarget:(id)target
                            andSelector:(SEL)selector;

#pragma mark - Initializer
/**
 *  Initializes an observer with a notification name.
 *  @param note  The name of the notification to observe.
 *  @param block The block to be called when a notification with the observed name is posted.
 *  @return A new instance of FFNotificationObserver.
 */
- (instancetype)initWithNotification:(NSString *)note
                              object:(id)object
                            andBlock:(FFNotificationObserverBlock)block;
/**
 *  Initializes an observer with a notification name in a specific center and on a specific queue.
 *  This is the designated initializer.
 *  @param note   The name of the notification to observe.
 *  @param center The NSNotificationCenter to watch for notifications with the given name.
 *  @param queue  The NSOperationQueue on which the block will be called.
 *  @param block  The block to be called when a notification with the observed name is posted.
 *  @return A new instance of FFNotificationObserver.
 */
- (instancetype)initWithNotification:(NSString *)note
                              object:(id)object
                            inCenter:(NSNotificationCenter *)center
                             onQueue:(NSOperationQueue *)queue
                            andBlock:(FFNotificationObserverBlock)block NS_DESIGNATED_INITIALIZER;

/**
 *  Initializes an observer with a notification name.
 *  @param note     The name of the notification to observe.
 *  @param target   The target of the selector.
 *  @param selector The selector to be called when a notification with the observed name is posted.
 *  @return A new instance of FFNotificationObserver.
 */
- (instancetype)initWithNotification:(NSString *)note
                              object:(id)object
                              target:(id)target
                            selector:(SEL)selector;
/**
 *  Initializes an observer with a notification name in a specific center and on a specific queue.
 *  @param note     The name of the notification to observe.
 *  @param center   The NSNotificationCenter to watch for notifications with the given name.
 *  @param queue    The NSOperationQueue on which the block will be called.
 *  @param target   The target of the selector.
 *  @param selector The selector to be called when a notification with the observed name is posted.
 *  @return A new instance of FFNotificationObserver.
 */
- (instancetype)initWithNotification:(NSString *)note
                              object:(id)object
                            inCenter:(NSNotificationCenter *)center
                             onQueue:(NSOperationQueue *)queue
                              target:(id)target
                            selector:(SEL)selector;

#pragma mark - Methods
/**
 *  Removes the observer from the NSNotificationCenter.
 *  This is called automatically on dealloc.
 */
- (void)unregister;

@end
