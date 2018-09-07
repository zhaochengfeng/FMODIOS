//
//  fmod_player.hpp
//  AudioProgress
//
//  Created by 赵成峰 on 2018/8/31.
//  Copyright © 2018年 赵成峰. All rights reserved.
//

#ifndef fmod_player_hpp
#define fmod_player_hpp

#include <stdio.h>
#include "fmod.hpp"

//Player
typedef struct FPlayer
{
    FMOD_SYSTEM *system;
    FMOD_SOUND *sound;
    FMOD_CHANNEL *channel;
    FMOD_CHANNELGROUP *channelGroup;
    FMOD_DSP *dsp;
    float volume;
    int flag;
} FPlayer;

//初始化
int play_init(FPlayer **play);

//播放音频
int play_start(FPlayer *play, const char *name, int flag);

//暂停或恢复 type =1 暂停 0恢复
int play_continue_pause(FPlayer *play,int type);

//关闭 释放资源
void play_close(FPlayer *play);

//停止播放
int play_stop(FPlayer *play);

//是否正在播放
bool play_is_playing(FPlayer *play);

#endif /* fmod_player_hpp */
