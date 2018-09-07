//
//  fmod_player_effect.hpp
//  AudioProgress
//
//  Created by 赵成峰 on 2018/8/31.
//  Copyright © 2018年 赵成峰. All rights reserved.
//

#ifndef fmod_player_effect_hpp
#define fmod_player_effect_hpp

#include <stdio.h>
#include "fmod.hpp"

void fmod_set_audio_effect(int flag, FMOD_SYSTEM *fmod_system, FMOD_CHANNEL *fmod_channel, FMOD_DSP *fmod_dsp);

#endif /* fmod_player_effect_hpp */
