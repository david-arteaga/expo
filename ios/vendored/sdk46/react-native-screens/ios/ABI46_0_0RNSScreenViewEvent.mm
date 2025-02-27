#import "ABI46_0_0RNSScreenViewEvent.h"
#import <ABI46_0_0React/ABI46_0_0RCTAssert.h>

@implementation ABI46_0_0RNSScreenViewEvent {
  double _progress;
  int _closing;
  int _goingForward;
}

@synthesize viewTag = _viewTag;
@synthesize eventName = _eventName;

- (instancetype)initWithEventName:(NSString *)eventName
                         ABI46_0_0ReactTag:(NSNumber *)ABI46_0_0ReactTag
                         progress:(double)progress
                          closing:(int)closing
                     goingForward:(int)goingForward
{
  ABI46_0_0RCTAssertParam(ABI46_0_0ReactTag);

  if ((self = [super init])) {
    _eventName = [eventName copy];
    _viewTag = ABI46_0_0ReactTag;
    _progress = progress;
    _closing = closing;
    _goingForward = goingForward;
  }
  return self;
}

ABI46_0_0RCT_NOT_IMPLEMENTED(-(instancetype)init)

- (NSDictionary *)body
{
  NSDictionary *body = @{
    @"progress" : @(_progress),
    @"closing" : @(_closing ? 1 : 0),
    @"goingForward" : @(_goingForward ? 1 : 0),
  };

  return body;
}

- (BOOL)canCoalesce
{
  return NO;
}

+ (NSString *)moduleDotMethod
{
  return @"ABI46_0_0RCTEventEmitter.receiveEvent";
}

- (NSArray *)arguments
{
  return @[ self.viewTag, ABI46_0_0RCTNormalizeInputEventName(self.eventName), [self body] ];
}

@end
