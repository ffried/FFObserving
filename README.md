#FFObserving

KVO and NSNotificationCenter observing made easy.

##HOW TO
There isn't much to say about how to use it. `FFObserver` and `FFNotificationObserver` both have convenience initalizers and class methods for easily creating new instances. Their header documentation and arguments are mostly self-explaining.

In most cases you don't need to call `- (void)unregister;` yourself. The observer unregisters itself on dealloc.

The `@property (nonatomic, strong) NSOperationQueue *queue;` can be changed to another queue. If you set nil as queue the `currentQueue` will be taken.
The call on the queue is blocking the queue on which the notification was sent / change was detected unless it's the same as the `queue` property.

##LICENSE
FFObserving is licensed under MIT. See [LICENSE file](https://github.com/ffried/FFObserving/blob/master/LICENSE) for more information.

