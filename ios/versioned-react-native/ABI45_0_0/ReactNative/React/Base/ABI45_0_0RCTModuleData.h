/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

#import <ABI45_0_0React/ABI45_0_0RCTInvalidating.h>
#import "ABI45_0_0RCTDefines.h"

@protocol ABI45_0_0RCTBridgeMethod;
@protocol ABI45_0_0RCTBridgeModule;
@class ABI45_0_0RCTBridge;
@class ABI45_0_0RCTModuleRegistry;
@class ABI45_0_0RCTViewRegistry;
@class ABI45_0_0RCTBundleManager;
@class ABI45_0_0RCTCallableJSModules;

typedef id<ABI45_0_0RCTBridgeModule> (^ABI45_0_0RCTBridgeModuleProvider)(void);

@interface ABI45_0_0RCTModuleData : NSObject <ABI45_0_0RCTInvalidating>

- (instancetype)initWithModuleClass:(Class)moduleClass
                             bridge:(ABI45_0_0RCTBridge *)bridge
                     moduleRegistry:(ABI45_0_0RCTModuleRegistry *)moduleRegistry
            viewRegistry_DEPRECATED:(ABI45_0_0RCTViewRegistry *)viewRegistry_DEPRECATED
                      bundleManager:(ABI45_0_0RCTBundleManager *)bundleManager
                  callableJSModules:(ABI45_0_0RCTCallableJSModules *)callableJSModules;

- (instancetype)initWithModuleClass:(Class)moduleClass
                     moduleProvider:(ABI45_0_0RCTBridgeModuleProvider)moduleProvider
                             bridge:(ABI45_0_0RCTBridge *)bridge
                     moduleRegistry:(ABI45_0_0RCTModuleRegistry *)moduleRegistry
            viewRegistry_DEPRECATED:(ABI45_0_0RCTViewRegistry *)viewRegistry_DEPRECATED
                      bundleManager:(ABI45_0_0RCTBundleManager *)bundleManager
                  callableJSModules:(ABI45_0_0RCTCallableJSModules *)callableJSModules NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithModuleInstance:(id<ABI45_0_0RCTBridgeModule>)instance
                                bridge:(ABI45_0_0RCTBridge *)bridge
                        moduleRegistry:(ABI45_0_0RCTModuleRegistry *)moduleRegistry
               viewRegistry_DEPRECATED:(ABI45_0_0RCTViewRegistry *)viewRegistry_DEPRECATED
                         bundleManager:(ABI45_0_0RCTBundleManager *)bundleManager
                     callableJSModules:(ABI45_0_0RCTCallableJSModules *)callableJSModules NS_DESIGNATED_INITIALIZER;

/**
 * Calls `constantsToExport` on the module and stores the result. Note that
 * this will init the module if it has not already been created. This method
 * can be called on any thread, but may block the main thread briefly if the
 * module implements `constantsToExport`.
 */
- (void)gatherConstants;

@property (nonatomic, strong, readonly) Class moduleClass;
@property (nonatomic, copy, readonly) NSString *name;

/**
 * Returns the module methods. Note that this will gather the methods the first
 * time it is called and then memoize the results.
 */
@property (nonatomic, copy, readonly) NSArray<id<ABI45_0_0RCTBridgeMethod>> *methods;

/**
 * Returns a map of the module methods. Note that this will gather the methods the first
 * time it is called and then memoize the results.
 */
@property (nonatomic, copy, readonly) NSDictionary<NSString *, id<ABI45_0_0RCTBridgeMethod>> *methodsByName;

/**
 * Returns the module's constants, if it exports any
 */
@property (nonatomic, copy, readonly) NSDictionary<NSString *, id> *exportedConstants;

/**
 * Returns YES if module instance has already been initialized; NO otherwise.
 */
@property (nonatomic, assign, readonly) BOOL hasInstance;

/**
 * Returns YES if module instance must be created on the main thread.
 */
@property (nonatomic, assign) BOOL requiresMainQueueSetup;

/**
 * Returns YES if module has constants to export.
 */
@property (nonatomic, assign, readonly) BOOL hasConstantsToExport;

/**
 * Returns the current module instance. Note that this will init the instance
 * if it has not already been created. To check if the module instance exists
 * without causing it to be created, use `hasInstance` instead.
 */
@property (nonatomic, strong, readwrite) id<ABI45_0_0RCTBridgeModule> instance;

/**
 * Returns the module method dispatch queue. Note that this will init both the
 * queue and the module itself if they have not already been created.
 */
@property (nonatomic, strong, readonly) dispatch_queue_t methodQueue;

/**
 * Whether the receiver has a valid `instance` which implements -batchDidComplete.
 */
@property (nonatomic, assign, readonly) BOOL implementsBatchDidComplete;

/**
 * Whether the receiver has a valid `instance` which implements
 * -partialBatchDidFlush.
 */
@property (nonatomic, assign, readonly) BOOL implementsPartialBatchDidFlush;

@end

ABI45_0_0RCT_EXTERN void ABI45_0_0RCTSetIsMainQueueExecutionOfConstantsToExportDisabled(BOOL val);
ABI45_0_0RCT_EXTERN BOOL ABI45_0_0RCTIsMainQueueExecutionOfConstantsToExportDisabled(void);
