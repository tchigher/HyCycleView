//
//  CyclePageViewHoverOffsetDemoController.m
//  HyCycleView
//  https://github.com/hydreamit/HyCycleView
//
//  Created by Hy on 2016/5/21.
//  Copyright © 2016年 Hy. All rights reserved.
//

#import "CyclePageViewHoverOffsetDemoController.h"


@interface CyclePageViewHoverOffsetDemoController ()
@property (nonatomic,strong) UIScrollView *scrollView;
@property (nonatomic,assign) CGFloat lastAlpha;
@end


@implementation CyclePageViewHoverOffsetDemoController
@dynamic scrollView;

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    if (@available(iOS 11.0, *)) {
        self.scrollView.contentInsetAdjustmentBehavior = UIScrollViewContentInsetAdjustmentNever;
    }
    [self.navigationController.navigationBar setAlpha:self.lastAlpha];
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [self.navigationController.navigationBar setAlpha:1.f];
}

- (void (^)(HyCyclePageViewConfigure * _Nonnull))configPageView {
    
    CGFloat naviHeight = 64;
    if ([[UIApplication sharedApplication].keyWindow respondsToSelector:NSSelectorFromString(@"safeAreaInsets")]) {
        naviHeight = [[UIApplication sharedApplication] delegate].window.safeAreaInsets.top + 44;
    }
    
    CGFloat headerViewH = 250;
    
    __weak typeof(self) _self = self;
    return ^(HyCyclePageViewConfigure * _Nonnull configure) {
        
        [[[[configure hoverViewOffset:naviHeight] headerViewDownAnimation:HyCyclePageViewHeaderViewDownAnimationScale] headerViewUpAnimation:HyCyclePageViewHeaderViewUpAnimationCover] verticalScrollProgress:^(HyCyclePageView * _Nonnull cyclePageView, UIView * _Nonnull view, NSInteger index, CGFloat offset) {
            
            __strong typeof(_self) self = _self;
            CGFloat margin = headerViewH - naviHeight;
            if (offset >= margin) {
                [self.navigationController.navigationBar setAlpha:1.0f];
            }else if (offset < 0) {
                [self.navigationController.navigationBar setAlpha:.0f];
            }else {
                [self.navigationController.navigationBar setAlpha:(offset / margin)];
            }
            self.lastAlpha = self.navigationController.navigationBar.alpha;
        }];
    };
}

@end
