//
//  FMAudioPlayer.m
//  AudioProgress
//
//  Created by 赵成峰 on 2018/8/31.
//  Copyright © 2018年 赵成峰. All rights reserved.
//

#import "FMAudioPlayer.h"
#import "FMAudioPlayer.h"
#include "fmod_player.hpp"

@implementation FMAudioPlayerOption

+ (NSArray<FMAudioPlayerOption *> *)defaultOptions
{
    NSMutableArray *array = [NSMutableArray array];
    {
        FMAudioPlayerOption *option = [[FMAudioPlayerOption alloc] init];
        option.name = @"原声";
        option.flag = FMAudioPlayerOptionFlagOriginal;
        [array addObject:option];
    }
    
    {
        FMAudioPlayerOption *option = [[FMAudioPlayerOption alloc] init];
        option.name = @"萝莉";
        option.flag = FMAudioPlayerOptionFlagLolita;
        [array addObject:option];
    }
    
    {
        FMAudioPlayerOption *option = [[FMAudioPlayerOption alloc] init];
        option.name = @"惊悚";
        option.flag = FMAudioPlayerOptionFlagThriller;
        [array addObject:option];
    }
    
    {
        FMAudioPlayerOption *option = [[FMAudioPlayerOption alloc] init];
        option.name = @"大叔";
        option.flag = FMAudioPlayerOptionFlagUncle;
        [array addObject:option];
    }    
    
    {
        FMAudioPlayerOption *option = [[FMAudioPlayerOption alloc] init];
        option.name = @"搞怪";
        option.flag = FMAudioPlayerOptionFlagFunny;
        [array addObject:option];
    }
    
    {
        FMAudioPlayerOption *option = [[FMAudioPlayerOption alloc] init];
        option.name = @"空灵";
        option.flag = FMAudioPlayerOptionFlagVacant;
        [array addObject:option];
    }
    
    {
        FMAudioPlayerOption *option = [[FMAudioPlayerOption alloc] init];
        option.name = @"机器人";
        option.flag = FMAudioPlayerOptionFlagRobot;
        [array addObject:option];
    }
    
    {
        FMAudioPlayerOption *option = [[FMAudioPlayerOption alloc] init];
        option.name = @"合唱";
        option.flag = FMAudioPlayerOptionFlagChorus;
        [array addObject:option];
    }
    return array;
}

@end

@interface FMAudioPlayer ()

@property (nonatomic, strong) NSString *path;
@property (nonatomic, strong) FMAudioPlayerOption *option;

@end

@implementation FMAudioPlayer
{
    FPlayer *_player;
}

- (instancetype)initWithPath:(NSString *)path option:(FMAudioPlayerOption *)option
{
    if (self = [super init]) {
        self.path = path;
        self.option = option;
        play_init(&_player);
    }
    return self;
}

- (void)dealloc
{
    play_close(_player);
}

- (void)play
{
    play_start(_player, [self.path UTF8String], self.option.flag);
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(checkIsPlaying) object:nil];
    [self performSelector:@selector(checkIsPlaying) withObject:nil afterDelay:0.1];
}

- (void)pause
{
    play_continue_pause(_player, 1);
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:@selector(checkIsPlaying) object:nil];
}

- (void)stop
{
    play_stop(_player);
}

- (void)checkIsPlaying
{
    if (play_is_playing(_player)) {
        NSLog(@"播放结束");
        [self stop];
    } else {
        [self performSelector:@selector(checkIsPlaying) withObject:nil afterDelay:0.1];
        NSLog(@"正在播放");
    }
}

@end
