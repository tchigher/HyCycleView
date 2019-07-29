//
//  HyCycleView.h
//  HyCycleView
//  https://github.com/hydreamit/HyCycleView
//
//  Created by Hy on 16/5/3.
//  Copyright © 2016年 Hy. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UIView+HyFrame.h"


typedef enum {
    HyCycleViewScrollStatic, // need hand scroll
    HyCycleViewScrollAuto   // auto scroll
} HyCycleViewScrollStyle;


typedef enum {
    HyCycleViewScrollLoadStyleWillAppear, // view/controller view  will appear load
    HyCycleViewScrollLoadStyleDidAppear  //  view/controller view  did appear load
} HyCycleViewScrollLoadStyle;


typedef enum {
    HyCycleViewScrollLeft,      // scroll to left
    HyCycleViewScrollRight,    // scroll to right
    HyCycleViewScrollTop,     // scroll to top
    HyCycleViewScrollBottom  // scroll to bottom
} HyCycleViewScrollDirection;


@class HyCycleView;
@interface HyCycleViewConfigure : NSObject

// currentPage (当前页面)
@property (nonatomic,assign,readonly) NSInteger currentPage;

// cycle loop default yes (是否为无限循环轮播 默认为YES)
- (HyCycleViewConfigure *(^)(BOOL))isCycleLoop;
// total Pages (总页数)
- (HyCycleViewConfigure *(^)(NSInteger))totalPage;
// start page (开始页)
- (HyCycleViewConfigure *(^)(NSInteger))startPage;
// timeInterval default 2.0 s (自动轮播时间间隔 默认2秒)
- (HyCycleViewConfigure *(^)(NSTimeInterval))timeInterval;

// auto or static scroll style (轮播方式：自动/手动, 默认是自动)
- (HyCycleViewConfigure *(^)(HyCycleViewScrollStyle))scrollStyle;
// cycle view load style (轮播View/Controller加载方式: 滑动出现立即加载/滑动到整个页面再加载)
- (HyCycleViewConfigure *(^)(HyCycleViewScrollLoadStyle))loadStyle;
// scroll direction (轮播方向:左、右、上、下)
- (HyCycleViewConfigure *(^)(HyCycleViewScrollDirection))scrollDirection;


// cycle views or controllers (轮播传入的是实例对象：view 或者 controller)
- (HyCycleViewConfigure *(^)(NSArray *))cycleInstances;
// cycle views or controllers of class (轮播传入的是Class：view class 或者 controller class)
- (HyCycleViewConfigure *(^)(NSArray<Class> *))cycleClasses;
- (HyCycleViewConfigure *(^)(Class (^)(HyCycleView *, NSInteger)))cycleClass;


// click cycleView action (点击某个轮播view的回调)
- (HyCycleViewConfigure *(^)(void(^)(HyCycleView *, NSInteger)))clickAction;

// one cycle will appear callback (当轮播view/controllerView出现的回调)
- (HyCycleViewConfigure *(^)(void(^)(HyCycleView *,  // HyCycleView
                                     id,            // cycleView
                                     NSInteger,    // currentIndex
                                     BOOL))       // is first load
                                     )viewWillAppear;

// totalPage and currentPage change (总页/当前页发生改变的回调)
- (HyCycleViewConfigure *(^)(void(^)(HyCycleView *, // HyCycleView
                                     NSInteger,    // totalPage
                                     NSInteger))  // currentPage
                                     )currentPageChange;

// totalPage and roundingPage change (总页/当前页(四舍五入)发生改变的回调)
- (HyCycleViewConfigure *(^)(void(^)(HyCycleView *, // HyCycleView
                                     NSInteger,    // totalPage
                                     NSInteger))  // roundingPage
                                     )roundingPageChange;

// scroll progress (滑动进度的回调)
- (HyCycleViewConfigure *(^)(void(^)(HyCycleView *, // HyCycleView
                                     NSInteger,    // fromPage
                                     NSInteger,   // toPage
                                     CGFloat))   // progress
                                    )scrollProgress;
@end





@interface HyCycleView : UIView

/**
 create cycleView

 @param frame frame
 @param configureBlock config the params
 @return HyCycleView
 */
+ (instancetype)cycleViewWithFrame:(CGRect)frame
                    configureBlock:(void (^)(HyCycleViewConfigure *configure))configureBlock;

@property (nonatomic, strong, readonly) HyCycleViewConfigure *configure;



/**
 scroll to next page

 @param animated animated
 */
- (void)scrollToNextPageWithAnimated:(BOOL)animated;


/**
 scroll to last page
 
 @param animated animated
 */
- (void)scrollToLastPageWithAnimated:(BOOL)animated;


/**
 scroll to the page

 @param page page
 @param animated animated
 */
- (void)scrollToPage:(NSInteger)page animated:(BOOL)animated;


@end
