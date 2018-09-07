//
//  FMAudioPlayer.h
//  AudioProgress
//
//  Created by 赵成峰 on 2018/8/31.
//  Copyright © 2018年 赵成峰. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, FMAudioPlayerOptionFlag) {
    FMAudioPlayerOptionFlagOriginal,//原声
    FMAudioPlayerOptionFlagLolita,  //萝莉
    FMAudioPlayerOptionFlagThriller,//惊悚
    FMAudioPlayerOptionFlagUncle,   //大叔
    FMAudioPlayerOptionFlagFunny,   //搞怪
    FMAudioPlayerOptionFlagVacant,  //空灵
    FMAudioPlayerOptionFlagRobot,   //机器人
    FMAudioPlayerOptionFlagChorus,  //合唱
};

@interface FMAudioPlayerOption : NSObject

@property (nonatomic, strong) NSString *name;
@property (nonatomic, assign) FMAudioPlayerOptionFlag flag;

+ (NSArray<FMAudioPlayerOption *> *)defaultOptions;

@end

@interface FMAudioPlayer : NSObject

- (instancetype)initWithPath:(NSString *)path option:(FMAudioPlayerOption *)option;

- (void)play;
- (void)pause;
- (void)stop;

@end
