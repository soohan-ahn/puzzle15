//
//  puzzle15AppController.h
//  puzzle15
//
//  Created by Soo Han Ahn on 2014. 5. 30..
//  Copyright __MyCompanyName__ 2014년. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

@end

