//
//  FFObserver.h
//
//  Created by Florian Friedrich on 14.10.13.
//  Copyright (c) 2013 Florian Friedrich. All rights reserved.
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

@class FFObserver;
/**
 *  The block being is called upon changes.
 *  @param observer         The FFObserver object.
 *  @param object           The observed object.
 *  @param changeDictionary The dictionary containing the changes.
 */
typedef void (^FFObserverBlock)(FFObserver *observer, id object, NSDictionary *changeDictionary);

/**
 *  Key-Value observes an object.
 *  Auto-removes itself from the object.
 *  Is thread-safe.
 */
@interface FFObserver : NSObject

#pragma mark - Properties
/**
 *  The observed object.
 */
@property (nonatomic, weak, readonly) id observedObject;
/**
 *  The observed keypath.
 */
@property (nonatomic, copy, readonly) NSString *keyPath;
/**
 *  The queue on which the block or selector will be called.
 */
@property (nonatomic, strong) NSOperationQueue *queue;

#pragma mark - Class Methods
/**
 *  Creates a new observer for an object and a keypath.
 *  @param object  The object to observe.
 *  @param keyPath The keypath of the object to observe.
 *  @param block   The block to be called on changes.
 *  @param queue   The queue on which the block gets called. Uses the current queue if set to nil.
 *  @return A new instance of FFObserver.
 */
+ (instancetype)observerWithObject:(id)object
                           keyPath:(NSString *)keyPath
                             block:(FFObserverBlock)block
                             queue:(NSOperationQueue *)queue;
/**
 *  Creates a new observer for an object and a keypath.
 *  @param object   The object to observe.
 *  @param keyPath  The keypath of the object to observe.
 *  @param target   The target to be notified about changes.
 *  @param selector The selecter to call on the target.
 *  @param queue    The queue on which the target gets notified. Uses the current queue if set to nil.
 *  @return A new instance of FFObserver.
 */
+ (instancetype)observerWithObject:(id)object
                           keyPath:(NSString *)keyPath
                            target:(id)target
                          selector:(SEL)selector
                             queue:(NSOperationQueue *)queue;

#pragma mark - Initializers
/**
 *  Initializes an observer with an object and a keypath.
 *  This is the designated initializer.
 *  @param object  The object to observe.
 *  @param keyPath The keypath of the object to observe.
 *  @param block   The block to be called on changes.
 *  @param queue   The queue on which the block gets called. Uses the current queue if set to nil.
 *  @return A new instance of FFObserver.
 */
- (instancetype)initWithObject:(id)object
                       keyPath:(NSString *)keyPath
                         block:(FFObserverBlock)block
                         queue:(NSOperationQueue *)queue NS_DESIGNATED_INITIALIZER;
/**
 *  Initializes an observer with an object and a keypath.
 *  @param object   The object to observe.
 *  @param keyPath  The keypath of the object to observe.
 *  @param target   The target to be notified about changes.
 *  @param selector The selecter to call on the target.
 *  @param queue    The queue on which the target gets notified. Uses the current queue if set to nil.
 *  @return A new instance of FFObserver.
 */
- (instancetype)initWithObject:(id)object
                       keyPath:(NSString *)keyPath
                        target:(id)target
                      selector:(SEL)selector
                         queue:(NSOperationQueue *)queue;

#pragma mark - Methods
/**
 *  Unregisters the observer from the observing object.
 *  This is called automatically on dealloc.
 */
- (void)unregister;

@end
