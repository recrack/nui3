#ifndef __nglNSApplication_h__
#define __nglNSApplication_h__

#include "ngl.h"
#import <Cocoa/Cocoa.h>

@class nglUIWindow;

@interface nglNSApplication : NSApplication
{
}
- (void) dealloc;
- (BOOL) openURL: (NSURL*) pUrl;
- (void) sendEvent: (NSEvent*) pEvent;

- (void) applicationDidFinishLaunching:       (NSApplication*) pUIApp;
- (BOOL) application:(NSApplication *)pNSApplication didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;
- (void) applicationDidBecomeActive:          (NSApplication*) pUIApp;
- (void) applicationWillResignActive:         (NSApplication*) pUIApp;
- (void) applicationDidReceiveMemoryWarning:  (NSApplication*) pUIApp;
- (void) applicationSignificantTimeChange:    (NSApplication*) pUIApp;
- (void) applicationWillTerminate:            (NSApplication*) pUIApp;

@end//nglNSApplication

//@interface nglNSApplicationDelegate : NSObject
//{
//}
//- (void) dealloc;


@end//nglNSApplicationDelegate


#endif//__nglNSApplication_h__