// Copyright 2015-present 650 Industries. All rights reserved.

#import <ABI45_0_0EXSensors/ABI45_0_0EXAccelerometer.h>
#import <ABI45_0_0ExpoModulesCore/ABI45_0_0EXAccelerometerInterface.h>

@implementation ABI45_0_0EXAccelerometer

ABI45_0_0EX_EXPORT_MODULE(ExponentAccelerometer);

- (const NSString *)updateEventName
{
  return @"accelerometerDidUpdate";
}

- (id)getSensorServiceFromModuleRegistry:(ABI45_0_0EXModuleRegistry *)moduleRegistry
{
  return [moduleRegistry getModuleImplementingProtocol:@protocol(ABI45_0_0EXAccelerometerInterface)];
}

- (void)setUpdateInterval:(double)updateInterval onSensorService:(id)sensorService
{
  [sensorService setAccelerometerUpdateInterval:updateInterval];
}

- (BOOL)isAvailable:(id)sensorService
{
  return [sensorService isAccelerometerAvailable];
}

- (void)subscribeToSensorService:(id)sensorService withHandler:(void (^)(NSDictionary *event))handlerBlock
{
  [sensorService sensorModuleDidSubscribeForAccelerometerUpdates:self withHandler:handlerBlock];
}

- (void)unsubscribeFromSensorService:(id)sensorService
{
  [sensorService sensorModuleDidUnsubscribeForAccelerometerUpdates:self];
}

@end
