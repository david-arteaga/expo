#import <Foundation/Foundation.h>

#import "ABI45_0_0RNTouchEventType.h"

#define MAX_POINTERS_COUNT 12

@class ABI45_0_0RNGestureHandler;

@interface ABI45_0_0RNGestureHandlerPointerTracker : NSObject

@property (nonatomic) ABI45_0_0RNTouchEventType eventType;
@property (nonatomic) NSArray<NSDictionary *> *changedPointersData;
@property (nonatomic) NSArray<NSDictionary *> *allPointersData;
@property (nonatomic) int trackedPointersCount;

- (id)initWithGestureHandler:(ABI45_0_0RNGestureHandler*)gestureHandler;

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event;
- (void)reset;
- (void)cancelPointers;

@end
