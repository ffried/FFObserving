//
//  NSOperationQueue+FFAdditions.h
//
//  Created by Florian Friedrich on 22.03.14.
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

/**
 *  Adds some useful methods to NSOperationQueue
 *  @see NSOperationQueue
 */
@interface NSOperationQueue (FFAdditions)

/**
 *  Compares the current queue with the main queue.
 *  @return YES if the current queue is the main queue, NO otherwise.
 */
+ (BOOL)isCurrentQueueMainQueue;

/**
 *  Checks if the queue is the main queue.
 *  @return YES if the queue is the main queue, No otherwise.
 */
- (BOOL)isMainQueue;
/**
 *  Checks if the queue is the current queue.
 *  @return YES if the queue is the current queue, NO otherwise.
 */
- (BOOL)isCurrentQueue;

/**
 *  Creates an operation with a block, sets its completion block and adds it to the queue.
 *  @param block      The block of the operation.
 *  @param completion The completion of the operation.
 *  @see NSBlockOperation
 */
- (void)addOperationWithBlock:(void (^)(void))block completion:(void (^)(void))completion;
/**
 *  Creates an operation with a block adds it to the queue and waits until it is finished.
 *  @param block The block of the operation
 *  @param wait  YES if it should wait, NO otherwise.
 *  @see NSBlockOperation
 */
- (void)addOperationWithBlock:(void (^)(void))block waitUntilFinished:(BOOL)wait;

@end
