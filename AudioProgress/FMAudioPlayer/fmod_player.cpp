//
//  fmod_player.cpp
//  AudioProgress
//
//  Created by 赵成峰 on 2018/8/31.
//  Copyright © 2018年 赵成峰. All rights reserved.
//

#include "fmod_player.hpp"
#include "fmod_player_effect.hpp"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

bool play_is_playing(FPlayer *play)
{
    int playing = 0;
    FMOD_Channel_IsPlaying (play->channel , &playing);
    FMOD_System_Update(play->system);
    return playing == 0;
}

int play_init(FPlayer **play)//初始化
{
    int err = 0;
    *play = (FPlayer *)malloc(sizeof(FPlayer));
    if(*play == NULL) return -1;
    memset(*play,0,sizeof(FPlayer));
    (*play)->volume = 1.f;
    err = FMOD_System_Create(&(*play)->system);
    if(err != 0)
    {
        free(*play);
        return -1;
    }
    err = FMOD_System_Init((*play)->system, 10, FMOD_INIT_NORMAL,NULL);
    if(err!=0)
    {
        free(*play);
        return -1;
    }
    return 0;
}

void play_close(FPlayer *play)//关闭 释放资源
{
    if(play->channel != NULL) {
        FMOD_Channel_Stop(play->channel);
    }
    if(play->sound != NULL) {
        FMOD_Sound_Release(play->sound);
    }
    if(play->system != NULL) {
        FMOD_System_Close(play->system);
        FMOD_System_Release(play->system);
    }
    if(play->flag!=0) {
        play->flag=0;
    }
    if(play!=0) {
        free(play);
    }
}

int play_start(FPlayer *play, const char *name, int flag)
{
    int err = 0;
    err = FMOD_System_CreateStream(play->system,name, FMOD_3D, 0, &play->sound);
    if(err!=0) return -1;
    
    err = FMOD_Sound_SetMode(play->sound,FMOD_LOOP_OFF);
    if(err != 0) return -1;
    
    err = FMOD_System_PlaySound(play->system, play->sound, play->channelGroup, false, &play->channel);
    
    if(err!=0)return -1;
    play->flag = 1;
    
    //设置音效
    fmod_set_audio_effect(flag, play->system, play->channel, play->dsp);
    
    return err;
}

//暂停或恢复 type =1 暂停 0恢复
int play_continue_pause(FPlayer *play,int type)
{
    int err = 0;
    if (play->channel != NULL) {
        if(type == 0) {
            err = FMOD_Channel_SetPaused(play->channel,type);
        } else {
            err = FMOD_Channel_SetPaused(play->channel,type);
        }
    }
    return err;
}

//停止播放
int play_stop(FPlayer *play)
{
    int err = 0;
    if (play->channel != NULL) {
        err = FMOD_Channel_Stop(play->channel);
    }
    play->flag = 0;
    return err;
}

//获取音乐时长
unsigned int play_get_total_seconds(FPlayer *play)
{
    unsigned int length = 0;
    if (play->sound != NULL) {
        FMOD_Sound_GetLength(play->sound,&length,FMOD_TIMEUNIT_MS);
    }
    return length;
}

//获取当前位置
unsigned int play_get_current_pos(FPlayer *play)
{
    unsigned int position = 0;
    if(play->channel != NULL) {
        FMOD_Channel_GetPosition(play->channel,&position,FMOD_TIMEUNIT_MS);
    }
    return position;
}

//设置播放位置
int play_set_current_pos(FPlayer *play,unsigned int position)
{
    int err = 0;
    if(play->channel != NULL)
    {
        play_continue_pause(play,1);
        FMOD_Channel_SetPosition(play->channel,position,FMOD_TIMEUNIT_MS);
        play_continue_pause(play,0);
    }
    return err;
}

int play_set_volume(FPlayer *play,float n)//设置音量
{
    int err=0;
    err = FMOD_Channel_SetVolume(play->channel,n);
    if(err != 0) play->volume = n;
    return err;
}
