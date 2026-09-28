#ifndef SOUND_CPS3SOUND_H
#define SOUND_CPS3SOUND_H

#include "types.h"

void SsRequest(u16 ReqNumber);
void SsResetBgmChannels();
void SsBgmControl(s8 unused, s8 VOLUME);
void FUN_0613a334();

#endif
